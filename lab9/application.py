import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

MONTHS = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        print(name)
        print(month)
        print(day)
        query = 'INSERT INTO birthdays (name, month, day) VALUES("{}", "{}", "{}")'.format(name, month, day)
        if int(month) < 1 or int(month) > 12 or int(day) < 1 or int(day) > 31:
            print("PROBLEM")
            return redirect("/")
        db.execute(query)
        return redirect("/")

    else:
        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


