#!/usr/bin/python3

import http.cookies
import os

def CheckSession():
	c = http.cookies.SimpleCookie(os.environ.get("HTTP_COOKIE"))
	if "username" in c:
		uname = c['username'].value
	else:
		return 0
	if "sid" in c:
	 	sid = c['sid'].value
	else:
		return 0
	sfile = open('/home/helmsna/secret/sessions', 'r')
	lines = sfile.readlines()
	sfile.close()
	for line in lines:
		pieces = line.split()
		if pieces[0] == uname and pieces[1] == sid:
			return 1
	return 0

def header(title, cookie=None):
	print('Content-Type: text/html')
	if cookie != None:
		print(cookie)
	print("")
	print("<!DOCTYPE html>")
	print("<html lang=en>")
	print("<head>")
	print("<title>" + title + "</title>")
	print("<link rel='stylesheet' href='style.css'>")
	print("<meta charset=utf-8>")
	print("</head>")
	print("<body class='background'>")

def footer():
  print("</body>")
  print("</html>")


