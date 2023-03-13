#!/bin/bash

#3.1) Programme de lecture
sudo ../bin/arduino-cli compile --fqbn arduino:avr:uno ../SONAR_ini/SONAR_ini.ino && sudo ../bin/arduino-cli upload -p /dev/tty"$1" --fqbn arduino:avr:uno ../SONAR_ini/SONAR_ini.ino

if [ $? -ne 0 ]; then
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
  
  progress_bar $((it2 * 100 / 5000 * 100 / 40))
  if [ "${it2}" -gt "${max}" ]
  then
      exit 1
  fi
  it2=$((it2+1))
done
