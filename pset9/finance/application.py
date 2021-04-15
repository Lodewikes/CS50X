import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # TODO
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id=?", session.get("user_id"))[0]["cash"]
    shares = db.execute("SELECT symbol, name, shares FROM shares WHERE user_pk=? AND shares!=0", session.get("user_id"))
    total_share_value = 0
    for share in shares:
        x = lookup(share["symbol"])
        share["price"] = x["price"]
        print(share)
        total_share_value = total_share_value + (share["price"] * share["shares"])
    return render_template("index.html", cash=cash, shares=shares, shares_val=total_share_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # TODO
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            message = "You must select a valid share symbol."
            id = "message"
            return render_template("buy.html", message=message, id=id), 400

        # lookup() the symbol
        quote = lookup(request.form.get("symbol"))

        if quote is None:
            message = "You must select a valid share symbol."
            id = "message"
            return render_template("buy.html", message=message, id=id), 400
        else:
            # request the number of shares
            shares = request.form.get("shares")
            if not isinstance(shares, (int)) or shares < 0:
                message = "invalid number of shares selected"
                id = "message"
                return render_template("buy.html", id=id, message=message), 400
            price = float(shares) * quote["price"]
            # check if user has enough cash available
            user_balance = db.execute("SELECT cash FROM users WHERE id=?", session.get("user_id"))[0]["cash"]
            if price > user_balance:
                message = "Insufficient Funds."
                id = "insufficientMessage"
                return render_template("buy.html", message=message, id=id), 400
            elif price < user_balance:
                user_balance -= price
                timestamp = str(datetime.datetime.now())
                # insert name, name_pk, symbol, shares into shares
                existSymbol = db.execute("SELECT symbol FROM shares WHERE symbol=? AND user_pk=?",
                                         quote["symbol"],
                                         session.get("user_id"))
                username = db.execute("SELECT username FROM users WHERE id=?", session.get("user_id"))[0]["username"]
                print(username)

                if existSymbol:
                    if existSymbol[0]["symbol"] == quote["symbol"]:
                        current_shares = db.execute("SELECT shares.shares FROM shares WHERE shares.symbol=?",
                                                    quote["symbol"])[0]["shares"]
                        new_shares = current_shares + int(shares)
                        db.execute("UPDATE shares SET shares=? WHERE symbol=? AND user_pk=?",
                                   new_shares,
                                   quote["symbol"],
                                   session.get("user_id")
                                   )
                elif not existSymbol:
                    print(existSymbol)
                    print(quote["symbol"])
                    db.execute("INSERT INTO shares (user, user_pk, symbol, name, shares) VALUES(?, ?, ?, ?, ?)",
                               username,
                               session.get("user_id"),
                               quote["symbol"],
                               quote["name"],
                               shares
                               )

                # TODO insert name, name_pk, date, time, symbol, +-shares, price/share into history
                db.execute("INSERT INTO history (user, user_pk, timestamp, symbol, delta_shares, price_share)"
                           " VALUES(?, ?, ?, ?, ?, ?)",
                           username,
                           session.get("user_id"),
                           timestamp,
                           quote["symbol"],
                           shares,
                           quote["price"]
                           )
                # insert new cash balance into user
                db.execute("UPDATE users SET cash=? WHERE id=?", user_balance, session.get("user_id"))
            return redirect("/")
        # git commit
    return render_template("buy.html", id="message")


@app.route("/history")
@login_required
def history():
    # TODO
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM history WHERE user_pk=?", session.get("user_id"))
    return render_template("history.html", trans=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    # TODO add a graph perhaps
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            message="please enter a symbol"
            return render_template("quote.html", message=message), 400
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote is None:
            message = "No such stock available."
            return render_template("quote.html", message=message), 400
        else:
            return render_template("quoted.html", message="", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # check if entered a username and password
        if not request.form.get("username") and not request.form.get("password"):
            message = "please supply a username and a password."
            return render_template("register.html", message=message), 400
        # check if entered a username
        if not request.form.get("username"):
            message = "Please supply a username."
            return render_template("register.html", message=message), 400
        # check if already existing username
        db_name = db.execute("SELECT users.username FROM users WHERE users.username='" +
                             request.form.get("username") + "'")
        if db_name:
            if db_name[0]["username"] == request.form.get("username"):
                message = "Username exists already."
                return render_template("register.html", message=message), 400
        elif not db_name:
            # check if entered a password
            if not request.form.get("password"):
                message = "Please supply a password."
                return render_template("register.html", message=message), 400
            # check if entered a matching confirmation password
            if request.form.get("password") != request.form.get("confirmation"):
                message = "Passwords must match."
                return render_template("register.html", message=message), 400
            password_hash = generate_password_hash(request.form.get("password"))
            query = 'INSERT INTO users (username, hash, cash) VALUES("{}", "{}", {})'.format(
                request.form.get("username"),
                password_hash,
                10000.00
            )
            db.execute(query)
            person = db.execute("SELECT * FROM users WHERE username=?", request.form.get("username"))
            session["user_id"] = person[0]["id"]
            return redirect("/")
    else:
        message = ""
        return render_template("register.html", message=message)
    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = "message"
    available_shares = db.execute("SELECT symbol FROM shares WHERE user_pk=? AND shares!=0", session.get("user_id"))
    if request.method == "POST":
        if not request.form.get("symbol"):
            message = "You must select a valid share symbol."
            return render_template("sell.html", message=message, id=id), 400

        # lookup() the symbol
        quote = lookup(request.form.get("symbol"))

        if quote is None:
            message = "You must select a valid share symbol."
            id = "message"
            return render_template("sell.html", message=message, id=id), 400
        else:
            # request the number of shares
            shares = request.form.get("shares")
            if not isinstance(shares, (int)) or shares < 0:
                message = "invalid number of shares selected"
                id = "message"
                return render_template("sell.html", id=id, message=message), 400
            price = float(shares) * quote["price"]
            # check if user has enough cash available
            user_balance = db.execute("SELECT cash FROM users WHERE id=?", session.get("user_id"))[0]["cash"]
            user_balance += price
            timestamp = str(datetime.datetime.now())
            # insert name, name_pk, symbol, shares into shares
            existSymbol = db.execute("SELECT symbol FROM shares WHERE symbol=? AND user_pk=?",
                                     quote["symbol"],
                                     session.get("user_id"))
            username = db.execute("SELECT username FROM users WHERE id=?", session.get("user_id"))[0]["username"]
            print(username)

            if existSymbol:
                if existSymbol[0]["symbol"] == quote["symbol"]:
                    current_shares = db.execute("SELECT shares.shares FROM shares WHERE shares.symbol=? AND user_pk=?",
                                                quote["symbol"], session.get("user_id"))[0]["shares"]
                    if int(shares) > current_shares:
                        message = "You only have {} shares to sell".format(current_shares)
                        return render_template("sell.html", message=message, id=id)
                    new_shares = current_shares - int(shares)
                    db.execute("UPDATE shares SET shares=? WHERE symbol=? AND user_pk=? ",
                               new_shares,
                               quote["symbol"],
                               session.get("user_id")
                               )
            else:
                message = "you do not have {} shares to sell.".format(quote["symbol"])
                return render_template("sell.html", message=message, id=id)

            # TODO insert name, name_pk, date, time, symbol, +-shares, price/share into history
            db.execute("INSERT INTO history (user, user_pk, timestamp, symbol, delta_shares, price_share)"
                       " VALUES(?, ?, ?, ?, ?, ?)",
                       username,
                       session.get("user_id"),
                       timestamp,
                       quote["symbol"],
                       int(shares) * (-1),
                       quote["price"]
                       )
            # insert new cash balance into user
            db.execute("UPDATE users SET cash=? WHERE id=?", user_balance, session.get("user_id"))
        return redirect("/")
        # git commit
    return render_template("sell.html", shares=available_shares, id=id)


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    cash = db.execute("SELECT cash FROM users WHERE id=?", session.get("user_id"))
    if request.method == "POST":
        addition = request.form.get("cash")
        new_balance = round((cash[0]["cash"] + float(addition)), 2)
        username = db.execute("SELECT username FROM users WHERE id=?", session.get("user_id"))[0]["username"]
        timestamp = str(datetime.datetime.now())
        db.execute("UPDATE users SET cash=? WHERE id=?", new_balance, session.get("user_id"))
        db.execute("INSERT INTO history (user, user_pk, timestamp, symbol, delta_shares, price_share)"
                   " VALUES(?, ?, ?, ?, ?, ?)",
                   username,
                   session.get("user_id"),
                   timestamp,
                   "Cash Deposit",
                   0,
                   addition
                   )
        return redirect("/")
    return render_template("account.html", cash=cash[0]["cash"])


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
