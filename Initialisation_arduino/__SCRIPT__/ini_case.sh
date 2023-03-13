#!/bin/bash

function decompose() {
  local num=$1
  local pow=0
  local arr=()

  while [ $num -gt 0 ]; do
    if [ $((num & 1)) -eq 1 ]; then
      arr+=("$((2**pow))")
    fi
    num=$((num >> 1))
    pow=$((pow+1))
  done

  echo "${arr[@]}"
}

# Example usage

# 1 -> Pour charger la carte & le joystick
# 2 -> Pour charger le joystick
# 4 -> pour charger la carte
# 8 -> pour attendre le gps
# 16 -> Pour attendre le sonar
# 32 -> Pour attendre gyroscope
# 64 -> Pour l'insertion dans la base de donnée
# 128 -> Compilation du script terminal


result=$(decompose $1)
echo "Result: $result"

for el in "${result}"; do
   if [ "${el}" == "1" ]; then
   
   
   sed -i 's/BRANCHEMENT_CARTE=1
SELECTION_CARTE=1
COMPILATION_SKETCH_CARTE_COMMUNICATION=1
COMMUNICATION_CARTE=1

BRANCHEMENT_JOYSTICK=1
SELECTION_JOYSTICK=1
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=1
LECTURE_EVENT=1
COMMUNICATION_JOYSTICK=1/BRANCHEMENT_CARTE=0
SELECTION_CARTE=0
COMPILATION_SKETCH_CARTE_COMMUNICATION=0
COMMUNICATION_CARTE=0

BRANCHEMENT_JOYSTICK=0
SELECTION_JOYSTICK=0
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=0
LECTURE_EVENT=0
COMMUNICATION_JOYSTICK=0/g' valid_var.properties
   
   ;;
   
   "Hardware")
   
   sed -i 's/BRANCHEMENT_CARTE=1
SELECTION_CARTE=1
COMPILATION_SKETCH_CARTE_COMMUNICATION=1
COMMUNICATION_CARTE=1

BRANCHEMENT_JOYSTICK=1
SELECTION_JOYSTICK=1
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=1
LECTURE_EVENT=1
COMMUNICATION_JOYSTICK=1/BRANCHEMENT_CARTE=0
SELECTION_CARTE=0
COMPILATION_SKETCH_CARTE_COMMUNICATION=0
COMMUNICATION_CARTE=0

BRANCHEMENT_JOYSTICK=0
SELECTION_JOYSTICK=0
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=0
LECTURE_EVENT=0
COMMUNICATION_JOYSTICK=0/g' valid_var.properties
   
   ;;
     
   "joystick")
   
   sed -i 's/BRANCHEMENT_JOYSTICK=1
SELECTION_JOYSTICK=1
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=1
LECTURE_EVENT=1
COMMUNICATION_JOYSTICK=1/BRANCHEMENT_JOYSTICK=0
SELECTION_JOYSTICK=0
COMPILATION_SKETCH_JOYSTICK_COMMUNICATION=0
LECTURE_EVENT=0
COMMUNICATION_JOYSTICK=0/g' valid_var.properties
   
   ;;
   
   "Carte")
   
   sed -i 's/BRANCHEMENT_CARTE=1
SELECTION_CARTE=1
COMPILATION_SKETCH_CARTE_COMMUNICATION=1
COMMUNICATION_CARTE=1/BRANCHEMENT_CARTE=0
SELECTION_CARTE=0
COMPILATION_SKETCH_CARTE_COMMUNICATION=0
COMMUNICATION_CARTE=0/g' valid_var.properties
   
   ;;
   
   "GPS")
   
   sed -i 's//g' valid_var.properties
   
   ;;
   
   "SONAR")
   
   sed -i 's//g' valid_var.properties
   
   ;;
   
   "GYRO")
   
   sed -i 's//g' valid_var.properties
   
   ;;
   
   "reset")
   
   sed -i 's//g' valid_var.properties
   
   ;;
   
   *);;
   
esac
