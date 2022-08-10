#!/bin/bash
#
#
# Checklog Script
#
#

echo "Enter in the username to search last log on for..."
read user
last -F | grep $user | tr -s ' ' | cut -d ' ' -f 4-8 
