import os
from eve import Eve

port = 5000
host = '0.0.0.0'

app = Eve(settings='settings.py')


if __name__ == '__main__':
    app.run(host=host, port=port, debug=True)
