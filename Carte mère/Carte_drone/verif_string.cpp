#include <Arduino.h>

// ------------------------------ Envoie ------------------------
bool check_sum(String message, int virgule, int max_length, int min_length, char deb, char fin)
{
  int commaCount = 0;
  bool foundStart = false;
  bool foundEnd = false;
  for (int i = 0; i < message.length(); i++) 
  {
      if (message[i] == deb) {
          foundStart = true;
          continue;
      }
      if (foundStart && message[i] == fin) 
      {
          foundEnd = true;
          break;
      }
      if (foundStart && message[i] == ',') 
      {
          commaCount++;
      }
  }

  if (commaCount == virgule && foundStart == true && foundEnd == true) 
  {
      return true;
  } 
  else 
  {
      return false;
  }
}

bool verif_integrite(String message)
{
  int values[4];
  int index = 0;
  int startInd = 2;

  for(int i=startInd; i< message.length(); i++)
  {
    if(message.charAt(i) == ',')
    {
      String val = message.substring(startInd, i);
      values[index] = val.toInt();
      startInd = i + 1;
      index++;
    }
    if(index >= 4)
    {
      break;
    }
    
  }
  if(values[0] > 356 || values[0] < 100)
  {
    return false;
  }
  else if(values[3] > 356 || values[3] < 100)
  {
    return false;
  }
  else if(values[1] > 2 || values[0] < 0)
  {
    return false;
  }
  else if(values[2] > 2 || values[0] < -2)
  {
    return false;
  }
  else
  {
    return true;
  }
}
