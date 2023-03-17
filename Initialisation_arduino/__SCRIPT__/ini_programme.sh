#!/bin/bash

# Fonction barre de temps

progress_bar() {
    local percent=$1
    local bar_length=50
    local filled_length=$((percent * bar_length / 100))
    local bar
    bar=$(printf "%-${bar_length}s" "|" | tr ' ' '-')
    printf "\r%s %d%%" "${bar:0:filled_length}|${bar:filled_length}" "$percent"
}

# ==================== Les conditions d'execution ======================
# |						     |
# |    Le script ini_case.sh prend plusieurs variable                  |
# |    Le script php doit envoyer plusieurs informations :             |
# |      * ACM* et event* bdname* pour la lecture des hardwares et bd  |
# |      * On envoit un nombre entre 0 et 7                            |
# |           -> Si on a 0 on fait tout                                |
# |           -> Si on a 7 = 4 +2 +1 on doit éxécuter 4,2,1 (le nom)   |
# |						     |
# ======================================================================


# ================= Lecture des cartes ===========

#====== Le branchement de la carte arduino =========
#1.1] le branchement de la carte
carte=$(glob /dev/ttyACM* | grep "$1")

if [ -z "${carte}" ]
then
    exit 1
else
    sed -i 's/BRANCHEMENT_CARTE=0/BRANCHEMENT_CARTE=1/g' valid_var.properties
fi

#1.2] Vérification de la carte (bonne sélection)
if [[ "/dev/tty$1" == *"${carte}"* ]]
then
    sed -i 's/SELECTION_CARTE=0/SELECTION_CARTE=1/g' valid_var.properties
else
    exit 1
fi

#1.3] S'assurer de la communication entre les cartes
#1.3.1) Utilisation de arduino-cli pour 

if ! sudo ../bin/arduino-cli compile --fqbn arduino:avr:uno ../Communication_sender/Communication_sender.ino && sudo ../bin/arduino-cli upload -p /dev/tty"$1" --fqbn arduino:avr:uno ../Communication_sender/Communication_sender.ino; then
    echo "Erreur, impossible de compiler le sketch arduino"
    exit 1
else
    sed -i 's/COMPILATION_SKETCH_CARTE_COMMUNICATION=0/COMPILATION_SKETCH_CARTE_COMMUNICATION=1/g' valid_var.properties
fi

#1.3.2) Condition de lecture
stty -F /dev/tty"$1" 9600
sleep 2
it=0
max=2000
while true;do
  output=$(timeout 5s cat /dev/tty"$1" | tee /dev/tty)
  if [[ "${output}" == *"1"* ]]
  then
      echo -e "\nCommunication établie"
      sed -i 's/COMMUNICATION_CARTE=0/COMMUNICATION_CARTE=1/g' valid_var.properties
      break
  fi
  
  progress_bar $((100 * 100 *it / (40 * 5000)))
  if [ "${it}" -gt "${max}" ]
  then
      exit 1
  fi
  it=$((it+1))
done

# ================= Lecture du joystick ===========

#2.1) Branchement du joystick
joy=$(cat /proc/bus/input/devices | grep js0)
if [ -z "${joy}" ]
then
    exit 1
else
    sed -i 's/BRANCHEMENT_JOYSTICK=0/BRANCHEMENT_JOYSTICK=1/g' valid_var.properties
fi

#2.2) Insertion du bon event
if [[ "$2" == *"${joy}"* ]]
then
    exit 1
else
    sed -i 's/SELECTION_JOYSTICK=0/SELECTION_JOYSTICK=1/g' valid_var.properties
fi


#2.3) Programme de lecture
sudo ../bin/arduino-cli lib install ArduinoJson

if ! sudo ../bin/arduino-cli compile --fqbn arduino:avr:uno ../joystic_ini/joystic_ini.ino && sudo ../bin/arduino-cli upload -p /dev/tty"$1" --fqbn arduino:avr:uno ../joystic_ini/joystic_ini.ino; then
    echo "Erreur, impossible de compiler le sketch arduino"
    exit 1
else
    sed -i 's/COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=0/COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=1/g' valid_var.properties
fi

if ! sudo python3 ../../joystick/lecture_event.py "$2" "$1" 500000 &
then
    echo "Erreur, impossible d'éxécuter le script python de lecture."
    exit 1
else
    sed -i 's/LECTURE_EVENT=0/LECTURE_EVENT=1/g' valid_var.properties
fi

echo "Veuillez appuyer sur A plusieurs fois pour avoir 5 (vous avez 5s): "
stty -F /dev/tty"$1" 500000
it2=0
max=2000
while true;do
  output=$(timeout 5s cat /dev/tty"$1" | tee /dev/tty)
  if [[ "${output}" == *"5"* ]]
  then
      echo -e "\nCommunication établie"
      sed -i 's/COMMUNICATION_JOYSTICK=0/COMMUNICATION_JOYSTICK=1/g' valid_var.properties
      break
  fi
  
  progress_bar $((100 * 100 *it / (40 * 5000)))
  if [ "${it2}" -gt "${max}" ]
  then
      exit 1
  fi
  it2=$((it2+1))
done

sudo pkill -f lecture_event.py

# ================= Lecture du sonar =============

#3.1) Programme de lecture

if ! sudo ../bin/arduino-cli compile --fqbn arduino:avr:uno ../SONAR_ini/SONAR_ini.ino && sudo ../bin/arduino-cli upload -p /dev/tty"$1" --fqbn arduino:avr:uno ../SONAR_ini/SONAR_ini.ino; then
    echo "Erreur, impossible de compiler le sketch arduino"
    exit 1
else
    sed -i 's/COMPILATION_SKETCH_SONAR_COMMUNICATION=0/COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=1/g' valid_var.properties
fi

stty -F /dev/tty"$1" 9600
sleep 2
it2=0
max=2000
while true;do
  output=$(timeout 5s cat /dev/tty"$1" | tee /dev/tty)
  if [[ "${output}" == *"DONE"* ]]
  then
      echo -e "\nCommunication établie"
      sed -i 's/COMMUNICATION_SONAR=0/COMMUNICATION_SONAR=1/g' valid_var.properties
      break
  fi
  
  progress_bar $((100 * 100 *it / (40 * 5000)))
  if [ "${it2}" -gt "${max}" ]
  then
      exit 1
  fi
  it2=$((it2+1))
done

# ================= Lecture du GPS =============

#4.1) Programme de lecture
