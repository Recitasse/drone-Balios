import serial

def arduino_connex():
   return serial.Serial('/dev/ttyACM0', 9600)


def envoyer_data(ser):

   ser.write(b'Hello, Arduino')

