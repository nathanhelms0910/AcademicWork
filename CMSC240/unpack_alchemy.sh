#!/bin/bash
#
# unpack_alchemy.sh
# A script by Nathan Helms
#
#Create Variables
URL=https://pypi.python.org/packages/source/S/SQLAlchemy-0.8.0.tar.gz
FNAME=$(echo $URL | cut -d/ -f8)
DIR=$(echo $FNAME | sed 's/.tar.gz$//g')
LOGFILE="/home/nathan/install.log"

#change directory to install directory
cd /scratch/nathan

#if the file exists, print File Exists. If not, download the file
if [ -f $FNAME ]; then
	 echo "File Exists"
else
	echo Downloading File...
	wget $URL >& /dev/null
fi

#Unpack the archive with tar
echo Unpacking Archive...
tar xf "$FNAME"

echo "Ready to install Alchemy. Continue? (y/n)"
read con

if [ con == "y" ]; then
	echo Installing SQLAlchemy...
	cd "/scratch/nathan/$DIR" && python setup.py install
	echo "Installed SQLAlchemy: $FNAME $(date)" >> $LOGFILE
else
	echo Installation Cancelled
fi

