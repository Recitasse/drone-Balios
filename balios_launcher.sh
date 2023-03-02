#!/bin/bash

echo "
    ___   _   _    ___ ___  ___        _   __  
   | _ ) /_\ | |  |_ _/ _ \/ __| __ __/ | /  \ 
   | _ \/ _ \| |__ | | (_) \__ \ \ V /| || () |
   |___/_/ \_\____|___\___/|___/  \_(_)_(_)__/ 
   ___________________________________________
  |___________________________________________|       
  
  "

# Lancer le lien php
#firefox_path=$(which firefox)
#url=$("drone")
#sudo ${firefox_path} ${url}

echo -e "\033[33mCentre de démarrage et d'arrêt du Balios\033[0m\n"

# Lancement du programme
sudo systemctl start mysql
sudo systemctl status mysql

sudo systemctl start apache2
sudo systemctl status apache2

echo -e "Vous pouvez afficher toutes les commandes avec la commande aide \n"
echo -e "\033[33mLes commandes : \033[0m"
echo -e "   \033[32mstop\033[0m: pour arrêter."
echo -e "   \033[32mredm\033[0m: pour redémarrer.\n"

# Lire une commande
read -p "Votre commande : " cmd

while [ "${cmd}" != "stop" ]
do
    if [ "${cmd}" == "redm" ]
    then
       sudo systemctl restart mysql
       sudo systemctl restart apache2
       sudo systemctl status mysql
       sudo systemctl status apache2
       echo -e "\033[32mMySQL et Apache ont redémarré correctement! \033[0m"
    
    else
       echo -e "\033[31mCette commande n'existe pas! \033[0m"
    fi
    read -p "Votre commande : " cmd
done


sudo systemctl stop mysql
sudo systemctl stop apache2
sudo systemctl status mysql
sudo systemctl status apache2









