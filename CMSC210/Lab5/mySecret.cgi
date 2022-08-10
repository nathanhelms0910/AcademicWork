#!/usr/bin/python3
import cgi
import common

def main():
  common.header("Secret Page")
  print("<p>You did it!</p>")
  common.footer()

main()

