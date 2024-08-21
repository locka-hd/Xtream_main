#!/bin/sh

SCRIPT=/home/xtreamcodes
USER=$(whoami)

if [ $USER != "root" ]]; then
  echo "Please run as root!"
  exit 0
fi

start() {
  pids=$(pgrep -u xtreamcodes nginx | wc -l)
  if [ $pids != 0 ]; then
    echo 'XtreamCodes is already running'
    return 1
  fi
  echo 'Starting XtreamCodes...'
  sudo chown -R xtreamcodes:xtreamcodes /sys/class/net
  sudo chown -R xtreamcodes:xtreamcodes $SCRIPT/content/streams
  sudo chown -R xtreamcodes:xtreamcodes $SCRIPT/tmp
  sudo -u xtreamcodes $SCRIPT/bin/nginx/sbin/nginx >/dev/null 2>/dev/null
  sudo -u xtreamcodes $SCRIPT/bin/nginx_rtmp/sbin/nginx_rtmp >/dev/null 2>/dev/null
  sudo -u xtreamcodes $SCRIPT/bin/daemons.sh
  sudo $SCRIPT/bin/php/bin/php $SCRIPT/tools/startup.php
  sudo -u xtreamcodes $SCRIPT/bin/php/bin/php $SCRIPT/tools/signals.php >/dev/null 2>/dev/null &
  sudo -u xtreamcodes $SCRIPT/bin/php/bin/php $SCRIPT/tools/watchdog.php >/dev/null 2>/dev/null &
  echo 'Running in foreground...'
}


stop() {
  pids=$(pgrep -u xtreamcodes nginx | wc -l)
  if [ $pids = 0 ]; then
    echo 'XtreamCodes is not running'
    return 1
  fi
  echo 'Stopping XtreamCodes...'
  sudo killall -u xtreamcodes
  sleep 1
  sudo killall -u xtreamcodes
  sleep 1
  sudo killall -u xtreamcodes
}

restart() {
  ps -U xtreamcodes | egrep -v "ffmpeg|PID" | awk '{print $1}' | xargs kill -9
  start
}

reload() {
  pids=$(pgrep -u xtreamcodes nginx | wc -l)
  if [ $pids = 0 ]]; then
    echo 'XtreamCodes is not running'
    return 1
  fi
  echo 'Reloading XtreamCodes...'
  sudo -u xtreamcodes $SCRIPT/bin/nginx/sbin/nginx -s reload
  sudo -u xtreamcodes $SCRIPT/bin/nginx_rtmp/sbin/nginx_rtmp -s reload
}

case "$1" in
  start)
    start
    ;;
  stop)
    stop
    ;;
  reload)
    reload
    ;;
  restart)
    restart
    ;;
  *)
    echo "Usage: $0 {start|stop|restart|reload}"
esac

exit 0
