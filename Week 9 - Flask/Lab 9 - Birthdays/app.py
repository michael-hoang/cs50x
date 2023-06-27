import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
            name,
            month,
            day,
        )
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        all_birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", all_birthdays=all_birthdays)


@app.route("/confirm-delete", methods=["POST"])
def confirm_delete():
    id = request.form.get("id")
    birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
    return render_template("delete.html", birthday=birthday)


@app.route("/delete", methods=["GET", "POST"])
def delete():
    if request.method == "POST":
        id = request.form.get("id")
        db.execute("DELETE FROM birthdays WHERE ID = ?", id)

    return redirect("/")


@app.route("/confirm-edit", methods=["POST"])
def confirm_edit():
    id = request.form.get("id")
    birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
    return render_template("edit.html", birthday=birthday)


@app.route("/edit", methods=["GET", "POST"])
def edit():
    if request.method == "POST":
        id = request.form.get("id")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if name:
            db.execute("UPDATE birthdays SET name = ? WHERE id = ?", name, id)
        if month:
            db.execute("UPDATE birthdays SET month = ? WHERE id = ?", month, id)
        if day:
            db.execute("UPDATE birthdays SET day = ? WHERE id = ?", day, id)

    return redirect("/")


if __name__ == "__main__":
    app.run(debug=True)
