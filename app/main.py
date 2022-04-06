from flask import Flask, request, make_response
import pandas as pd
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret_key'

try:
    file = open('data.csv', 'a')
    file.write("PH, TURBUDITY\n")
    file.close()
except Exception as err:
    print(err)


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
        file.close()
        return "0"
    except Exception as err:
        print(err)
        return "-1"

@app.route('/getCSV/', methods=['GET', 'POST'])
def getCsv():
    df = pd.read_csv(f"{os.getcwd()}/data.csv")
    resp = make_response(df.to_csv(index=False))
    resp.headers["Content-Disposition"] = "attachments; filename=data.csv"
    resp.headers["Content-Type"] = "text/csv"
    return resp
    # return "csd"