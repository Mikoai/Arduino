#include <Wire.h>
#define vGreen 13
#define vYellow 12
#define vRed 11
#define hGreen 7
#define hYellow 6
#define hRed 5
#define hWar 4

// 1 - Wlacz ruch pionowy
// 2 - Wlacz ruch poziomy
// 3 - Wlacz tryb nocny

int newCommand;
int lastCommand;
unsigned long time;
int lastTime;

void Rest(){
  digitalWrite(vGreen, LOW);
  digitalWrite(vRed, LOW);
  digitalWrite(hGreen, LOW);
  digitalWrite(hRed, LOW);
  digitalWrite(hWar, LOW);
  delay(500);
  digitalWrite(vYellow, HIGH);
  digitalWrite(hYellow, HIGH);
  delay(5000);
  digitalWrite(vYellow, LOW);
  digitalWrite(hYellow, LOW);
  delay(5000);
}

void change(bool b){
  if(b){
    digitalWrite(hGreen, LOW);
    delay(500);
    digitalWrite(hYellow, HIGH);
    delay(5000);
    digitalWrite(hYellow, LOW);
    digitalWrite(hRed, HIGH);
    delay(5000);
    digitalWrite(vRed, LOW);
    delay(500);
    digitalWrite(vYellow, HIGH);
    delay(5000);
    digitalWrite(vYellow, LOW);
    digitalWrite(vGreen, HIGH);
    delay(2000);
    digitalWrite(hWar, HIGH);
  } else if(!b){
    digitalWrite(hWar, LOW);
    delay(500);
    digitalWrite(vGreen, LOW);
    delay(500);
    digitalWrite(vYellow, HIGH);
    delay(5000);
    digitalWrite(vYellow, LOW);
    digitalWrite(vRed, HIGH);
    delay(5000);
    digitalWrite(hRed, LOW);
    delay(500);
    digitalWrite(hYellow, HIGH);
    delay(5000);
    digitalWrite(hYellow, LOW);
    digitalWrite(hGreen, HIGH);
  }
}

void setup()
{
  pinMode(vGreen, OUTPUT);
  pinMode(vYellow, OUTPUT);
  pinMode(vRed, OUTPUT);
  pinMode(hGreen, OUTPUT);
  pinMode(hYellow, OUTPUT);
  pinMode(hRed, OUTPUT);
  pinMode(hWar, OUTPUT);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Wire.begin(1);
}

void loop()
{
  
}

void receiveEvent(int i){
  newCommand = Wire.read();
  if(newCommand == 1) change(true);
  else if(newCommand == 2) change(false);
  else if(newCommand == 3) Rest();
}

void requestEvent(){
  Wire.write(newCommand); 
}