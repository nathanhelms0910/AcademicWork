#!/bin/bash
#
#
#
#


for file in $(ls);
  do
  touch $file;
  echo "touched $file"
  done

