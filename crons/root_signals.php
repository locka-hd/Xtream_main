<?php
if (posix_getpwuid(posix_geteuid())['name'] == 'root') {
    set_time_limit(0);
    if ($argc) {
        register_shutdown_function('shutdown');
        require str_replace('\\', '/', dirname($argv[0])) . '/../wwwdir/init.php';
        $unique_id = CRONS_TMP_PATH . md5(generateUniqueCode() . __FILE__);
        ipTV_lib::check_cron($unique_id);
        shell_exec("sudo kill -9 `ps -ef | grep 'XtreamCodesSignals' | grep -v grep | awk '{print \$2}'`;");
        cli_set_process_title('XtreamCodesSignals');
        loadCron();
    } else {
        exit(0);
    }
} else {
    exit('Please run as root!' . "\n");
}


function loadCron() {
    global $ipTV_db;
    // XtreamCodes::$rServers = ipTV_lib::getServers(true);

    if ($ipTV_db->query("SELECT `signal_id`, `custom_data` FROM `signals` WHERE `server_id` = '%s' AND `custom_data` <> '' AND `cache` = 0 ORDER BY signal_id ASC;", SERVER_ID)) {
        $rRows = $ipTV_db->get_rows();
        if (file_exists(TMP_PATH . 'crontab')) {
            exec('crontab -u xtreamcodes -l', $rCrons);
            $rCurrentCron = trim(implode("\n", $rCrons));
            $ipTV_db->query('SELECT * FROM `crontab` WHERE `enabled` = 1;');
            foreach ($ipTV_db->get_rows() as $rRow) {
                $rFullPath = CRON_PATH . $rRow['filename'];
                if (pathinfo($rFullPath, PATHINFO_EXTENSION) == 'php' && file_exists($rFullPath)) {
                    $rJobs[] = $rRow['time'] . ' ' . PHP_BIN . ' ' . $rFullPath . ' # XtreamCodes';
                }
            }
            $rActualCron = trim(implode("\n", $rJobs));
            if ($rCurrentCron != $rActualCron) {
                echo 'Updating Crons...' . "\n";
                unlink(TMP_PATH . 'crontab');
            }
        }
        if (count($rRows) > 0) {
            foreach ($rRows as $rRow) {
                $rData = json_decode($rRow['custom_data'], true);
                if (!$rRow['signal_id']) {
                } else {
                    $ipTV_db->query('DELETE FROM `signals` WHERE `signal_id` = \'%s\';', $rRow['signal_id']);
                }
                switch ($rData['action']) {
                    case 'reboot':
                        echo 'Rebooting system...' . "\n";
                        $ipTV_db->query("INSERT INTO `mysql_syslog`(`server_id`, `type`, `error`, `username`, `ip`, `database`, `date`) VALUES('%s', 'REBOOT', 'System rebooted on request.', 'root', 'localhost', NULL, '%s');", SERVER_ID, time());
                        $ipTV_db->close_mysql();
                        shell_exec('sudo reboot');
                        break;
                    case 'reload_nginx':
                        echo 'Reloading nginx...' . "\n";
                        $ipTV_db->query("INSERT INTO `mysql_syslog`(`server_id`, `type`, `error`, `username`, `ip`, `database`, `date`) VALUES('%s', 'RELOAD', 'NGINX services reloaded on request.', 'root', 'localhost', NULL, '%s');", SERVER_ID, time());
                        shell_exec('sudo ' . BIN_PATH . 'nginx_rtmp/sbin/nginx_rtmp -s reload');
                        shell_exec('sudo ' . BIN_PATH . 'nginx/sbin/nginx -s reload');
                        break;
                    case 'update':
                        echo 'Updating...' . "\n";
                        $ipTV_db->query("INSERT INTO `mysql_syslog`(`server_id`, `type`, `error`, `username`, `ip`, `database`, `date`) VALUES('%s', 'UPDATE', 'Updating XtreamCodes...', 'root', 'localhost', NULL, '%s');", SERVER_ID, time());
                        shell_exec('sudo ' . PHP_BIN . ' ' . TOOLS_PATH . 'update.php "update" 2>&1 &');
                        break;
                    default:
                        break;
                }
            }
        }
        $ipTV_db->query('DELETE FROM `signals` WHERE LENGTH(`custom_data`) > 0 AND UNIX_TIMESTAMP() - `time` >= 86400;');
        $ipTV_db->close_mysql();
    } else {
        exit();
    }
}

function shutdown() {
    global $ipTV_db;
    global $unique_id;
    if (is_object($ipTV_db)) {
        $ipTV_db->close_mysql();
    }
    @unlink($unique_id);
}
