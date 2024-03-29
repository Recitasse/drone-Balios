#!/bin/bash

current_directory=$(pwd)
user=$USER
nom_term="Balios"

chmod  +x "${current_directory}"/balios_launcher.sh

#Création du .desktop
{
echo "[Desktop Entry]"
echo "Encoding=UTF-8"
echo "Version=1.0"
echo "Type=Application"
echo "Terminal=true"
echo "Exec=gnome-terminal --title '${USER}-${nom_term}' --command 'bash -c ${current_directory}/balios_launcher.sh'"
echo "Name=Balios"
echo "Icon=${current_directory}/www/bateau.jpg"
echo "Categories=Application"
echo "Comment=Application permettant de contrôler le drone"
} >> /home/"${user}"/Desktop/Balios.desktop

chmod a+rx /home/"${user}"/Desktop/Balios.desktop
sudo chmod 755 /home/"${user}"/Desktop/Balios.desktop
gio set /home/"${user}"/Desktop/Balios.desktop metadata::trusted true

# On renome le terminal
echo -ne "\033]0;Centre de démarrage du Balios\007"
echo -e "Vérification des logiciels et packages.\n"
#On regarde si les principaux programmes sont bien installés

#On regarde pour mysql
if ! dpkg-query -W -f='${Status}' mysql-server 2>/dev/null | grep -q "ok installed"; then
  echo -e "\033[31m\033[1m❌  MySQL n'est pas installé ! \033[0m\033[0m"
  sudo apt-get install mysql-server
  sudo mysql_
  echo -e "\033[32m\033[1m✔  MySQL installé ! \033[0m\033[0m"
  mysql_version=$(mysql --version)
  echo "      Version : ${mysql_version}"
  echo "Paramétrer MYSQL"
  mysql_secure_installation 
  echo "Entrer votre mot de passe utilisateur MySQL :"
  read -r mdp_mysql
  
  # Démarrage de mysql pour créer un utilisateur
  if (mysql -u root -p"${mdp_mysql}" -e "SELECT User FROM mysql.user WHERE User='balios'@'localhost';" | grep "'balios'@'localhost'" > /dev/null)
  then
     echo "L'utilisateur est prêt"
     else
     echo "Création de l'utilisateur:"
     mysql -u root -p -e "CREATE user 'balios'@'localhost' Identified by 'droneBalios1';"
     mysql -u root -p -e "GRANT ALL PRIVILEGES ON *.* TO 'balios'@'localhost';"
     fi
  
else
  echo -e "\033[32m\033[1m✔  MySQL installé ! \033[0m\033[0m"
  mysql_version=$(mysql --version)
  echo "      Version : ${mysql_version}"
fi

# Pour python

if ! dpkg-query -W -f='${Status}' python3 2>/dev/null | grep -q "ok installed"; then
  echo -e "\033[31m\033[1m❌  Python3 n'est pas installé ! \033[0m\033[0m"
  sudo apt-get install python3
else
  echo -e "\033[32m\033[1m✔  Python3 installé ! \033[0m\033[0m"
  python_version=$(python3 --version)
  echo "      Version : ${python_version}"
fi
# Vérification pour les librairies en utilisateur root
lieu=$(dir /usr/bin/python3 | grep pip.py)
if [ -n "${lieu}" ]; then
   sudo curl https://bootstrap.pypa.io/get-pip.py -o /usr/bin/get-pip.py
   sudo python3 /usr/bin/get-pip.py
   echo -e "   \033[31m• La librairie pip installée dans le dossier /usr/bin/python3.\033[0m "
fi

# Pour apache2
if ! dpkg-query -W -f='${Status}' apache2 2>/dev/null | grep -q "ok installed"; then
  echo -e "\033[31m\033[1m❌  Apache2 n'est pas installé ! \033[0m\033[0m"
  sudo apt-get install apache2
  
  #Configuration du server Apache
  echo -e "\033[32m\033[1m✔  Apache2 installé ! \033[0m\033[0m"
  apache2_version=$(apache2 -v | grep "Server version" | cut -d/ -f2 | awk '{print $1}')
  echo "      Version : ${apache2_version}"
  echo -e "      \033[33mConfiguration actuelle du par feu :.\033[0m"
  sudo ufw status

else
  echo -e "\033[32m\033[1m✔  Apache2 installé ! \033[0m\033[0m"
  apache2_version=$(apache2 -v | grep "Server version" | cut -d/ -f2 | awk '{print $1}')
  echo "      Version : ${apache2_version}"
  echo -e "      \033[33mConfiguration actuelle du par feu :\033[0m"
  sudo ufw status
fi
# on regarde le dns et l'ip du site
DNS="/etc/hosts"
dns_nom="dronebalios.com"
if ! grep -q "${dns_nom}" "${DNS}"; then
  echo "127.0.4.1	${dns_nom}" >> "${DNS}"
fi
# On l'ajoute à la configuration d'apache
vm="/etc/apache2/apache2.conf"
vm_ip="ServerName dronebalios.com"
if ! grep -q "${vm_ip}" "${vm}"; then
  sudo bash -c "echo '<VirtualHost 127.0.4.1:80>' >> '${vm}'"
  sudo bash -c "echo 'ServerName dronebalios.com' >> '${vm}'"
  sudo bash -c "echo 'DocumentRoot /home/raphael/Desktop/drone-Balios/www' >> '${vm}'"
  sudo bash -c "echo '<Directory /home/raphael/Desktop/drone-Balios/www>' >> '${vm}'"
  sudo bash -c "echo 'Options Indexes FollowSymLinks' >> '${vm}'"
  sudo bash -c "echo 'AllowOverride None' >> '${vm}'"
  sudo bash -c "echo 'Require all granted' >> '${vm}'"
  sudo bash -c "echo '</Directory>' >> '${vm}'"
  sudo bash -c "echo '</VirtualHost>' >> '${vm}'"
else
   echo -e "\033[32m\033[1m✔\033[0m Configuration apache2 déjà effectuée.\033[0m"
fi
echo -e "\033[32m\033[1m✔\033[0m Configuration apache2 terminée.\033[0m\n"


# Installation de Putty
checkpuTTY=$(which putty)
if [ -z "${checkpuTTY}" ]; then
   echo -e "\033[31m\033[1m❌ PuTTY n'est pas installé ! \033[0m\033[0m"
   sudo apt-get install putty
fi
echo -e "\033[32m\033[1m✔  PuTTY installé ! \033[0m\033[0m"

#Installation de Tmux
if [ -z "${checkpuTTY}" ]; then
   echo -e "\033[31m\033[1m❌ tmux n'est pas installé ! \033[0m\033[0m"
   sudo apt-get install tmux
fi
echo -e "\033[32m\033[1m✔  tmux installé ! \033[0m\033[0m"

# Installation d'Arduino
check=$(which arduino)
if [ -n "${check}" ]; then
  echo -e "\033[32m\033[1m✔  Arduino installé ! \033[0m\033[0m"
  arduino_version=$(arduino --version | grep "Arduino: ")
  echo "      Version : ${arduino_version}"
else
  # installation d'arduino
  echo -e "\033[31m\033[1m❌  Arduino n'est pas installé ! \033[0m\033[0m"
  echo -e "\033[33mTéléchargement d'arduino : 1.8.14\033[0m"
  sudo wget https://downloads.arduino.cc/arduino-1.8.14-linux64.tar.xz -P /home/"${user}"/.local/share
  echo -e "\033[33mTéléchargement réussit ! 1.8.14\033[0m"
  sudo chmod 777 /home/"${user}"/.local/share/arduino-1.8.14-linux64.tar.xz
  sudo tar -xf /home/"${user}"/.local/share/arduino-1.8.14-linux64.tar.xz -C /home/"${user}"/.local/share
  sudo rm /home/"${user}"/.local/share/arduino-1.8.14-linux64.tar.xz
  cd /home/"${user}"/.local/share/arduino-1.8.14/ || exit
  chmod +x install.sh
  sudo ./install.sh
  sudo usermod -a -G dialout "${user}"
  echo -e "\033[32m\033[1m✔  Arduino installé ! \033[0m\033[0m"
  arduino_version=$(arduino --version | grep "Arduino: ")
  echo "      Version : ${arduino_version}"
fi


# Installation des packages python


echo -e "\nInstallations des librairies python :"
lib_pyth=("pip" "evdev" "asyncio" "mysql-connector-python" "numpy" "pyserial" "json")

for i in "${lib_pyth[@]}"; do

  if python3 -c "import ${i}" 2> /dev/null; then
    echo -e "   \033[32m• La librairie \033[1m${i}\033[0m est installé ! \033[0m"
    version=$(python3 -m pip show "${i}" | grep Version | awk '{print $2}')
    echo "                  └$version."
  else
    echo -e "   \033[31m• La librairie ${i} n'est pas installée.\033[0m "
    sudo python3 -m pip install "${i}"
    echo -e "   \033[32m• La librairie \033[1m${i}\033[0m est installé ! \033[0m"
    version=$(python3 -m pip show "${i}" | grep Version | awk '{print $2}')
    echo "                  └$version."
  fi
done

if python3 -c "import evdev" 2> /dev/null; then
   sudo apt-get install evdev
fi


echo -e "___________________________________________________________"
echo -e "Vérification des accès des privilèges sudoers :"
#Ajout des sudoers pour lire les scripts python
if sudo grep -q "www-data ALL=(ALL) NOPASSWD: ${current_directory}/joystick/lecture_event.py" /etc/sudoers; then
  echo -e "\033[32m•  Joystick accéssible en lecture ! \033[0m"
else
  echo -e "\033[31m• www-data n'a pas l'autorisation d'utiliser \033[1mjoystick.py\033[0m.\033[0m"
  echo -e "\033[33mCommande effectuée : www-data ALL=(ALL) NOPASSWD: /home/${user}/Desktop/Balios/joystick/lecture_event.py\033[0m"
  echo "www-data ALL=(ALL) NOPASSWD: /home/${user}/Desktop/Balios/joystick/lecture_event.py" | sudo -S tee -a /etc/sudoers
fi

if sudo grep -q "www-data ALL=(ALL) NOPASSWD: /usr/bin/screen, ${current_directory}/Initialisation_arduino/bin/arduino-cli" /etc/sudoers; then
echo -e "\033[32m•  Arduino accéssible en lecture ! \033[0m"
else
  echo -e "\033[31m• www-data n'a pas l'autorisation d'utiliser \033[1mArduino\033[0m.\033[0m"
  echo -e "\033[33mCommande effectuée : www-data ALL=(ALL) NOPASSWD: /usr/bin/screen, ${current_directory}/Initialisation_arduino/bin/arduino-cli\033[0m"
  echo "www-data ALL=(ALL) NOPASSWD: www-data ALL=(ALL) NOPASSWD: /usr/bin/screen, ${current_directory}/Initialisation_arduino/bin/arduino-cli" | sudo -S tee -a /etc/sudoers
fi

if sudo grep -q "www-data ALL=(ALL) NOPASSWD: /usr/bin/python3" /etc/sudoers; then
  echo -e "\033[32m•  Php à la permission d'éxécuter un script python possédant la librairie evdev (donne accès aux /dev/input/event*) ! \033[0m"
else
  echo -e "\033[31m• www-data n'a pas l'autorisation d'utiliser \033[1mevdev\033[0m.\033[0m"
  echo -e "\033[33mCommande effectuée : www-data ALL=(ALL) NOPASSWD: /usr/bin/python3\033[0m"
     echo "www-data ALL=(ALL) NOPASSWD: /usr/bin/python3" | sudo tee -a /etc/sudoers
fi

echo -e "\033[33mVérifier par vous-mêmes (par raison de sécurité) l'accès au privilège root des sudoers.\033[0m"
echo -e "\033[32m\033[1m✔  Paramétrage des sudoers effectué ! \033[0m\033[0m"

echo -e "\n \033[32m\033[1m	    Installation réussit! \033[0m\033[0m"
echo -e "\n___________________________________________________________"

# Affichage

echo "
    ___ ___ ___ _  ___   _____ _  _ _   _ ___  
   | _ )_ _| __| \| \ \ / / __| \| | | | | __| 
   | _ \| || _|| .  |\ V /| _|| .  | |_| | _|  
   |___/___|___|_|\_| \_/ |___|_|\_|\___/|___| 
                                               
    ___ _   _ ___                              
   / __| | | | _ \                             
   \__ \ |_| |   /                             
   |___/\___/|_|_\                             
                                               
    ___   _   _    ___ ___  ___        _   __  
   | _ ) /_\ | |  |_ _/ _ \/ __| __ __/ | /  \ 
   | _ \/ _ \| |__ | | (_) \__ \ \ V /| || () |
   |___/_/ \_\____|___\___/|___/  \_(_)_(_)__/ 
   ___________________________________________
  |___________________________________________|                                               
   "
echo -e "Le logiciel \033[1mBalios\033[0m est actuellement en \033[1mv.1.0\033[0m.\nCertaines applications et modules ne sont pas encore disponnibles,\nvous pouvez lire les mise à jour successives dans les logs ci-dessus.\n" 

echo -e "\033[33m\033[1mFonctionnalité v.1.0:\033[0m\033[0m"
echo -e "	MODULE_CONTRÔLE \033[33mv.1.0\033[0m : 'Contrôle radio'"
echo -e "	MODULE_AUTONOME \033[33mv.1.0\033[0m : 'Contrôle automatique'"
echo -e "	RELEVÉ_BATHYMÉTRIQUE \033[33mv.1.0\033[0m : 'Contrôle automatique'\n"
echo -e "___________________________________________________________"

echo -e "\033[1mLa version v.1.0 est la première version encore non opérationnelle.\033[0m"
echo -e "\nAppuyer sur un touche pour fermer"
