from flask import Flask, url_for, redirect, render_template, request, flash

app = Flask(__name__)
app.secret_key = "student3"

points = 0
health = 100
strength = 0
items = {}

@app.route("/")
def index():
	return render_template("index.html")

@app.route("/instructions")
def instruct():
	return render_template("instructions.html")

@app.route("/room/1")
def room1():
	room = "Entrance"
	rooms = {'Left Path' : '/room/2', 'Right Path' : '/room/3'}
	desc = """You enter the maze and see a lantern sitting on a crate. You pick up the lantern to keep a light on you for the dark corridors. Where do you go next?"""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/2")
def room2():
	global items
	global health
	global strength
	if not 'Lantern' in items :
		items['Lantern'] = 1
	room = "Bat Attack!"
	health = health - 15
	strength = strength + 20
	rooms = {'Left Path' : '/room/4', 'Forward' : '/room/5', 'Right Path' : '/room/6', 'Go Back' : '/room/1'}
	desc = """You enter the dark corridor, thankfully you grabbed that lantern. However, despite the increased visibility, you could not see the swarm of bats hanging right above you before they dived down on you. You lose 15 health, although you endure it, gaining 20 strength."""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)


@app.route("/room/3")
def room3():
	global items
	global strength
	global points
	if not "Lantern" in items :
		items['Lantern'] = 1
	room = "A blocked path..."
	check = 0
	for item in items.keys() :
		if item == "Pickaxe":
			check = 1
			break
	if check == 1 :
		room = "A way through the rubble.."
		rooms = {'Through the Rubble' : '/room/10', 'Go Back' : '/room/1'}
		desc = """With your new pickaxe, there seems to be a way through the rocks ahead. You use the pickaxe, breaking the rocks and gaining some points and strength at the same time! Do you proceed through the new opening?"""
		strength = strength + 15
		points = points + 25
	else :
		room = "A blocked path.."
		rooms = {'Go Back' : 'localhost:6003/room/1'}
		desc = """You see a large pile of rocks and boulders ahead of you. You currently do not have the physical means to cross this obstacle"""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/4")
def room4():
	room = "A long corridor ahead"
	rooms = {'Continue to Other Side' : '/room/7', 'Enter Side Hallway' : '/room/8', 'Go Back' : '/room/2'}
	desc = """You enter a long hallway with seemingly one way through, however you notice a faint light coming from a side corridor. Where do you go next?"""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/5")
def room5():
	global health
	global strength
	global points
	room = "Dead End... but.."
	rooms = {'Go Back' : '/room/2'}
	desc = """Upon entering the room you notice it is dead end. However, you see an item in the corner of the room. Upon further inspection, the item disappears, granting you bonus health, strength, and points! A great find! However it doesn't get you closer to the end. Might as well turn around"""
	health = health + 30
	strength = strength + 15
	points = points + 20
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/6")
def room6():
	room = "Strength Test"
	if strength == 50 :
		rooms = {'Brute Force' : '/room/9', 'Go Back' : '/room/2'}
		desc = """There seems to be a path forward, but only if you're strong enough to push your way through... You seem up to the task to do so."""
	else :
		rooms = {'Go Back' : '/room/2'}
		desc = """There seems to be a path forward, but only if you're strong enough to push your way through... You currently do not seem up to this task.."""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/7")
def room7():
	global items
	global points
	room = "A useful tool"
	rooms = {'Go Back' : '/room/4'}
	desc = """Upon crossing the hallway, you see a pickaxe sticking out of a stone, with similar nature to Excalibur. You reach to lift it out of the stone, and it releases with a lot less effort than expected. You decide to keep it on you. Perhaps it can be useful to keep around..."""
	points = points + 40
	if not "Pickaxe" in items :
		items["Pickaxe"] = 1
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/8")
def room8():
	global health
	global strength
	room = "An unfortunate end.."
	rooms  = {'Restart' : '/'}
	health = 0;
	strength = 0;
	desc = """Upon entering the room, the door shuts behind you, sealing you inside.. with a giant monster. Unfortunately the monster is too strong for you to ever overcome and you meet a quick end"""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/9")
def room9():
	room = "An exit!"
	rooms = {'Play Again' : '/'}
	desc = """You have survived the maze! Congrats! Click below if you want to retry and find the other exit..."""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

@app.route("/room/10")
def room10():
	room = "An old but suitable exit"
	rooms = {'Play Again' : '/'}
	desc = """After escaping the maze through the hidden passage, you realize you just pulled a book out of Minecraft to win... wow. There was another exit and everything and yet you decided this path? Why don't you go back and find it."""
	return render_template("room.html", rooms = rooms, inv = items, name = room, desc = desc, hp = health, st = strength, score = points)

if __name__ == '__main__':
	app.run(host="0.0.0.0", port=6003, debug=True)
