#include <Wire.h>
#define hRed 13
#define hGreen 12
#define vRed 7
#define vGreen 6

// 1 - Wlacz ruch pionowy
// 2 - Wlacz ruch poziomy
// 3 - Wlacz tryb nocny

int newCommand;
int lastCommand;
unsigned long time;
int lastTime;

void Rest(){
 digitalWrite(vRed, LOW);
 digitalWrite(vGreen, LOW); 
 digitalWrite(hRed, LOW); 
 digitalWrite(hGreen, LOW); 
}

void Off(bool b){
  if(b){
   digitalWrite(vGreen, LOW);
   digitalWrite(vRed, HIGH);  
  } else if(!b){
   digitalWrite(hGreen, LOW);
   digitalWrite(hRed, HIGH); 
  }
}

void On(bool b){
  if(b){
   digitalWrite(vRed, LOW);
   digitalWrite(vGreen, HIGH);  
  } else if(!b){
   digitalWrite(hRed, LOW);
   digitalWrite(hGreen, HIGH); 
  }
}

void setup()
{
  pinMode(vRed, OUTPUT);
  pinMode(vGreen, OUTPUT);
  pinMode(hRed, OUTPUT);
  pinMode(hGreen, OUTPUT);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.begin(2);
}

void loop()
{
  
}

void receiveEvent(int i){
  newCommand = Wire.read();
  if(newCommand == 1) Off(true);
  else if(newCommand == 11) On(false);
  else if(newCommand == 2) Off(false);
  else if(newCommand == 12) On(true);
  else if(newCommand == 3) Rest();
}