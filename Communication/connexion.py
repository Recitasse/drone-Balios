from bdd import BDD
import sys
import asyncio
import evdev
import serial
from function import read_events_f

# nom_bdd actuelle : droneBalios_Communication
# 1: nom_bdd, 2: ACM, 3: event, 4: baud, 5: delais

bdd = BDD(sys.argv[1])
bdd.creation_tables()

async def get_data(ser: serial, bdd: BDD):
    ser.timeout = 0.01
    ser.read(size=1024).decode('ascii', errors='ignore').strip()

    while True:
        text = ser.read(size=1024).decode('ascii', errors='ignore').strip()
        print(text)
        if text:
            parties = text.split(',')
            if(len(parties) == 5):
                bdd.integration_gps_lat(float(parties[1]))
                bdd.integration_gps_long(float(parties[2]))
                bdd.integration_sonar(float(parties[3]))
                await asyncio.sleep(5)
        else:
            await asyncio.sleep(0.005)

async def main():

    ser = serial.Serial('/dev/tty'+str(sys.argv[2]), sys.argv[4])
    device = evdev.InputDevice("/dev/input/" + str(sys.argv[3]))
    tache1 = asyncio.create_task(read_events_f(device, ser, sys.argv[5]))
    tache2 = asyncio.create_task(get_data(ser, bdd))
    await asyncio.gather(tache1, tache2)


asyncio.run(main())

    



