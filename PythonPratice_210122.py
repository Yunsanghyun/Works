from flask import Flask
app = Flask(__name__)

@app.route("/")

def hello():
    return "안녕하셋"   