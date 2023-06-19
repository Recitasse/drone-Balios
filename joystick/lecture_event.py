# Librairies générales
import evdev
import asyncio
import sys

# Librairies crées
from H_ARDUINOCONNECTOR_lib import arduino_connex
from H_FONCTION_joystick_lib import read_events_f

# ======== Initialisation de la manette ============
Ini = 0

# ========== Instanciation des outils ==========
# arduino_connex(ACM0, 9600)
# InputDevice(event29)

async def main():
    ser = arduino_connex(str(sys.argv[2]), int(sys.argv[3]))
    # Connexion et ajout de l'event correspondant
    device = evdev.InputDevice("/dev/input/" + str(sys.argv[1]))
    # Récupération des données du Joystick en async
    await read_events_f(device,ser,str(sys.argv[4]))
    

asyncio.run(main())
            
