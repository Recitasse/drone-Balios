#include <Servo.h>
#include <Arduino.h>
#include "function.h"

class MOTEURS
{
  private:
    int TL_MOT;
    int TR_MOT;
    int BL_MOT;
    int BR_MOT;
    int tl_prop;
    int tr_prop;
    int bl_prop;
    int br_prop;
    Servo TLesc;
    Servo TResc;
    Servo BLesc;
    Servo BResc;
  public:
  
    MOTEURS(int TL_MOT, int TR_MOT, int BL_MOT, int BR_MOT)
    {
      this->TL_MOT=TL_MOT;
      this->TR_MOT=TR_MOT;
      this->BL_MOT=BL_MOT;
      this->BR_MOT=BR_MOT;
    }

    void MOTEUR_INIT()
    {
      TLesc.attach(TL_MOT); 
      TResc.attach(TR_MOT); 
      BLesc.attach(BL_MOT); 
      BResc.attach(BR_MOT); 
      
      TLesc.writeMicroseconds(1000); // Envoyer le signal minimum pour l'ESC
      TResc.writeMicroseconds(1000); 
      BLesc.writeMicroseconds(1000);
      BResc.writeMicroseconds(1000); 
      
      delay(2000);  // Attendre 2 secondes pour l'étalonnage de l'ESC
      
      TLesc.writeMicroseconds(1500); // Envoyer le signal minimum pour l'ESC
      TResc.writeMicroseconds(1500); 
      BLesc.writeMicroseconds(1500);
      BResc.writeMicroseconds(1500); 
    }

    void propulse(float* Prop)
    {
      this->tl_prop = Prop[0];
      this->tr_prop = Prop[1];
      this->bl_prop = Prop[2];
      this->br_prop = Prop[3];
      TLesc.writeMicroseconds(tl_prop); // Envoyer le signal minimum pour l'ESC
      TResc.writeMicroseconds(tr_prop); 
      BLesc.writeMicroseconds(bl_prop);
      BResc.writeMicroseconds(br_prop); 
    }

    void propulse_tl(int tl_prop)
    {
      this->tl_prop = tl_prop;
      TLesc.writeMicroseconds(tl_prop); // Envoyer le signal minimum pour l'ESC
    }

    void propulse_tr(int tr_prop)
    {
      this->tr_prop = tr_prop;
      TResc.writeMicroseconds(tr_prop); // Envoyer le signal minimum pour l'ESC
    }

    void propulse_br(int br_prop)
    {
      this->br_prop = br_prop;
      BResc.writeMicroseconds(br_prop); // Envoyer le signal minimum pour l'ESC
    }

    void propulse_bl(int bl_prop)
    {
      this->bl_prop = bl_prop;
      BLesc.writeMicroseconds(bl_prop); // Envoyer le signal minimum pour l'ESC
    }
};
