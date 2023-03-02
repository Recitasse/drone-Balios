from numpy import arccos, sqrt, pi
import asyncio
import evdev
from H_DBCONNECTOR_joystick_lib import Joystick, integration_commande, lecture_manette_commande

# Fonction qui détermine le signe d'un input
def signe(v):
	if(v<0):
		return -1
	else:
		return 1



# Calcul de la valeur Psi du Joystick
def psi_extract(x,y):
	r = sqrt(x**2 + y**2)
	if(r > 7000):
		if((signe(y) == -1) and (signe(x) == 1)):
			return -45
		elif((signe(y) == -1) and (signe(x) == -1)):
			return 45
		elif((signe(y) == 1) and (signe(x) == -1)):
			return arccos(y/r)*90/pi
		elif((signe(y) == 1) and (signe(x) == 1)):
			return -arccos(y/r)*90/pi
		else:
			return 0
	else:
		return 0
		

# Lecture et sauvegarde des évènements
async def read_events(device,cursor,db):
    DATA = {'POSITION': {'PSI':0, 'Y':0, 'X':0}, 'REGLAGE': {'MODE':1, 'AUTO':0, 'INVERSE':1}}
    async for event in device.async_read_loop():
        if event.type == evdev.ecodes.EV_ABS:
            if event.code == evdev.ecodes.ABS_X:
                x_pos = event.value
            elif event.code == evdev.ecodes.ABS_Y:
                y_pos = event.value
            if 'x_pos' in locals() and 'y_pos' in locals():
                DATA['POSITION']['PSI'] = round(psi_extract(x_pos,-y_pos),1)*DATA['REGLAGE']['INVERSE']
     
        elif event.type == evdev.ecodes.EV_KEY:
            # Réglage du mode
            if event.code == evdev.ecodes.BTN_MODE:
               if DATA['REGLAGE']['MODE'] == 1 and event.value == 1:
                  DATA['REGLAGE']['MODE'] = 2
               elif DATA['REGLAGE']['MODE'] == 2 and event.value == 1:
                  DATA['REGLAGE']['MODE'] = 1
                  
            # Réglage de l'inversement
            elif event.code == evdev.ecodes.BTN_START:
               if DATA['REGLAGE']['INVERSE'] == -1 and event.value == 1:
                  DATA['REGLAGE']['INVERSE'] = 1
               elif DATA['REGLAGE']['INVERSE'] == 1 and event.value == 1:
                  DATA['REGLAGE']['INVERSE'] = -1
                  
            # Réglage du mode automatique
            elif event.code == evdev.ecodes.BTN_SELECT:
               if DATA['REGLAGE']['AUTO'] == 0 and event.value == 1:
                  DATA['REGLAGE']['AUTO'] = 1
               elif DATA['REGLAGE']['AUTO'] == 1 and event.value == 1:
                  DATA['REGLAGE']['AUTO'] = 0
                  
            # On récupère les valeurs pour avancer
            elif event.code == evdev.ecodes.BTN_A:
               DATA['POSITION']['Y'] = 5*event.value*DATA['REGLAGE']['MODE']
            elif event.code == evdev.ecodes.BTN_B:
               DATA['POSITION']['Y'] = -5*event.value*DATA['REGLAGE']['MODE']
            elif event.code == evdev.ecodes.BTN_Y:
               DATA['POSITION']['Y'] = event.value*DATA['REGLAGE']['INVERSE']*DATA['REGLAGE']['MODE']
            
            # On récupère la translation
            elif event.code == evdev.ecodes.BTN_X:
               DATA['POSITION']['X'] = event.value*DATA['REGLAGE']['INVERSE']*DATA['REGLAGE']['MODE']
               
            elif event.code == evdev.ecodes.BTN_TL:
               DATA['POSITION']['PSI'] = 1*event.value*5
            elif event.code == evdev.ecodes.BTN_TR:
               DATA['POSITION']['PSI'] = -1*event.value*5
            
        # Prise en comtpe des réglages
        integration_commande(DATA, cursor, db)
        lecture_manette_commande(cursor)
        print(DATA)
               
               
               
               
