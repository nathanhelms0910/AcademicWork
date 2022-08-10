#!/bin/bash
#
#
# Looping Script
#
#

echo "Listing addresses of clients..."
for command in $(cat clients.txt);
	do
       	echo $command;
	echo "Now testing $command..."
	function sshTest()
 	{
	  ssh $command "df -h"

	}
	sshTest
	done
echo "Test completed"
