<?php

//cron lines log

set_time_limit(0);
if ($argc) {
    register_shutdown_function('shutdown');
    require str_replace('\\', '/', dirname($argv[0])) . '/../wwwdir/init.php';
    cli_set_process_title('XtreamCodes[Lines Logs]');
    $identifier = TMP_DIR . md5(UniqueID() . __FILE__);
    ipTV_lib::check_cron($identifier);
    loadCron();
} else {
    exit(0);
}

function loadCron() {
    global $ipTV_db;
    $logFile = TMP_DIR . 'client_request.log';
    if (!file_exists($logFile)) {
    } else {
        $Query = rtrim(parseLogs($logFile), ',');

        if (!empty($Query)) {
            $ipTV_db->simple_query("INSERT INTO `client_logs` (`stream_id`,`user_id`,`client_status`,`query_string`,`user_agent`,`ip`,`extra_data`,`date`) VALUES " . $Query);
        }
        unlink($logFile);
    }
}
function parseLogs($logFile) {
    global $ipTV_db;
    $Query = '';
    $fp = fopen($logFile, 'r');
    while (!feof($fp)) {
        $line = trim(fgets($fp));
        if (!empty($line)) {
            $line = json_decode(base64_decode($line), true);
            $line = array_map(array($ipTV_db, 'escape'), $line);
            $Query .= '(\'' . $line['stream_id'] . '\',\'' . $line['user_id'] . '\',\'' . $line['action'] . '\',\'' . $line['query_string'] . '\',\'' . $line['user_agent'] . '\',\'' . $line['user_ip'] . '\',\'' . $line['extra_data'] . '\',\'' . $line['time'] . '\'),';
            break;
        }
    }
    fclose($fp);
    return $Query;
}
function shutdown() {
    global $ipTV_db;
    global $identifier;
    if (!is_object($ipTV_db)) {
    } else {
        $ipTV_db->close_mysql();
    }
    @unlink($identifier);
}
