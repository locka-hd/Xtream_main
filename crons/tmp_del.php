<?php
if ($argc) {
    $cache_playlists = 60;

    set_time_limit(0);
    require str_replace('\\', '/', dirname($argv[0])) . '/../wwwdir/init.php';
    cli_set_process_title('XtreamCodes[TMP Cleaner]');
    $unique_id = TMP_DIR . md5(UniqueID() . __FILE__);
    ipTV_lib::check_cron($unique_id);
    foreach (array(TMP_DIR, DIVERGENCE_TMP_PATH, FLOOD_TMP_PATH, STALKER_TMP_PATH, LOGS_TMP_PATH) as $tmpPath) {
        foreach (scandir($tmpPath) as $file) {
            if (600 <= time() - filemtime($tmpPath . $file) && stripos($file, 'stalker_') === false) {
                if (is_file($tmpPath . $file)) {
                    unlink($tmpPath . $file);
                }
            }
        }
    }
    foreach (scandir(PLAYLIST_PATH) as $file) {
        if ($cache_playlists < time() - filemtime(PLAYLIST_PATH . $file)) {
            if (is_file(PLAYLIST_PATH . $file)) {
                unlink(PLAYLIST_PATH . $file);
            }
        }
    }
    clearstatcache();
    @unlink($unique_id);
} else {
    exit(0);
}
