#!/bin/python
from eve import Eve
import os

globalViewState = "0" # this is bad, when container reboots, view is not persisted!

app = Eve()
app._static_folder = os.getcwd()

@app.route('/ping')
def hello_world():
    return '{ "answer" : "pong" }'

@app.route('/<path:path>')
def index (path):
    return app.send_static_file('frontend/' + path)

@app.route('/globalViewState', methods=['GET'])
def viewState ():
    global globalViewState
    return globalViewState

@app.route('/globalViewState/<string:state>', methods=['POST'])
def changeViewState (state):
    global globalViewState
    globalViewState = state
    return 'ok', 200

if __name__ == "__main__":
    app.run(debug=True)
