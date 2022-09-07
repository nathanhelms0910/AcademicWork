#pretty much everything in here is based on work by Arpan Neupane:
#https://www.youtube.com/watch?v=71EU8gnZqZQ
from flask import *
from flask_sqlalchemy import SQLAlchemy
from flask_login import UserMixin
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import InputRequired, Length, ValidationError
from flask_bcrypt import Bcrypt

#Flask shenanigans
app = Flask(__name__)
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
app.config['SECRET_KEY'] = '4c4d498b84202fa0ae1087e42f20379f7509261ccfebcc0146497d7d116206ec'

#login_manager = LoginManager()
#login_manager.init_app(app)

#@login_manager.user_loader
#def load_user(user_id):
 #   return User.get(user_id)

#Class for database fields
class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(30), nullable=False, unique=True)
    password = db.Column(db.String(80), nullable=False)
#form for registering new users
class RegisterForm(FlaskForm):
    username = StringField(validators=[InputRequired(), Length(
        min=4, max=20)], render_kw={"userplaceholder": "Username"})
    password = PasswordField(validators=[InputRequired(), Length(
        min=4, max=20)], render_kw={"passplaceholder": "Password"})        
    submit = SubmitField("Register")
#validates by checking database for username, if there is another of the same, shoo them away
    def validate_username(self, username):
        existing_user_username = User.query.filter_by(
                username=username.data).first()
        if existing_user_username:
            raise ValidationError("Username already in use.")

#form for logging in registered users
class LoginForm(FlaskForm):
    username = StringField(validators=[InputRequired(), Length(
        min=4, max=20)], render_kw={"userplaceholder": "Username"})
    password = PasswordField(validators=[InputRequired(), Length(
        min=4, max=20)], render_kw={"passplaceholder": "Password"})        
    submit = SubmitField("Login")

#Landing page
@app.route("/", methods =["GET", "POST"])
def home():
    return render_template('home.html')
#Login page
@app.route('/login')
def login():
    form = LoginForm()
    return render_template('login.html', form=form)
#registration page
@app.route("/register", methods =["GET", "POST"])
def register():
    form = RegisterForm()

    if(form.validate_on_submit()): 
        #This takes the input from the registration form and then hashes the password
        #and then throws that junk into the database.
        #TODO READ ONLY DATABASE? WHY?
        hashed_pword = bcrypt.generate_password_hash(form.password.data)
        new_user = User(username=form.username.data, password=hashed_pword)
        db.session.add(new_user)
        db.session.commit()
        return redirect('http://lights.cs.longwood.edu/login')
    return render_template('register.html', form=form)

if __name__ == "__main__":
    app.run(debug=True)
