import serial
import json
import asyncio
from H_DBCONNECTOR_capteur_lib import sonar, integration_sonar, lecture_capteur_sonar, explode


async def read_data(ser,cursor,db):
   phrase = ser.readline()
   phrase = phrase.decode('utf-8')
   print(explode(":",phrase))
   '''
   try:
      jsonD_parse = json.loads(jsonD_decode)
      v = jsonD_parse["SONAR"]["D"]
      integration_sonar(v, cursor, db)
      lecture_capteur_sonar(cursor)
   except json.decoder.JSONDecodeError:
      # Les données sont vides
      pass'''


