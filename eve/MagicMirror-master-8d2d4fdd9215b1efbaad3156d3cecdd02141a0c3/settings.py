DOMAIN = {
        'jokes': {
            'allow_unknown' : True,
            'schema': {
                'text' : {
                    'type' : 'string'
                }
            }
        },
        'humidity': {
            'allow_unknown' : True,
            'schema': {
                'value' : {
                    'type' : 'number'
                }
            }
        },
        'temperature': {
            'allow_unknown' : True,
            'schema': {
                'value' : {
                    'type' : 'number'
                }
            }
        },
        'pressure': {
            'allow_unknown' : True,
            'schema': {
                'value' : {
                    'type' : 'number'
                }
            }
        },
        'altitude': {
            'allow_unknown' : True,
            'schema': {
                'value' : {
                    'type' : 'number'
                }
            }
        },
        'lux': {
            'allow_unknown' : True,
            'schema': {
                'value' : {
                    'type' : 'number'
                }
            }
        },
        'news': { # this is probably not needed - use 3rd party rss
            'allow_unknown' : True,
            'schema': {
                'text' : {
                    'type' : 'number'
                }
            }
        },
    }
MONGO_HOST = 'localhost'
MONGO_PORT = 27017

MONGO_DBNAME = 'mirror'

RESOURCE_METHODS = ['GET', 'POST', 'DELETE']
ITEM_METHODS = ['GET', 'PATCH', 'PUT', 'DELETE']

URL_PREFIX="api"

X_DOMAINS = '*'

#MONGO_HOST = ""
