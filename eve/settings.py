import os

# We want to seamlessy run our API both locally and on Heroku. If running on
# Heroku, sensible DB connection settings are stored in environment variables.
MONGO_HOST = '172.17.0.2'
MONGO_PORT = 27017
MONGO_USERNAME = os.environ.get('MONGO_USERNAME', 'admin')
MONGO_PASSWORD = os.environ.get('MONGO_PASSWORD', 'password')
MONGO_DBNAME = os.environ.get('MONGO_DBNAME', 'weather_station')

# Enable reads (GET), inserts (POST) and DELETE for resources/collections
# (if you omit this line, the API will default to ['GET'] and provide
# read-only access to the endpoint).
# RESOURCE_METHODS = ['GET', 'POST', 'DELETE']

# Enable reads (GET), edits (PATCH) and deletes of individual items
# (defaults to read-only item access).
# ITEM_METHODS = ['GET', 'PATCH', 'DELETE']

# We enable standard client cache directives for all resources exposed by the
# API. We can always override these global settings later.
CACHE_CONTROL = 'max-age=20'
CACHE_EXPIRES = 20


dhtTable = {
    'schema': {
        '_id' : {
            'type': 'number',
            'required': True,
        },
        'Temperature' : {
            'type': 'number',
            'required': True,
        },
        'Humidity' : {
            'type': 'number',
            'required': True,
        },
        'Timestamp' : {
            'type': 'datetime',
            'required': True,
        }
    }
}

bmpTable = {
    'schema': {
        '_id' : {
            'type': 'number',
            'required': True,
        },
        'Temperature' : {
            'type': 'number',
            'required': True,
        },
        'Altitude' : {
            'type': 'number',
            'required': True,
        },
        'Pressure' : {
            'type': 'number',
            'required': True,
        },
        'Timestamp' : {
            'type': 'datetime',
            'required': True,
        }
    }
}

tslTable = {
    'schema': {
        '_id' : {
            'type': 'number',
            'required': True,
        },
        'full_luminosity' : {
            'type': 'number',
            'required': True,
        },
        'Lux' : {
            'type': 'number',
            'required': True,
        },
        'ir_luminosity' : {
            'type': 'number',
            'required': True,
        },
        'Timestamp' : {
            'type': 'datetime',
            'required': True,
        }
    }
}

# The DOMAIN dict explains which resources will be available and how they will
# be accessible to the API consumer.
DOMAIN = {
    'dhtTable' : dhtTable,
    'bmpTable' : bmpTable,
    'tslTable' : tslTable
}
