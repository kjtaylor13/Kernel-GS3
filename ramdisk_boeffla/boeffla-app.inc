# Versions of apps bundled with this kernel
VERSION_TWEAKS="bk_v001"
VERSION_DIALOG="bk_v001"

# Uninstall boeffla-tweak and dialog helper apps that might still be installed in system/app
if [ -f /system/app/BoefflaTweaks.apk ]; then
	/sbin/busybox mount -o remount,rw -t ext4 $SYSTEM_DEVICE /system
	/sbin/busybox rm /system/app/BoefflaTweaks.apk
	/sbin/busybox mount -o remount,ro -t ext4 $SYSTEM_DEVICE /system
	echo $(date) Old Boeffla tweaks app removed from system/app folder >> $BOEFFLA_LOGFILE
fi

if [ -f /system/app/BoefflaTweaksDialogHelper.apk ]; then
	/sbin/busybox mount -o remount,rw -t ext4 $SYSTEM_DEVICE /system
	/sbin/busybox rm /system/app/BoefflaTweaksDialogHelper.apk
	/sbin/busybox mount -o remount,ro -t ext4 $SYSTEM_DEVICE /system
	echo $(date) Old Boeffla dialog app removed from system/app folder >> $BOEFFLA_LOGFILE
fi


# Depending on the config setting, boeffla tweaks and boeffla dialog apps
# get installed/upgraded or uninstalled

if /sbin/busybox [ "`/sbin/busybox grep boeffla_app=off $BOEFFLA_CONFIG`" ]; then

	# If app is installed, uninstall it now and delete all config scripts
	STATUS=`/system/bin/pm path bo.boeffla`
	if [ ! -z $STATUS ]; then
		/system/bin/pm uninstall bo.boeffla

		/sbin/busybox mount -o remount,rw -t ext4 $SYSTEM_DEVICE /system
		/sbin/busybox rm /system/etc/init.d/*_bk*
		/sbin/busybox rm /system/etc/init.d/*_???bk*
		/sbin/busybox mount -o remount,ro -t ext4 $SYSTEM_DEVICE /system

		/sbin/busybox rm /data/boeffla-*

		echo $(date) Boeffla tweaks app uninstalled and settings deleted >> $BOEFFLA_LOGFILE
	fi

	# If dialog app is installed, uninstall it now
	STATUS=`/system/bin/pm path bo.boeffla.tweaks.dialog.helper`
	if [ ! -z $STATUS ]; then
		/system/bin/pm uninstall bo.boeffla.tweaks.dialog.helper
		echo $(date) Boeffla dialog app uninstalled >> $BOEFFLA_LOGFILE
	fi

else

	# if no or old version of tweaks app is installed, install/upgrade now
	if ! [ "`/sbin/busybox grep $VERSION_TWEAKS /data/app/bo.boeffla-*.apk`" ] ; then
		/system/bin/pm install -r /res/app/BoefflaTweaks.apk
		echo $(date) Boeffla tweaks app $VERSION_TWEAKS installed/updated >> $BOEFFLA_LOGFILE
	fi

	# if no or old version of dialog app is installed, install/upgrade now
	if ! [ "`/sbin/busybox grep $VERSION_DIALOG /data/app/bo.boeffla.tweaks.dialog.helper-*.apk`" ] ; then
		/system/bin/pm install -r /res/app/BoefflaTweaksDialogHelper.apk
		echo $(date) Boeffla dialog app $VERSION_DIALOG installed/updated >> $BOEFFLA_LOGFILE
	fi

fi


# TEMPORARY CLEANUP, TO BE REMOVED AFTER A WHILE

# Move scripts from old script pack folder to new one if old folder exists

if [ -d /sdcard/BoefflaScripts ] ; then
	/sbin/busybox mkdir /sdcard/boeffla-kernel-data/ScriptPacks
	/sbin/busybox mv /sdcard/BoefflaScripts/* /sdcard/boeffla-kernel-data/ScriptPacks
	/sbin/busybox rm -rf /sdcard/BoefflaScripts
fi

# Delete old version file used before grepping the version out
/sbin/busybox rm /data/boeffla-appversion
