#!/usr/bin/python3

def header(title):
	print('Content-Type: text/html')
	print("")
	print("<!DOCTYPE html>")
	print("<html lang=en>")
	print("<head>")
	print("<title>" + title + "</title>")
	print("<meta charset=utf-8>")
	print("</head>")
	print("<body>")

def footer():
  print("</body>")
  print("</html>")


