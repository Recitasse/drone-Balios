# Librairies générales
import evdev
import asyncio
import sys
# Librairies crées
from H_FONCTION_joystick_lib import read_events
from H_DBCONNECTOR_joystick_lib import Joystick, integration_commande, lecture_manette_commande
from H_DBCONNECTOR_lib import connexion_db

# ========== Instanciation des outils ==========
# Connexion à la base de donnée
cursor, db = connexion_db(str(sys.argv[2]))
# Déclaration du Joystick
Joystick(cursor, db)


async def main():
    # Connexion et ajout de l'event correspondant
    device = evdev.InputDevice("/dev/input/" + str(sys.argv[1]))
    # Récupération des données du Joystick en async
    
    await read_events(device,cursor,db)

asyncio.run(main())
            
