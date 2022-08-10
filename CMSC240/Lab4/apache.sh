#!/bin/bash
#
#
# Apache Script
#
#
#

FILENAME=$1
if [ "x$FILENAME" == "x" ]
then
  echo "Filename not found"
else
  sed -i.bak "/^ServerRoot/s/httpd/www/g" $FILENAME
fi
