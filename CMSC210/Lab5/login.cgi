#!/usr/bin/python3

import http.cookies
import random
import cgi
import common
import hashlib

def MakeCookie(username):
	c = http.cookies.SimpleCookie()
	c["username"] = username
	sid = ""
	for i in range(0,128):
		sid += random.choice("0123456789abcdefghijklmnopqrstuvwxyz")
	c["sid"] = sid
	file = open('/home/helmsna/secret/sessions', 'a')
	file.write(username + '\t' + sid + '\n')
	file.close()
	return c

def payload(username):
	cookie = MakeCookie(username)
	common.header("Login Page", cookie)
	print("<img class='sizeadjust' src='confetti.png' alt='Confetti Image'>")
	print("<h1>Login Accepted</h1>")
	print("<h3>This is a link to the <a href=mySecret.cgi>page</a></h3>")

	common.footer()


def sorry():
	common.header("Sorry!")
	print("<div class='divBack'>")
	print("<h1>Sorry! Access Denied</h1>")
	print("<a href=login.html>Return to login screen</a>")
	print("</div>")
	common.footer()


def CheckPassword():
	form = cgi.FieldStorage()
	if "username" in form and "password" in form:
		username = form['username'].value
		password = form['password'].value
		file = open('/home/helmsna/secret/passwords', 'r')
		lines = file.readlines()
		file.close()
		m = hashlib.sha1()
		m.update(password.encode())
		hex = m.hexdigest()
		for line in lines:
			pieces = line.split()
			if username == pieces[0] and hex == pieces[1]:
				payload(username)
				return
	sorry()
	return

CheckPassword()
