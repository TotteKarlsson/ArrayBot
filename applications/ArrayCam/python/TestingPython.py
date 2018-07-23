import time
from datetime import datetime
import sys
import logging
import os


def main():

    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)

    # create a file handler
    appDataFolder = os.path.join(os.getenv('LOCALAPPDATA'), 'ArrayCam')
    handler = logging.FileHandler(os.path.join(appDataFolder,'pyPlugin.log'), mode='w')


    # create a logging format
    formatter = logging.Formatter('%(asctime)s  %(name)s  %(levelname)s  %(message)s', "%H:%M:%S")
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    try:
        #Retrieve arguments
        print ('Number of arguments:' +  str(len(sys.argv)) +  ' argument(s).')
        print ('Argument List:' + str(sys.argv))

        if len(sys.argv) != 2:
            raise Exception('Wrong number of arguments passed to ' + os.path.basename(__file__))

        cwd = os.getcwd()
        logger.info('CWD = ' + cwd )

        nr = 0
        for arg in sys.argv:
            logger.info('arg ' + str(nr) + ' = ' + arg)
            nr = nr + 1

        raise ValueError('Testing an exception')

    except Exception as e:
            logger.info(str(e))

if __name__ == "__MyPlugin__":
    main()
