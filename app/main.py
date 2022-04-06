from distutils.log import debug
from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    return "App is Running..."

@app.route('/updateCSV/', methods=['GET', 'POST'])
def updateCSV():
    data = request.args.get('data')
    print(data)
    try:
        file = open('data.csv', 'a')
        x, y = map(float, data.split(","))
        file.write(f"{x}, {y}\n")
        print("Data Updated in CSV")
        return "0"
    except Exception as err:
        print(err)
        return "-1"