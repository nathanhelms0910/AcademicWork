#!/usr/bin/python3

import cgi
import common

def main():
  form = cgi.FieldStorage()

  verb_b = form.getvalue("verb2", "drive")
  noun_a = form.getvalue("noun1", "Zavala")
  noun_b = form.getvalue("noun2", "Cabal")
  noun_c = form.getvalue("noun3", "Cabal war on mars")
  noun_d = form.getvalue("noun4", "Brachus Zahn")
  noun_e = form.getvalue("noun5", "Hive")
  adj_a = form.getvalue("adjective1", "ugly")
  adj_b = form.getvalue("adjective2", "red")
  adj_c = form.getvalue("adjective3", "angry")
  pronoun_a = form.getvalue("pronoun1", "He")
  pronoun_b = form.getvalue("pronoun2", "their")
  adverb = form.getvalue("adverb", "knew")
  adverb_b = form.getvalue("adverb2", "landed")
  plural_noun = form.getvalue("plural", "glimmer piles")
  

  common.header("Mad Libs Generation")
  print("<h1>Mad Libs Generation</h1>")
  print("<p>There once was a person named " + noun_a + ". " + pronoun_a + " lived in a town in the middle of nowhere.</p>")
  print("<p>The town was always crawling with " + adj_a + " " + noun_b + "s.</p>")
  print("<p>Luckily for " + noun_a + ", whom " + adverb + " about the " + noun_b + "'s motive, decided to " + verb_b + " to " + noun_b + "'s warehouse.</p>")
  print("<p>After making it to the " + adj_b + " warehouse, where " + noun_b + " did " + pronoun_b + " criminal acts, there was a sign up above.</p>")
  print("<p>" + noun_c + " was what the sign said. When " + noun_a + " entered the warehouse, " + pronoun_a + " was met with a man named " + noun_d + "</p>")
  print("<p>'FOOLS!' proclaimed " + noun_d + ". 'You have walked straight into my trap! Prepare to face the pit of " + adj_c + " " + noun_e + "!'</p>")
  print("<p>In response to " + noun_d + "'s threat, " + noun_a + " made a leap of faith and " + adverb_b + " on top of " + noun_d + "'s head like a Mario villain. " + noun_d + " then was killed and " + noun_a + " had won all of the " + plural_noun + " that " + pronoun_a + " had ever wanted. The End.</p>")
  common.footer()

main()
