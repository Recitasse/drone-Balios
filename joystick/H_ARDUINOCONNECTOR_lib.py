import serial
import json
import time

def arduino_connex(nom, baud):
   return serial.Serial('/dev/tty'+str(nom), baud)

def envoyer_data(ser, DATA):
   data_string = str(json.dumps(DATA))+'\n'
   data_string = data_string.encode('utf-8')
   ser.write(data_string)

def envoyer_data_df(ser, DATA, f):
   data_string = ','.join(map(str, DATA)).encode('utf-8')
   ser.write(data_string)
   time.sleep(f)
