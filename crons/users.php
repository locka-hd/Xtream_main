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
                    $ipTV_db->query('SELECT * FROM `lines_live` WHERE `hls_end` = 0;');
                    $rRows = $ipTV_db->get_rows();
                    if (count($rRows) > 0) {
                        $rStreamIDs = array();
                        foreach ($rRows as $rRow) {
                            if (!in_array($rRow['stream_id'], $rStreamIDs) || $rRow['stream_id'] > 0) {
                                $rStreamIDs[] = intval($rRow['stream_id']);
                            }
                        }
                        $rOnDemand = array();
                        if (count($rStreamIDs) > 0) {
                            $ipTV_db->query('SELECT `stream_id`, `server_id`, `on_demand` FROM `streams_servers` WHERE `stream_id` IN (' . implode(',', $rStreamIDs) . ');');
                            foreach ($ipTV_db->get_rows() as $rRow) {
                                $rOnDemand[$rRow['stream_id']][$rRow['server_id']] = intval($rRow['on_demand']);
                            }
                        }
                        $rRedis = ipTV_lib::$redis->multi();
                        foreach ($rRows as $rRow) {
                            echo 'Resynchronising UUID: ' . $rRow['uuid'] . "\n";
                            if (empty($rRow['hmac_id'])) {
                                $rRow['identity'] = $rRow['user_id'];
                            } else {
                                $rRow['identity'] = $rRow['hmac_id'] . '_' . $rRow['hmac_identifier'];
                            }
                            $rRow['on_demand'] = ($rOnDemand[$rRow['stream_id']][$rRow['server_id']] ?: 0);
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
                            $rDeSync[] = $rRow['uuid'];
                        }
                        $rRedis->exec();
                        if (count($rDeSync) > 0) {
                            $ipTV_db->query("DELETE FROM `lines_live` WHERE `uuid` IN ('" . implode("','", $rDeSync) . "');");
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
    if (ipTV_lib::$settings['redis_handler']) {
        if ($rDelete['count'] > 0) {
            $rRedis = ipTV_lib::$redis->multi();
            foreach ($rDelete['line'] as $rUserID => $rUUIDs) {
                $rRedis->zRem('LINE#' . $rUserID, ...$rUUIDs);
                $rRedis->zRem('LINE_ALL#' . $rUserID, ...$rUUIDs);
            }
            foreach ($rDelete['stream'] as $rStreamID => $rUUIDs) {
                $rRedis->zRem('STREAM#' . $rStreamID, ...$rUUIDs);
            }
            foreach ($rDelete['server'] as $rServerID => $rUUIDs) {
                $rRedis->zRem('SERVER#' . $rServerID, ...$rUUIDs);
                $rRedis->zRem('SERVER_LINES#' . $rServerID, ...$rUUIDs);
            }
            if (count($rDelete['uuid']) > 0) {
                $rRedis->zRem('CONNECTIONS', ...$rDelete['uuid']);
                $rRedis->zRem('LIVE', ...$rDelete['uuid']);
                $rRedis->sRem('ENDED', ...$rDelete['uuid']);
                $rRedis->del(...$rDelete['uuid']);
            }
            $rRedis->exec();
        }
    } else {
        foreach ($rDelete as $rServerID => $rConnections) {
            if (count($rConnections) > 0) {
                $ipTV_db->query("DELETE FROM `lines_live` WHERE `uuid` IN ('" . implode("','", $rConnections) . "')");
            }
        }
    }
    foreach ((ipTV_lib::$settings['redis_handler'] ? $rDelete['server'] : $rDelete) as $rServerID => $rConnections) {
        if ($rServerID != SERVER_ID) {
            $rQuery = '';
            foreach ($rConnections as $rConnection) {
                $rQuery .= '(' . $rServerID . ',1,' . $rTime . ',' . $ipTV_db->escape(json_encode(array('type' => 'delete_con', 'uuid' => $rConnection))) . '),';
            }
            $rQuery = rtrim($rQuery, ',');
            if (!empty($rQuery)) {
                $ipTV_db->query('INSERT INTO `signals`(`server_id`, `cache`, `time`, `custom_data`) VALUES ' . $rQuery . ';');
            }
        }
    }
    foreach ($rDelStream as $rStreamID => $rConnections) {
        foreach ($rConnections as $rConnection) {
            ipTV_lib::unlinkFile(CONS_TMP_PATH . $rStreamID . '/' . $rConnection);
        }
    }
    if (ipTV_lib::$settings['redis_handler']) {
        return array('line' => array(), 'server' => array(), 'server_lines' => array(), 'stream' => array(), 'uuid' => array(), 'count' => 0);
    }
    return array();
}
function loadCron() {
    global $ipTV_db;
    global $rPHPPIDs;

    if (ipTV_lib::$settings['redis_handler']) {
        ipTV_lib::connectRedis();
    }

    $rStartTime = time();

    if (!ipTV_lib::$settings['redis_handler'] && ipTV_lib::$Servers[SERVER_ID]['is_main']) {
        $rAutoKick = ipTV_lib::$settings['user_auto_kick_hours'] * 3600;
        $rLiveKeys = $rDelete = $rDeleteStream = array();

        if (ipTV_lib::$settings['redis_handler']) {
            $rRedisDelete = array(
                'line' => array(),
                'server' => array(),
                'server_lines' => array(),
                'stream' => array(),
                'uuid' => array(),
                'count' => 0
            );

            list($rKeys, $rConnections) = ipTV_streaming::getConnections();
            $rUsers = array();

            foreach ($rConnections as $i => $rConnection) {
                if (is_array($rConnection)) {
                    $rUsers[$rConnection['identity']][] = $rConnection;
                    $rLiveKeys[] = $rConnection['uuid'];
                } else {
                    $rRedisDelete['count']++;
                    $rRedisDelete['uuid'][] = $rKeys[$i];
                }
            }
        } else {
            $rUsers = ipTV_streaming::getConnections((ipTV_lib::$Servers[SERVER_ID]['is_main'] ? null : SERVER_ID));
        }

        foreach ($rUsers as $rUserID => $rConnections) {
            foreach ($rConnections as $rConnection) {
                if ($rConnection['server_id'] == SERVER_ID || ipTV_lib::$settings['redis_handler']) {
                    $isExpired = !is_null($rConnection['exp_date']) && $rConnection['exp_date'] < $rStartTime;
                    $isHLSExpired = $rConnection['container'] == 'hls' && (30 <= $rStartTime - $rConnection['hls_last_read'] || $rConnection['hls_end'] == 1);
                    $isTSExpired = $rConnection['container'] == 'ts' && checkTSExpired($rConnection, $rPHPPIDs, $rStartTime);

                    if ($isExpired || $isHLSExpired || $isTSExpired) {
                        closeConnection($rConnection, $rRedisDelete, $rDelete, $rDeleteStream);
                    }
                }
            }
        }

        if (!empty($rRedisDelete['uuid']) || !empty($rDelete)) {
            processDeletions($rRedisDelete, $rDeleteStream);
        }
    }

    $rConnectionSpeeds = glob(DIVERGENCE_TMP_PATH . '*');
    if (count($rConnectionSpeeds) > 0) {
        processDivergences($rConnectionSpeeds);
    }

    if (ipTV_lib::$Servers[SERVER_ID]['is_main']) {
        if (ipTV_lib::$settings['redis_handler']) {
            $ipTV_db->query('DELETE FROM `lines_divergence` WHERE `uuid` NOT IN (SELECT `uuid` FROM `lines_live`);');
        } else {
            $ipTV_db->query("DELETE FROM `lines_divergence` WHERE `uuid` NOT IN ('" . implode("','", $rLiveKeys) . "');");
        }
    }

    if (ipTV_lib::$Servers[SERVER_ID]['is_main']) {
        $ipTV_db->query('DELETE FROM `lines_live` WHERE `uuid` IS NULL;');
    }
}

function closeConnection($rConnection, &$rRedisDelete, &$rDelete, &$rDeleteStream) {
    echo 'Closing connection: ' . $rConnection['uuid'] . "\n";
    ipTV_streaming::closeConnection($rConnection, false, false);

    if (ipTV_lib::$settings['redis_handler']) {
        $rRedisDelete['count']++;
        $rRedisDelete['line'][$rConnection['identity']][] = $rConnection['uuid'];
        $rRedisDelete['stream'][$rConnection['stream_id']][] = $rConnection['uuid'];
        $rRedisDelete['server'][$rConnection['server_id']][] = $rConnection['uuid'];
        $rRedisDelete['uuid'][] = $rConnection['uuid'];
    } else {
        $rDelete[$rConnection['server_id']][] = $rConnection['uuid'];
        $rDeleteStream[$rConnection['stream_id']] = $rDelete[$rConnection['server_id']];
    }
}

function checkTSExpired($rConnection, $rPHPPIDs, $rStartTime) {
    if ($rConnection['server_id'] == SERVER_ID) {
        return !ipTV_streaming::isProcessRunning($rConnection['pid'], 'php-fpm');
    } elseif (
        $rConnection['date_start'] <= ipTV_lib::$Servers[$rConnection['server_id']]['last_check_ago'] - 1 &&
        !empty($rPHPPIDs[$rConnection['server_id']])
    ) {
        return !in_array((int)$rConnection['pid'], $rPHPPIDs[$rConnection['server_id']]);
    }

    return 45 <= $rStartTime - $rConnection['hls_last_read'];
}

function processDivergences($rConnectionSpeeds) {
    global $ipTV_db;

    $rBitrates = array();
    $ipTV_db->query('SELECT `lines_live`.`uuid`, `streams_servers`.`bitrate` FROM `lines_live` LEFT JOIN `streams_servers` ON `lines_live`.`stream_id` = `streams_servers`.`stream_id` AND `lines_live`.`server_id` = `streams_servers`.`server_id` WHERE `lines_live`.`server_id` = \'%d\';', SERVER_ID);

    foreach ($ipTV_db->get_rows() as $rRow) {
        $rBitrates[$rRow['uuid']] = intval($rRow['bitrate'] / 8 * 0.92);
    }

    foreach ($rConnectionSpeeds as $rConnectionSpeed) {
        if (!empty($rConnectionSpeed)) {
            $rUUID = basename($rConnectionSpeed);
            $rAverageSpeed = intval(file_get_contents($rConnectionSpeed));
            $rDivergence = intval(($rAverageSpeed - $rBitrates[$rUUID]) / $rBitrates[$rUUID] * 100);
            $rDivergence = $rDivergence > 0 ? 0 : abs($rDivergence);

            $ipTV_db->query('INSERT INTO `lines_divergence`(`uuid`,`divergence`) VALUES (?, ?) ON DUPLICATE KEY UPDATE `divergence` = VALUES(`divergence`);', $rUUID, $rDivergence);
        }
    }

    shell_exec('rm -f ' . DIVERGENCE_TMP_PATH . '*');
}


function shutdown() {
    global $ipTV_db;
    global $unique_id;
    if (is_object($ipTV_db)) {
        $ipTV_db->close_mysql();
    }
    @unlink($unique_id);
}
