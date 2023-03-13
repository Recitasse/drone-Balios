import serial
import json
from H_ARDUINOCONNECTOR_lib import arduino_connex
import asyncio
import sys
from H_CAPTEURS_lib import read_data
from H_DBCONNECTOR_capteur_lib import sonar
from H_DBCONNECTOR_lib import connexion_db

cursor, db = connexion_db(str(sys.argv[3]))
sonar(cursor, db)

async def main():
    while True:
       ser = arduino_connex(str(sys.argv[1]), int(sys.argv[2]))
       await read_data(ser, cursor, db)
    
asyncio.run(main())
