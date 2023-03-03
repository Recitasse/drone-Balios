#!/bin/bash

echo "
    ___   _   _    ___ ___  ___        _   __  
   | _ ) /_\ | |  |_ _/ _ \/ __| __ __/ | /  \ 
   | _ \/ _ \| |__ | | (_) \__ \ \ V /| || () |
   |___/_/ \_\____|___\___/|___/  \_(_)_(_)__/ 
   ___________________________________________
  |___________________________________________|       
  
  "

echo -e "\033[33mCentre de démarrage et d'arrêt du Balios\033[0m\n"

# Lancement du programme
sudo systemctl start mysql
sudo systemctl status mysql

sudo systemctl start apache2
sudo systemctl status apache2

# Lancer le lien php
firefox -new-window http://dronebalios.com/

echo -e "Vous pouvez afficher toutes les commandes avec la commande aide \n"
echo -e "\033[33mLes commandes : \033[0m"
echo -e "   \033[33mstop\033[0m: pour arrêter."
echo -e "   \033[33mredm\033[0m: pour redémarrer."
echo -e "   \033[33mraf\033[0m: pour rafraichir la configuration du server."
echo -e "   \033[33mjoyinput\033[0m: pour afficher le nom de l'évènement."
echo -e "   \033[33msql-session\033[0m: pour afficher les différentes sessions."

# Lire une commande
read -p "Votre commande : " cmd

while [ "${cmd}" != "stop" ]
do
    #Pour redémarrer
    if [ "${cmd}" == "redm" ]
    then
       sudo systemctl restart mysql
       sudo systemctl restart apache2
       sudo systemctl status mysql
       sudo systemctl status apache2
       echo -e "\033[32mMySQL et Apache ont redémarré correctement! \033[0m"
       
    #Pour redémarrer
    elif [ "${cmd}" == "raf" ]
    then
       sudo systemctl reload mysql
       sudo systemctl reload apache2
       sudo systemctl status mysql
       sudo systemctl status apache2 
    
    #Pour lire l'event du joystik
    elif [ "${cmd}" == "joyinput" ]
    then
       result=$(sudo cat /proc/bus/input/devices | grep -B 2 -A 9 Controller)
       if [ -z ${result} ]
       then
           echo -e "\033[031mVous n'avez pas branché de joystick (ou celui-ci n'est pas reconnu).\033[0m"
       else
           echo -e "${result}\n"
       fi
    #Pour redémarrer
    


    else
       echo -e "\033[31mCette commande n'existe pas! \033[0m"
    fi
    

       
    
    read -p "Votre commande : " cmd
done


sudo systemctl stop mysql
sudo systemctl stop apache2
sudo systemctl status mysql
sudo systemctl status apache2









