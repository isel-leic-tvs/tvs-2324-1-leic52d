#!/bin/bash

if [ $UID != 0 ] ; then
	echo "must be called as superuser"
	exit 1
fi

ECHOD=echod
ECHOD_DIR=/opt/$ECHOD
SYSTD_DIR=/etc/systemd/system
 
if [ ! -d $ECHOD_DIR ]; then
	echo "inexistent $ECHOD_DIR"
	exit
fi	


#terminate server if active

if systemctl is-active $ECHOD ; then
	systemctl stop $ECHOD
fi	
systemctl disable echod

rm -rf $ECHOD_DIR
rm -f  $SYSTD_DIR/$ECHOD.service  

  
echo echod uninstall done!

