import sqlite3 as sql
from flask import Flask, render_template, request
app = Flask(__name__)


@app.route('/')
def homePage():
	return render_template("index.html")

@app.route('/recipelist')
def returnList():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes")
	rows = cur.fetchall();
	return render_template("recipelist.html", rows = rows)



@app.route('/ingredientslist')
def returnIngredients():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM ingredients")
	rows = cur.fetchall();
	return render_template("ingredientslist.html", rows = rows)

@app.route('/breakfastrecipes')
def returnBekfast():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes WHERE recipeType = 'Breakfast'")
	rows = cur.fetchall();
	return render_template("bekfast.html", rows = rows)

@app.route('/lunchrecipes')
def returnLunch():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes WHERE recipeType = 'Lunch'")
	rows = cur.fetchall();
	return render_template("lunch.html", rows = rows)
	

@app.route('/dinnerrecipes')
def returnDinner():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes WHERE recipeType = 'Dinner'")
	rows = cur.fetchall();
	return render_template("dinnerbone.html", rows = rows)

@app.route('/snackrecipes')
def returnSnacks():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes WHERE recipeType = 'Snacks'")
	rows = cur.fetchall();
	return render_template("snacks.html", rows = rows)

@app.route('/dessertrecipes')
def returnDesserts():
	db = sql.connect('recipes.db')
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipes WHERE recipeType = 'Dessert'")
	rows = cur.fetchall();
	return render_template("desserts.html", rows = rows)

@app.route('/<recipeID>')
def returnRecipe(recipeID):
	db = sql.connect('recipes.db')
	par = (recipeID,)
	db.row_factory = sql.Row
	cur = db.cursor()
	cur.execute("SELECT * FROM recipeInfo WHERE recipeID = ?", par)
	rows = cur.fetchall();

	cur.execute("SELECT * FROM ingredients WHERE recipeID = ?", par)
	ing = cur.fetchall();

	cur.execute("SELECT * FROM instructions WHERE recipeID = ?", par)
	inst = cur.fetchall();

	cur.execute("SELECT * FROM equipment WHERE recipeID = ?", par)
	equip = cur.fetchall();

	return render_template("recipe.html", rows = rows, ing = ing, inst = inst, equip = equip)

if __name__ == '__main__':
	app.run(host="0.0.0.0", port=6003, debug=True)
