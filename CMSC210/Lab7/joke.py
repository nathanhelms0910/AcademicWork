import requests
import json
import random

response = requests.get("https://official-joke-api.appspot.com/jokes/knock-knock/random")
doc = response.json()
joke = {}

for id in doc:
	setup = id["setup"]
	punchline = id["punchline"]
	joke[setup] = punchline

for key, value in joke.items():
	print(key, '\n', value)
