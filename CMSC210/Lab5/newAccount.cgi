#!/usr/bin/python3

import cgi
import common
from hashlib import sha1

def main():
	cipher = sha1()
	form = cgi.FieldStorage()
	user = form.getvalue("newUsername", "user")
	passwd = form.getvalue("newPasswd", "passwd")
	passFile = open("/home/helmsna/secret/passwords", "a")

	passFile.write(user)
	passFile.write("    ")

	cipher.update(passwd.encode())
	hash = cipher.hexdigest()
	passFile.write(hash)
	passFile.write("\r\n")
	passFile.close()

	common.header("Account Created")
	print("<h1>Account Created</h1>")
	print("<h2>You can now return to the Login Screen <a href='login.html'>here</a> to continue</h2>")
	common.footer()

main()
