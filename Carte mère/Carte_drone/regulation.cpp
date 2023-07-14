#include <Arduino.h>
#include "function.h"
#include <math.h>



void redim(float fac_psi, float fac_vx, float fac_vy, float* &Commande)
{
  /*
   *           this->dir[0] = commande.Psi;
          this->dir[1] = commande.X;
          this->dir[2] = commande.Y;
   */
  Commande[0] *= fac_psi;
  Commande[1] *= fac_vx;
  Commande[2] *= fac_vy;
}
