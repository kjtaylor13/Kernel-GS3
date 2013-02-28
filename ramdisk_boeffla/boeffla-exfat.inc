# load exfat drivers if not configured to off in boeffla config file or via boeffla tweaks app

if [ ! "`/sbin/busybox grep exfat=off $BOEFFLA_CONFIG`" ] && [ ! -f /data/boeffla-exfat ]; then
  /sbin/busybox insmod /lib/modules/exfat_core.ko
  /sbin/busybox insmod /lib/modules/exfat_fs.ko
fi
