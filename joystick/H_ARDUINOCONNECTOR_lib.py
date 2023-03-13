import serial
import json

def arduino_connex(nom, baud):
   return serial.Serial('/dev/tty'+str(nom), baud)


def envoyer_data(ser, DATA):

   data_string = str(json.dumps(DATA))+'\n'
   data_string = data_string.encode('utf-8')
   
   ser.write(data_string)

