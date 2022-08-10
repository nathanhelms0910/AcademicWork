#!/usr/bin/python3

import cgi
import common

def main():
  form = cgi.FieldStorage()
  i = 1
  scores = []
  first_name = form.getvalue("firstname", "John")
  last_name = form.getvalue("lastname", "Doe")
  scores += [int(form.getvalue("score1", "0"))]
  scores += [int(form.getvalue("score2", "0"))]
  scores += [int(form.getvalue("score3", "0"))]
  scores += [int(form.getvalue("score4", "0"))]
  scores += [int(form.getvalue("score5", "0"))]


  maxval = scores[0]
  minval = scores[0]
  sumval = 0
  for i in scores:
    if i > maxval: 
      maxval = i
    if minval > i: 
      minval = i
  sumval = sumval + i
  avg = sumval / len(scores)

  common.header("Score Report")
  print("<h1>Name: " + first_name + " " + last_name + "</h1>")
  print("<h2>Score Report:</h2>")
  print("<p>Max Score: " + str(maxval) + "</p>")
  print("<p>Min Score: " + str(minval) + "</p>")
  print("<p>Average Score: " + str(avg) + "</p>")
  common.footer()

main()




