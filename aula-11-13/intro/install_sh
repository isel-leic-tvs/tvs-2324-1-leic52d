#!/bin/bash

SYSD_DIR=/etc/systemd/system

enabling=0

if [ $# == 1 ] ; then
	if [ $1 != "-e" ] ; then 
		echo 'usage: install [-e]'
	else
		enabling=1
	fi
fi

cp a.service b.service test.target $SYSD_DIR 
systemctl daemon-reload

if [ $enabling == 1 ] ; then
	systemctl enable a b
fi




		
		
	
