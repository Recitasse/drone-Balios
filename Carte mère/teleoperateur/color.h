class COLOR
{
  private:
    int r;
    int g;
    int j;
    int b;
    bool receive = false;
    float proxi;
  public:
    COLOR(int r, int g, int j, int b)
    {
      this->r=r;
      this->g=g;
      this->j=j;
      this->b=b;
    }

    COLOR_INIT()
    {
      pinMode(r, OUTPUT);
      pinMode(g, OUTPUT);
      pinMode(j, OUTPUT);
      pinMode(b, OUTPUT);
    }

    void radio_data(bool receive)
    {
      this->receive = receive;
      if(receive){digitalWrite(b, HIGH);}
      else{digitalWrite(b, LOW);}
    }

    void detecteur_prox(float proxi)
    {
      this->proxi=proxi;
      if(proxi > 5){
        digitalWrite(g, HIGH);
        digitalWrite(r, LOW);
        digitalWrite(j, LOW);
      }
      else if(proxi <= 5 && proxi > 2){
        digitalWrite(g, LOW);
        digitalWrite(r, LOW);
        digitalWrite(j, HIGH);
      }
      else if(proxi <2){
        digitalWrite(g, LOW);
        digitalWrite(r, HIGH);
        digitalWrite(j, LOW);
      }
      else
      {
        digitalWrite(g, LOW);
        digitalWrite(r, HIGH);
        digitalWrite(j, LOW);
      }
    }

    
}
