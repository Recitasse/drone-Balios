from numpy import arccos, sqrt, pi, sin, cos, tan, log, exp
import evdev
import time
from wgs2lamb import wgs2lamb
from datetime import datetime


# Fonction qui détermine le signe d'un input
def signe(v):
	if(v<0):
		return -1
	else:
		return 1

def map_angle(val):
    return int((val+45)*(256/90)+100)

def integrite(parties) ->bool:
   if(len(parties) != 8):
        return False
   if(len(parties[4]) < 6 and len(parties[5]) < 6):
        return False
   try:
        float(parties[4])
        float(parties[5])
        float(parties[6])
   except ValueError:
        return False
   return True
        
         
     

# Calcul de la valeur Psi du Joystick
def psi_extract(x,y):
	r = sqrt(x**2+y**2)
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
		
def pow_psi(x,y,s):
	# s La sensibilité -> 0 intterdit, 1 linéaire, 2 hyperbolique etc.
	r = sqrt(x**2+y**2)
	if(r>2**15*0.95):
		return 2**8
	else:
		return int((1/2**15)**s*r**s*2**8)
               
        
def envoyer_data_df(ser, DATA, f):
   data_string = ','.join(map(str, DATA)).encode('utf-8')
   ser.write(data_string)
   time.sleep(f)
               
               
# Lecture et sauvegarde des évènements au format JSON
async def read_events_f(device,ser, f):
    DATA = {'POSITION': {'PSI':0, 'POW':0, 'Y':0, 'X':0}, 'REGLAGE': {'MODE':1, 'AUTO':1, 'ARRET':1}}
    async for event in device.async_read_loop():
        if event.type == evdev.ecodes.EV_ABS:
            if event.code == evdev.ecodes.ABS_X:
                x_pos = event.value
            elif event.code == evdev.ecodes.ABS_Y:
                y_pos = event.value
            if 'x_pos' in locals() and 'y_pos' in locals():
                DATA['POSITION']['PSI'] = round(psi_extract(x_pos,-y_pos),1)*DATA['REGLAGE']['ARRET']
                DATA['POSITION']['POW'] = round(pow_psi(x_pos,-y_pos, 3),2)
     
        elif event.type == evdev.ecodes.EV_KEY:
            # Réglage du mode
            if event.code == evdev.ecodes.BTN_MODE:
               if DATA['REGLAGE']['MODE'] == 1 and event.value == 1:
                  DATA['REGLAGE']['MODE'] = 2
               elif DATA['REGLAGE']['MODE'] == 2 and event.value == 1:
                  DATA['REGLAGE']['MODE'] = 1
                  
            # Réglage de l'ARRETment
            elif event.code == evdev.ecodes.BTN_START:
               if DATA['REGLAGE']['ARRET'] == -1 and event.value == 1:
                  DATA['REGLAGE']['ARRET'] = 1
               elif DATA['REGLAGE']['ARRET'] == 1 and event.value == 1:
                  DATA['REGLAGE']['ARRET'] = -1
                  
            # Réglage du mode automatique
            elif event.code == evdev.ecodes.BTN_SELECT:
               if DATA['REGLAGE']['AUTO'] == -1 and event.value == 1:
                  DATA['REGLAGE']['AUTO'] = 1
               elif DATA['REGLAGE']['AUTO'] == 1 and event.value == 1:
                  DATA['REGLAGE']['AUTO'] = -1
                  
            # On récupère les valeurs pour avancer
            elif event.code == evdev.ecodes.BTN_A:
               DATA['POSITION']['Y'] = 1*event.value*DATA['REGLAGE']['MODE']
            elif event.code == evdev.ecodes.BTN_B:
               DATA['POSITION']['Y'] = -1*event.value*DATA['REGLAGE']['MODE']
            elif event.code == evdev.ecodes.BTN_Y:
               DATA['POSITION']['Y'] = event.value*DATA['REGLAGE']['ARRET']*DATA['REGLAGE']['MODE']
            
            # On récupère la translation
            elif event.code == evdev.ecodes.BTN_X:
               DATA['POSITION']['X'] = event.value*DATA['REGLAGE']['ARRET']*DATA['REGLAGE']['MODE']
               
            elif event.code == evdev.ecodes.BTN_TL:
               DATA['POSITION']['PSI'] = 1*event.value*5
            elif event.code == evdev.ecodes.BTN_TR:
               DATA['POSITION']['PSI'] = -1*event.value*5
            
        if(DATA['REGLAGE']['ARRET'] == -1 and DATA['REGLAGE']['AUTO'] == 1):
            DATA_new = ["C,228,0,0,100,E"]
            envoyer_data_df(ser, DATA_new, float(f)*10**-3)
        elif(DATA['REGLAGE']['ARRET'] == 1 and DATA['REGLAGE']['AUTO'] == -1):
            DATA_new = ["A,228,0,0,100,E"]
            envoyer_data_df(ser, DATA_new, float(f)*10**-3)
         
        else:
         DATA_new = ["S,"+str(map_angle(DATA['POSITION']['PSI']))+","+str(DATA['POSITION']['X'])+","+str(DATA['POSITION']['Y'])+","+str(DATA['POSITION']['POW']+100)+",E"]
         envoyer_data_df(ser, DATA_new, float(f)*10**-3)
         #print(DATA_new)

        

def affichage(text:str):
     parties = text.split(',')
     #for i in range(len(parties)):
      #    print(parties[i])
     X, Y = wgs2lamb(float(parties[4]), float(parties[5]))
     print(">----------------------------------------------------<")
     print("Distance : {0:.1f} ({1:}, {2:})".format(float(parties[1]), X, Y))
     print("Etats : {0:.1f} C°; humidité : {1:.1f}.".format(float(parties[3]), float(parties[2])))
     print(datetime.now().strftime("%H:%M:%S"))
     print(">----------------------------------------------------<")