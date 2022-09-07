from flask import Flask, request, url_for, render_template
from itlives import MoveDamnYou 

app = Flask(__name__)

@app.route("/")
def home():
  return render_template("index.html");

@app.route("/itlives", methods=["POST"])
def runmotor():
	print("Motor activated");
	motor = MoveDamnYou(22, 27, 17, 18)
	motor.clockwise(5.0/1000, 512)

if __name__ == "__main__":
	app.run()
