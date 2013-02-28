# LED fading

if /sbin/busybox [ "`/sbin/busybox grep led_fading=on $BOEFFLA_CONFIG`" ]; then

  echo "1" > /sys/class/sec/led/led_fade

  echo $(date) "LED fading normal enabled" >> $BOEFFLA_LOGFILE

fi

if /sbin/busybox [ "`/sbin/busybox grep led_fading=onbright $BOEFFLA_CONFIG`" ]; then

  echo "2" > /sys/class/sec/led/led_fade

  echo $(date) "LED fading bright enabled" >> $BOEFFLA_LOGFILE

fi

if /sbin/busybox [ "`/sbin/busybox grep led_fading=offbright $BOEFFLA_CONFIG`" ]; then

  echo "3" > /sys/class/sec/led/led_fade

  echo $(date) "LED blinking bright enabled" >> $BOEFFLA_LOGFILE

fi
