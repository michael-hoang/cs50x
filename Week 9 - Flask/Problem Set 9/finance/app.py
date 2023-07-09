import datetime as dt
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# My own helper functions
def get_stock_transactions(symbol: str) -> list:
    """Return all transactions for a specific stock."""
    return db.execute(
        "SELECT * FROM history WHERE user_id = ? AND symbol = ?",
        session["user_id"],
        symbol,
    )


def get_currently_owned_stocks() -> list:
    """Return a list of currently owned stocks by the user."""
    return [
        stock["symbol"]
        for stock in db.execute(
            "SELECT * FROM current_stock_ownership WHERE user_id = ? ORDER BY symbol",
            session["user_id"],
        )
    ]


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    total_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    total_portfolio_value = 0
    owned_stocks = get_currently_owned_stocks()
    portfolio = []
    for symbol in owned_stocks:
        trxs = get_stock_transactions(symbol)
        qty = 0
        for trx in trxs:
            qty += int(trx["quantity"])

        current_price = lookup(symbol)["price"]
        total_value = qty * current_price
        total_portfolio_value += total_value
        portfolio.append(
            {
                "symbol": symbol,
                "quantity": qty,
                "current_price": usd(current_price),
                "total_value": usd(total_value),
            }
        )

    return render_template(
        "index.html",
        total_cash=usd(total_cash[0]["cash"]),
        total_portfolio_value=usd(total_portfolio_value),
        portfolio=portfolio,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        try:
            price = lookup(symbol)["price"]
            shares = int(request.form.get("shares"))
        except TypeError:
            return apology(
                "Symbol not found in Yahoo Finance's database. If you believe this to be incorrect, please contact their API department at mail-api@yahooinc.com. Really appreciate it!"
            )
        except ValueError:
            # Handle decimal integers (ex. 1.0)
            shares = int(request.form.get("shares").split(".")[0])

        if shares < 1:
            return apology("Please enter a positive value for number of shares.")

        id = session["user_id"]
        cash = float(db.execute("SELECT cash FROM users WHERE id = ?", id)[0]["cash"])
        total = price * shares

        if total > cash:
            return apology("Insuffient funds. Need to deposite more cash.")
        else:
            # Execute buy order
            db.execute(
                "INSERT INTO history (symbol, quantity, price, date, user_id) VALUES (?, ?, ?, ?, ?)",
                symbol,
                shares,
                price,
                dt.datetime.now().strftime("%m/%d/%Y %H:%M:%S"),
                id,
            )
            # Update user's remaining cash balance
            remaining_cash = cash - total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, id)
            flash(
                f"You have successfully purchased {shares} share(s) of {symbol} at {usd(price)} per share. Your total cost was {usd(total)}, and your remaining cash balance is {usd(remaining_cash)}."
            )

            # Add symbol to the current_stock_ownership table, if not already
            stocks_list = [
                stock["symbol"]
                for stock in db.execute(
                    "SELECT * FROM current_stock_ownership WHERE user_id = ? ORDER BY symbol",
                    id,
                )
            ]
            if symbol not in stocks_list:
                db.execute(
                    "INSERT INTO current_stock_ownership (user_id, symbol) VALUES (?, ?)",
                    id,
                    symbol,
                )

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if not stock:
            return render_template(
                "quoted.html", price="Make sure symbol is correct.", symbol="N/A"
            )
        return render_template(
            "quoted.html",
            price=(usd(stock["price"]) + " per share"),
            symbol=stock["symbol"],
        )

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """
    Register user
    Note: Clicking "Register" at the top left makes a "GET" request, since we are just requesting for the register.html template.
    Clicking on the "Register" button on the register.html template makes a "POST" request since we are trying to 'post' or send
    data to the server. In this register method, we only need to check if the user is making a "POST" request and then query the
    the database. Otherwise, the method will direct the user via "GET" to the register.html template.
    """
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password").strip()
        pw_confirm = request.form.get("confirmation").strip()
        # Ensure all three input fields (Username, Password, and Confirm Password) are not empty. (2nd layer validiation in the backend)
        if not username or not password or not pw_confirm:
            return apology("Do not leave any blank fields.")
        # Ensure password confirmation is the same as password.
        if password != pw_confirm:
            return apology("Password confirmation non-match.")
        # Ensure username does not exist.
        if db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username is already registered.")
        # Store username and password hash in database, and then flash successful registration message to user at login.html.
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        flash(
            "Thank you for registering an account with C$50 Finance. Please log in to continue."
        )
        return render_template("login.html")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        try:
            price = lookup(symbol)["price"]
            shares = int(request.form.get("shares"))
        except TypeError:
            return apology(
                "Symbol not found in Yahoo Finance's database. If you believe this to be incorrect, please contact their API department at mail-api@yahooinc.com. Really appreciate it!"
            )
        except ValueError:
            # Handle decimal integers (ex. 1.0)
            shares = int(request.form.get("shares").split(".")[0])

        if shares < 1:
            return apology("Please enter a positive value for number of shares.")
        if symbol not in get_currently_owned_stocks():
            return apology(f"You do not have any shares of {symbol}.")

        avail_shares = db.execute(
            "SELECT SUM(quantity) AS avail_shares FROM history WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            symbol,
        )
        if avail_shares[0]["avail_shares"] < shares:
            return apology(f"You do not have enough shares of {symbol}.")

        total_return = price * shares
        # Record sell transaction in history table
        db.execute(
            "INSERT INTO history (symbol, quantity, price, date, user_id) VALUES (?, ?, ?, ?, ?)",
            symbol,
            -shares,
            price,
            dt.datetime.now().strftime("%m/%d/%Y %H:%M:%S"),
            session["user_id"],
        )
        # Update user cash
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            total_return,
            session["user_id"],
        )
        # Remove symbol from current_stock_ownership table if user sells all avail_shares
        if avail_shares[0]["avail_shares"] == shares:
            db.execute(
                "DELETE FROM current_stock_ownership WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                symbol,
            )

        remaining_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        flash(
            f"You have successfully sold {shares} share(s) of {symbol} at {usd(price)} per share. Your total return was {usd(total_return)}, and your updated cash balance is {usd(remaining_cash[0]['cash'])}."
        )

    return render_template("sell.html")


if __name__ == "__main__":
    app.run(debug=True)
