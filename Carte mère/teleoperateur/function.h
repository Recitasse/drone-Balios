#ifndef FUNCTION_H
#define FUNCTION_H

// ------------------------------ Envoie ------------------------
bool check_sum(String message, int virgule, int max_length, int min_length, char fin)
{
  int commaCount = 0;
  bool foundStart = false;
  bool foundEnd = false;
  for (int i = 0; i < message.length(); i++) 
  {
      if (message[i] == 'C' || message[i] == 'A' || message[i] == 'S' || message[i] == 'V') {
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
      if(strlen(message.c_str()) <= max_length || strlen(message.c_str()) >= min_length)
      {
        String Psi_test = message.substring(2,5);
        String Psi_pow = message.substring(message.length()-5,message.length()-2);
        if(Psi_test.length() == 3 && Psi_pow.length() == 3)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
  } 
  else 
  {
      return false;
  }
}

bool check_sum_out(String message, int virgule, int max_length, int min_length, char fin)
{
  int commaCount = 0;
  bool foundStart = false;
  bool foundEnd = false;
  for (int i = 0; i < message.length(); i++) 
  {
      if (message[i] == 'V') {
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


#endif
