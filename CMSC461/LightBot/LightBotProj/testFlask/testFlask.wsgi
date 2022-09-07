#!/usr/bin/python

import logging
import sys
sys.path.insert(0, '/home/pi/LightBotProj/testFlask')
from testFlask import app as application
application.secret_key = 'anything'

