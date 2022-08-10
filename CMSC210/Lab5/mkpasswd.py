#!/usr/bin/python3

from hashlib import sha1

cipher = sha1()
passFile = open("/home/helmsna/secret/passwords", "a")

print('Please enter a username: ')
name = input()
passFile.write(name)
passFile.write("    ")

print('Please enter a password: ')
passwd = input()

cipher.update(passwd.encode())
hash = cipher.hexdigest()
passFile.write(hash)
passFile.write("\r\n")

print('The username is ', name)
print('The encrypted password is: ', hash)
passFile.close()

