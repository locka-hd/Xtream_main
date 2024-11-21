<?php
if (posix_getpwuid(posix_geteuid())['name'] == 'xtreamcodes') {
    set_time_limit(0);
    ini_set('memory_limit', -1);
    if ($argc) {
        register_shutdown_function('shutdown');
        require str_replace('\\', '/', dirname($argv[0])) . '/../wwwdir/init.php';
        cli_set_process_title('XtreamCodes[Users Parser]');
        $unique_id = CRONS_TMP_PATH . md5(generateUniqueCode() . __FILE__);
        ipTV_lib::checkCron($unique_id);
        $rSync = null;
        if (count($argv) == 2 && ipTV_lib::$Servers[SERVER_ID]['is_main']) {
            ipTV_lib::connectRedis();
            if (is_object(ipTV_lib::$redis)) {
                $rSync = intval($argv[1]);
                if ($rSync == 1) {
                $rDeSync = $rRedisUsers = $rRedisUpdate = $rRedisSet = array();
    
               // Retrieve active rows from lines_live table
               $ipTV_db->query('SELECT * FROM `lines_live` WHERE `hls_end` = 0;');
                 $rRows = $ipTV_db->get_rows();
    
                   if (count($rRows) > 0) {
                   $rStreamIDs = array();

                     // Collect unique stream IDs
                     foreach ($rRows as $rRow) {
                        if (!in_array($rRow['stream_id'], $rStreamIDs) && $rRow['stream_id'] > 0) {
                        $rStreamIDs[] = intval($rRow['stream_id']);
                       }
                    }

                   $rOnDemand = array();

                   // Fetch on_demand status for collected stream IDs
                    if (count($rStreamIDs) > 0) {
                    $ipTV_db->query(
                        'SELECT `stream_id`, `server_id`, `on_demand` 
                         FROM `streams_servers` 
                         WHERE `stream_id` IN (' . implode(',', $rStreamIDs) . ');'
                    );
                    foreach ($ipTV_db->get_rows() as $rRow) {
                        $rOnDemand[$rRow['stream_id']][$rRow['server_id']] = intval($rRow['on_demand']);
            }
        }

        // Use Redis multi-exec for performance
        $rRedis = ipTV_lib::$redis->multi();

        $rProcessedUUIDs = array(); // Track processed UUIDs to avoid duplicates
        foreach ($rRows as $rRow) {
            echo 'Resynchronising UUID: ' . $rRow['uuid'] . "\n";

            if (empty($rRow['hmac_id'])) {
                $rRow['identity'] = $rRow['user_id'];
            } else {
                $rRow['identity'] = $rRow['hmac_id'] . '_' . $rRow['hmac_identifier'];
            }

            $rRow['on_demand'] = ($rOnDemand[$rRow['stream_id']][$rRow['server_id']] ?? 0);

            // Check for duplicate UUIDs and retain the most recent entry
            if (!isset($rProcessedUUIDs[$rRow['uuid']]) || 
                $rProcessedUUIDs[$rRow['uuid']] < $rRow['date_start']) {
                
                $rProcessedUUIDs[$rRow['uuid']] = $rRow['date_start'];

                $rRedis->zAdd('LINE#' . $rRow['identity'], $rRow['date_start'], $rRow['uuid']);
                $rRedis->zAdd('LINE_ALL#' . $rRow['identity'], $rRow['date_start'], $rRow['uuid']);
                $rRedis->zAdd('STREAM#' . $rRow['stream_id'], $rRow['date_start'], $rRow['uuid']);
                $rRedis->zAdd('SERVER#' . $rRow['server_id'], $rRow['date_start'], $rRow['uuid']);

                if ($rRow['user_id']) {
                    $rRedis->zAdd('SERVER_LINES#' . $rRow['server_id'], $rRow['user_id'], $rRow['uuid']);
                }

                $rRedis->zAdd('CONNECTIONS', $rRow['date_start'], $rRow['uuid']);
                $rRedis->zAdd('LIVE', $rRow['date_start'], $rRow['uuid']);
                $rRedis->set($rRow['uuid'], igbinary_serialize($rRow));
            } else {
                // Mark duplicate UUIDs for deletion
                $rDeSync[] = $rRow['uuid'];
            }
        }

        $rRedis->exec();

        // Remove duplicate UUIDs from the database
        if (count($rDeSync) > 0) {
            $ipTV_db->query(
                "DELETE FROM `lines_live` WHERE `uuid` IN ('" . implode("','", $rDeSync) . "');"
            );
        }
   }
}

            } else {
                exit("Couldn't connect to Redis." . "\n");
            }
        }
        if (ipTV_lib::$settings['redis_handler'] && ipTV_lib::$Servers[SERVER_ID]['is_main']) {
            ipTV_lib::$Servers = ipTV_lib::getServers(true);
            $rPHPPIDs = array();
            foreach (ipTV_lib::$Servers as $rServer) {
                $rPHPPIDs[$rServer['id']] = (array_map('intval', json_decode($rServer['php_pids'], true)) ?: array());
            }
        }
        loadCron();
    } else {
        exit(0);
    }
} else {
    exit('Please run as XtreamCodes!' . "\n");
}
function processDeletions($rDelete, $rDelStream = array()) {
    global $ipTV_db;
    $rTime = time();

    // Validate structure
    if (!is_array($rDelete) || empty($rDelete)) {
        error_log("Invalid rDelete structure passed to processDeletions.");
        return false;
    }

    // Handle Redis-based cleanup
    if (ipTV_lib::$settings['redis_handler']) {
        if (!empty($rDelete['count'])) {
            try {
                $rRedis = ipTV_lib::$redis->multi();

                // Remove UUIDs associated with users
                foreach ($rDelete['line'] as $rUserID => $rUUIDs) {
                    $rRedis->zRem('LINE#' . $rUserID, ...$rUUIDs);
                    $rRedis->zRem('LINE_ALL#' . $rUserID, ...$rUUIDs);
                }

                // Remove UUIDs associated with streams
                foreach ($rDelete['stream'] as $rStreamID => $rUUIDs) {
                    $rRedis->zRem('STREAM#' . $rStreamID, ...$rUUIDs);
                }

                // Remove UUIDs associated with servers
                foreach ($rDelete['server'] as $rServerID => $rUUIDs) {
                    $rRedis->zRem('SERVER#' . $rServerID, ...$rUUIDs);
                    $rRedis->zRem('SERVER_LINES#' . $rServerID, ...$rUUIDs);
                }

                // Remove UUIDs from global lists
                if (!empty($rDelete['uuid'])) {
                    $batchSize = 1000;
                    $uuidChunks = array_chunk($rDelete['uuid'], $batchSize);
                    foreach ($uuidChunks as $chunk) {
                        $rRedis->zRem('CONNECTIONS', ...$chunk);
                        $rRedis->zRem('LIVE', ...$chunk);
                        $rRedis->sRem('ENDED', ...$chunk);
                        $rRedis->del(...$chunk);
                    }
                }

                // Execute the Redis operations
                if ($rRedis->exec() === false) {
                    error_log("Redis transaction failed: No commands executed.");
                }
            } catch (Exception $e) {
                error_log("Redis deletion error: " . $e->getMessage());
                return false;
            }
        }
    } else {
        // Handle database-based cleanup
        foreach ($rDelete as $rServerID => $rConnections) {
            if (!empty($rConnections)) {
                try {
                    $ipTV_db->query("DELETE FROM `lines_live` WHERE `uuid` IN ('" . implode("','", $rConnections) . "') LIMIT " . count($rConnections));
                } catch (Exception $e) {
                    error_log("Database deletion error: " . $e->getMessage());
                }
            }
        }
    }

    // Generate deletion signals for other servers
    foreach ((ipTV_lib::$settings['redis_handler'] ? $rDelete['server'] : $rDelete) as $rServerID => $rConnections) {
        if ($rServerID != SERVER_ID && !empty($rConnections)) {
            $rQuery = '';
            foreach ($rConnections as $rConnection) {
                $rQuery .= '(' . $rServerID . ', 1, ' . $rTime . ', ' 
                        . $ipTV_db->escape(json_encode(array('type' => 'delete_con', 'uuid' => $rConnection))) . '),';
            }
            $rQuery = rtrim($rQuery, ',');
            if (!empty($rQuery)) {
                try {
                    $ipTV_db->query('INSERT INTO `signals`(`server_id`, `cache`, `time`, `custom_data`) VALUES ' . $rQuery . ';');
                } catch (Exception $e) {
                    error_log("Signal generation error: " . $e->getMessage());
                }
            }
        }
    }

    // Cleanup associated stream files
    foreach ($rDelStream as $rStreamID => $rConnections) {
        foreach ($rConnections as $rConnection) {
            $filePath = CONS_TMP_PATH . $rStreamID . '/' . $rConnection;
            if (file_exists($filePath)) {
                if (!ipTV_lib::unlinkFile($filePath)) {
                    error_log("Failed to delete file: " . $filePath);
                }
            }
        }
    }

    // Return updated structure for Redis cleanup tracking
    if (ipTV_lib::$settings['redis_handler']) {
        return array(
            'line' => array(),
            'server' => array(),
            'server_lines' => array(),
            'stream' => array(),
            'uuid' => array(),
            'count' => 0
        );
    }

    return array();
}

function loadCron() {
    global $ipTV_db, $rPHPPIDs;

    if (ipTV_lib::$settings['redis_handler']) {
        ipTV_lib::connectRedis();
        if (!is_object(ipTV_lib::$redis)) {
            error_log("Failed to connect to Redis.");
            return;
        }
    }

    $rStartTime = time();
    $rAutoKick = ipTV_lib::$settings['user_auto_kick_hours'] * 3600;

    $rRedisDelete = initializeRedisDeleteStructure();
    $rProcessedUUIDs = [];
    $rUsers = [];

    // Fetch all active user connections
    if (ipTV_lib::$settings['redis_handler']) {
        list($rKeys, $rConnections) = ipTV_streaming::getConnections();
        foreach ($rConnections as $i => $rConnection) {
            if (is_array($rConnection)) {
                $uuid = $rConnection['uuid'];
                if (!isset($rProcessedUUIDs[$uuid]) || $rProcessedUUIDs[$uuid] < $rConnection['date_start']) {
                    $rProcessedUUIDs[$uuid] = $rConnection['date_start'];
                    $rUsers[$rConnection['identity']][] = $rConnection;
                }
            } else {
                $rRedisDelete['count']++;
                $rRedisDelete['uuid'][] = $rKeys[$i];
            }
        }
    } else {
        $rUsers = ipTV_streaming::getConnections(ipTV_lib::$Servers[SERVER_ID]['is_main'] ? null : SERVER_ID);
    }

    // Confirm user IDs and retrieve max connections
    $rMaxConnectionsArray = $rRestreamerArray = [];
    $rUserIDs = ipTV_lib::confirmIDs(array_keys($rUsers ?? []));
    if (count($rUserIDs) > 0) {
        $ipTV_db->query('SELECT `id`, `max_connections`, `is_restreamer` FROM `users` WHERE `id` IN (' . implode(',', $rUserIDs) . ');');
        foreach ($ipTV_db->get_rows() as $rRow) {
            $rMaxConnectionsArray[$rRow['id']] = $rRow['max_connections'];
            $rRestreamerArray[$rRow['id']] = $rRow['is_restreamer'];
        }
    }

    // Process user connections
    foreach ($rUsers as $rUserID => $rConnections) {
        $rActiveCount = 0;
        $rMaxConnections = $rMaxConnectionsArray[$rUserID] ?? 0;
        $rIsRestreamer = $rRestreamerArray[$rUserID] ?? false;

        foreach ($rConnections as $rConnection) {
            if (processConnection($rConnection, $rMaxConnections, $rActiveCount, $rIsRestreamer, $rRedisDelete)) {
                $rActiveCount++;
            }
        }

        if ($rMaxConnections > 0 && $rActiveCount > $rMaxConnections) {
            error_log("User $rUserID exceeded maximum allowed connections.");
        }
    }

    // Cleanup expired connections
    if ($rRedisDelete['count'] > 0) {
        processDeletions($rRedisDelete);
    }

    // Perform divergence cleanup and line synchronization
    cleanupDivergenceFiles();
    cleanupLinesLive();
    synchronizeDivergence();
}

function processConnection($rConnection, $rMaxConnections, &$rActiveCount, $rIsRestreamer, &$rRedisDelete) {
    global $rStartTime, $rAutoKick;

    $uuid = $rConnection['uuid'];
    $shouldClose = false;

    if (is_null($rConnection['exp_date']) || $rConnection['exp_date'] >= $rStartTime) {
        $rTotalTime = $rStartTime - $rConnection['date_start'];
        if (!($rAutoKick > 0 && $rTotalTime >= $rAutoKick) || $rIsRestreamer) {
            if ($rConnection['container'] === 'hls') {
                if ($rStartTime - $rConnection['hls_last_read'] >= 30 || $rConnection['hls_end'] == 1) {
                    $shouldClose = true;
                }
            } else if ($rConnection['container'] === 'ts') {
                $shouldClose = checkStreamStatus($rConnection);
            }
        }
    } else {
        $shouldClose = true;
    }

    if ($shouldClose) {
        echo "Closing connection: $uuid\n";
        closeConnection($rConnection, $rRedisDelete);
        return false;
    }

    return true;
}

function checkStreamStatus($rConnection) {
    global $rPHPPIDs;

    if ($rConnection['server_id'] == SERVER_ID) {
        return !ipTV_streaming::isProcessRunning($rConnection['pid'], 'php-fpm');
    } else {
        $lastCheck = ipTV_lib::$Servers[$rConnection['server_id']]['last_check_ago'];
        $pidExists = in_array($rConnection['pid'], $rPHPPIDs[$rConnection['server_id']] ?? []);
        return $rConnection['date_start'] <= $lastCheck - 1 && !$pidExists;
    }
}

function closeConnection($rConnection, &$rRedisDelete) {
    $uuid = $rConnection['uuid'];
    $rRedisDelete['count']++;
    $rRedisDelete['uuid'][] = $uuid;
    $rRedisDelete['line'][$rConnection['identity']][] = $uuid;
    $rRedisDelete['stream'][$rConnection['stream_id']][] = $uuid;
    $rRedisDelete['server'][$rConnection['server_id']][] = $uuid;

    if ($rConnection['user_id']) {
        $rRedisDelete['server_lines'][$rConnection['server_id']][] = $uuid;
    }
}

function processDeletions($rDelete) {
    global $ipTV_db;

    try {
        if (ipTV_lib::$settings['redis_handler']) {
            $rRedis = ipTV_lib::$redis->multi();

            foreach ($rDelete['uuid'] as $uuid) {
                $rRedis->del($uuid);
            }
            foreach ($rDelete['line'] as $rUserID => $rUUIDs) {
                $rRedis->zRem('LINE#' . $rUserID, ...$rUUIDs);
                $rRedis->zRem('LINE_ALL#' . $rUserID, ...$rUUIDs);
            }

            $rRedis->exec();
        } else {
            $ipTV_db->query("DELETE FROM `lines_live` WHERE `uuid` IN ('" . implode("','", $rDelete['uuid']) . "')");
        }
    } catch (Exception $e) {
        error_log("Error in processDeletions: " . $e->getMessage());
    }
}

function cleanupLinesLive() {
    global $ipTV_db;

    do {
        $affectedRows = $ipTV_db->query('DELETE FROM `lines_live` WHERE `uuid` IS NULL LIMIT 1000;')->affected_rows;
        if ($affectedRows > 0) {
            echo "Cleaned up $affectedRows rows in lines_live.\n";
        }
    } while ($affectedRows > 0);
}

function cleanupDivergenceFiles() {
    $rConnectionSpeeds = glob(DIVERGENCE_TMP_PATH . '*');
    foreach ($rConnectionSpeeds as $filePath) {
        unlink($filePath);
        echo "Deleted divergence file: $filePath\n";
    }
}

function synchronizeDivergence() {
    global $ipTV_db;

    // Fetch divergence data
    $rStreamMap = [];
    $ipTV_db->query('SELECT `stream_id`, `bitrate` FROM `streams_servers` WHERE `server_id` = ' . SERVER_ID);
    foreach ($ipTV_db->get_rows() as $rRow) {
        $rStreamMap[intval($rRow['stream_id'])] = intval($rRow['bitrate'] / 8 * 0.92);
    }

    // Process divergence synchronization
    $rDivergenceUpdate = [];
    $rConnectionSpeeds = glob(DIVERGENCE_TMP_PATH . '*');
    foreach ($rConnectionSpeeds as $filePath) {
        $uuid = basename($filePath);
        $averageSpeed = intval(file_get_contents($filePath));
        $bitrate = $rStreamMap[$uuid] ?? 0;
        $divergence = ($bitrate > 0) ? intval(($averageSpeed - $bitrate) / $bitrate * 100) : 0;
        $rDivergenceUpdate[] = "('$uuid', " . abs($divergence) . ")";
    }

    if (count($rDivergenceUpdate) > 0) {
        $ipTV_db->query('INSERT INTO `lines_divergence`(`uuid`,`divergence`) VALUES ' . implode(',', $rDivergenceUpdate) . ' ON DUPLICATE KEY UPDATE `divergence`=VALUES(`divergence`);');
    }
}

function initializeRedisDeleteStructure() {
    return [
        'line' => [],
        'server' => [],
        'server_lines' => [],
        'stream' => [],
        'uuid' => [],
        'count' => 0
    ];
}
function shutdown() {
    global $ipTV_db;
    global $unique_id;
    if (is_object($ipTV_db)) {
        $ipTV_db->close_mysql();
    }
    @unlink($unique_id);
}
