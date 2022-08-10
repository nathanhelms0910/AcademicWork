from flask import Flask, render_template, request
import json
import sqlite3 as sql

app = Flask(__name__)
messages = [ ("Bot 1", "Greeting", "Hello World"), ("Bot 2", "Departure", "Goodbye World") ]


@app.route("/")
def main():
	return render_template("messages.html")

@app.route("/messages")
def get_messages():
	db = sql.connect("chat.db")
	cur = db.cursor()
	cur.execute("SELECT username, topic, message FROM messages")
	rows = cur.fetchall()
	cur.close()
	db.close()
	return json.dumps(rows)

@app.route("/add_message", methods=["POST"])
def add_message():
	global messages
	file = open('/home/helmsna/public_html/Lab8/authusers', 'r')
	lines = file.readlines()
	file.close()
	if "username" in request.form and "message" in request.form and "topic" in request.form:
		username = request.form["username"]
		message = request.form["message"]
		topic = request.form["topic"]
	else:
		return "No message found"

	for line in lines:
		pieces = line.split()
		print(pieces)
		if "username" in request.form and request.form["username"] == pieces[0]:  
				db = sql.connect("chat.db")
				cur = db.cursor()
				cur.execute("INSERT INTO messages(username, topic, message) VALUES (?, ?, ?)", (username, topic, message))
				db.commit()
				cur.close()
				db.close()
				return "Submitted"
	return "No message found"

@app.route("/add_auth_user", methods=["POST"])
def add_user():
	new_user = request.form["newuser"]
	if new_user.isalnum():
		authFile = open('/home/helmsna/public_html/Lab8/authusers', 'a')
		authFile.write(new_user + "\n")
		authFile.close()
		return "Added"
	else:
		return "No user submitted"

		
app.run(host="0.0.0.0", port=6003)
