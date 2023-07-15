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
    float Prop[4] = {0,0,0,0};
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

      Serial.println("Initialisation des moteurs.");
      
      TLesc.writeMicroseconds(1000); // Envoyer le signal minimum pour l'ESC
      TResc.writeMicroseconds(1000); 
      BLesc.writeMicroseconds(1000);
      BResc.writeMicroseconds(1000); 
      
      delay(2000);  // Attendre 2 secondes pour l'étalonnage de l'ESC
      Serial.print("Vérification.");
      
      TLesc.writeMicroseconds(1500);
      TResc.writeMicroseconds(1500); // 2e type soit 0
      BLesc.writeMicroseconds(1500);
      BResc.writeMicroseconds(1500); // 2e soit 0
      Serial.println("Moteurs prêts !");
    }

    void propulse(float* Prop)
    {
      this->tl_prop = Prop[2];
      this->tr_prop = Prop[1];
      this->bl_prop = Prop[3];
      this->br_prop = Prop[0];

      // Recalibrage des esc différents

      this->tr_prop -= 500;
      this->tl_prop -= 500;
      
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

    // ============== Partie régulation ==================

    void PID_manuel(float* states, float* Commande)
    {
      redim(4,2,2,Commande);
      
      regul VPsi;
      regul Vx;
      regul Vy;

      // Pour Vx ====== Kp : 5, Ki : 0.1, Kd : 0 ==================

      Vx.erreur = Commande[1] - 5*states[0];
      Vx.integral += Vx.erreur;
      Vx.erreurm1 = Vx.erreur - Vx.erreurm1;
      Vx.commande = (5*Vx.erreur + 0.5*Vx.integral + 0.3*Vx.derive);
      Vx.erreurm1 = Vx.erreur;


      // Pour Vy ====== Kp : 5, Ki : 0, Kd : 0.3 ==================
      
      Vy.erreur = Commande[2] - 5*states[1];
      Vy.integral += Vy.erreur;
      Vy.erreurm1 = Vy.erreur - Vy.erreurm1;
      Vy.commande = (5*Vy.erreur + 0.5*Vy.integral + 0.3*Vy.derive);
      Vy.erreurm1 = Vy.erreur;

      // Pour VPsi ====== Kp : 1, Ki : 0, Kd : 0.05 ==================

      float maxr = 90;
      
      VPsi.erreur = Commande[0]*maxr/4 - states[2],
      VPsi.integral += VPsi.erreur;
      VPsi.erreurm1 = VPsi.erreur - VPsi.erreurm1;
      VPsi.commande = (1*VPsi.erreur + 0*VPsi.integral + 0.3*VPsi.derive);
      VPsi.erreurm1 = VPsi.erreur;

      float Prop[4] = {0,0,0,0};
      float dir[3] = {VPsi.commande, Vx.commande, Vy.commande};

      joystick_lec(dir, Prop, 1);

      for(int i=0; i<2; i++)
      {
        Prop[i] = Prop[i]*825/12+1150;
        if(Prop[i] < 1150)
        {
          Prop[i] = 1150;
        }
      }
      for(int i=2; i<4; i++)
      {
        Prop[i] = Prop[i]*500/12+1500;
        if(Prop[i] < 1500)
        {
          Prop[i] = 1500;
        }
      }
      
      for(int i=0; i<4; i++)
      {
        if(Prop[i] > 2000)
        {
          Prop[i] = 2000;
        }
        Serial.print(int(Prop[i]));
        Serial.print("\t");
      }
      Serial.print("\n");

      BLesc.writeMicroseconds(int(Prop[3]));
      BResc.writeMicroseconds(int(Prop[2]));
      TLesc.writeMicroseconds(int(Prop[0]));
      TResc.writeMicroseconds(int(Prop[1]));

    }



    
};
