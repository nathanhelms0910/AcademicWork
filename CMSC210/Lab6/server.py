from flask import Flask, url_for, redirect, render_template, request, flash

app = Flask(__name__)
app.secret_key="student3"

@app.route("/")
def index():
	return "Hello World"

@app.route("/poll")
def pain():
	return render_template("poll.html", title="Poll")

votes = {}

@app.route("/vote", methods=["GET", "POST"])
def vote():
	if request.method == "POST":
		if "animal" in request.form:
			animal = request.form['animal']
			if not animal in votes:
				votes[animal] = 1
			else:
				votes[animal] += 1
			flash('You voted for ' + animal + '!')
	return render_template("results.html", title="Results", votes=votes)


	
app.run(host='0.0.0.0', port=6003, debug=True)
