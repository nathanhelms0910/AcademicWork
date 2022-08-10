import requests
import json
import random
from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def main():
	joke = {}
	return render_template("glitter.html", joke=joke)

@app.route('/grabRandom')
def program():
	response = requests.get("https://official-joke-api.appspot.com/jokes/random")
	doc = response.json()
	print(doc)
	joke = {}
	setup = doc["setup"]
	punchline = doc["punchline"]
	return render_template("glitter.html", setup=setup, punchline=punchline)

@app.route('/grabRandomKnock')
def randomKnock():
	response = requests.get("https://official-joke-api.appspot.com/jokes/knock-knock/random")
	doc = response.json()
	joke = {}
	setup = doc["setup"]
	punchline = doc["punchline"]
	return render_template("glitter.html", setup=setup, punchline=punchline)

app.run(host='0.0.0.0', port=6003, debug=True)
