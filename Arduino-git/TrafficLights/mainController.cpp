#include <Wire.h>
#define vBtn 2
#define hBtn 3
#define nightDip 7

// 1 - Wlacz ruch pionowy
// 2 - Wlacz ruch poziomy
// 3 - Wlacz tryb nocny

int lastCommand;
int newCommand = 1;
int time;

void setup()
{
  pinMode(hBtn, INPUT);
  pinMode(hBtn, INPUT);
  pinMode(nightDip, INPUT);
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  if(newCommand != lastCommand || newCommand == 3){
    Wire.beginTransmission(2);
    Wire.write(newCommand);
    //Serial.println("Sent to 2");
    Wire.endTransmission();
    Wire.beginTransmission(1);
    Wire.write(newCommand);
    //Serial.println("Sent to 1");
    Wire.endTransmission();
    Wire.requestFrom(1, 1);
    Wire.beginTransmission(2);
    Wire.write(newCommand + 10);
    //Serial.println("Sent to 2");
    Wire.endTransmission();
    lastCommand = newCommand;
    time = millis() / 100;
  }
  
  if(digitalRead(hBtn) == HIGH) newCommand = 2;
  else if(digitalRead(vBtn) == HIGH) newCommand = 1;
  else if(digitalRead(nightDip) == HIGH) newCommand = 3;
  else if(lastCommand == 3 && digitalRead(nightDip) == LOW) newCommand = 1;
    
  if((time + 20) < (millis() / 100)){
    if(lastCommand == 1) newCommand = 2;
    else if(lastCommand == 2) newCommand = 1;
  }
}