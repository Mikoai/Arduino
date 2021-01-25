#include <LiquidCrystal.h>
#include <IRremote.h>
#define LedR 6
#define LedG 7
#define RECEIVER_PIN 3
#define trigPin 4
#define echoPin 5
#define infraPin 2

unsigned long startTime = 0;
bool flag = false;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

IRrecv receiver(RECEIVER_PIN);
decode_results results;
unsigned long key_value = 0;


String passwd = "1337";

char pilotKey(){
  if(receiver.decode(&results)){
    if (results.value == 0xFFFFFFFF) results.value = key_value;
     switch (results.value) {
      case 0xFD00FF: // POWER
        key_value = results.value;
        receiver.resume();
        return ('P');
      case 0xFD807F: // VOL+
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD40BF: // FUNC/STOP
        key_value = results.value;
        receiver.resume();
        return ('A');
      case 0xFD20DF: // │◄◄
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFDA05F: // ►││
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD609F: // ►►│
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD10EF: // ▼
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD906F: // VOL-
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD50AF: // ▲
        key_value = results.value;
        receiver.resume();
        return (NULL);
      case 0xFD30CF: // 0
        key_value = results.value;
        receiver.resume();
        return ('0');
      case 0xFDB04F: // EQ
        key_value = results.value;
        receiver.resume();
        return ('C');
      case 0xFD708F: // ST/REPT
        key_value = results.value;
        receiver.resume();
        return ('D');
      case 0xFD08F7: // 1
        key_value = results.value;
        receiver.resume();
        return ('1');
      case 0xFD8877: // 2
        key_value = results.value;
        receiver.resume();
        return ('2');
      case 0xFD48B7: // 3
        key_value = results.value;
        receiver.resume();
        return ('3');
      case 0xFD28D7: // 4
        key_value = results.value;
        receiver.resume();
        return ('4');
      case 0xFDA857: // 5
        key_value = results.value;
        receiver.resume();
        return ('5');
      case 0xFD6897: // 6
        key_value = results.value;
        receiver.resume();
        return ('6');
      case 0xFD18E7: // 7
        key_value = results.value;
        receiver.resume();
        return ('7');
      case 0xFD9867: // 8
        key_value = results.value;
        receiver.resume();
        return ('8');
      case 0xFD58A7: // 9
        key_value = results.value;
        receiver.resume();
        return ('9');
    }
  }
}

void unlock(){
  	digitalWrite(LedR, LOW);
	digitalWrite(LedG, HIGH);
  	lcd.clear();
 	lcd.setCursor(0, 0);
  	lcd.print("Poprawne haslo");
  	lcd.setCursor(0, 1);
  	lcd.print("Zamek otwarty");
  	delay(2000);
}

void lock(){
	digitalWrite(LedG, LOW);
  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Zamek");
  	lcd.setCursor(0, 1);
  	lcd.print("zamkniety");
}

void error(){
  	lcd.clear();
 	lcd.setCursor(0, 0);
  	lcd.print("ERROR");
  	lcd.setCursor(0, 1);
  	lcd.print("Bledne haslo");
  	delay(2000);
  	lcd.clear();
  	lock();
}

void alarm(){
 	digitalWrite(LedR, HIGH);
  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("!!ALARM!!");
}

String accessMode(){
  	String guess = "";

      	receiver.resume();
      	lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Prosze podac PIN");
        lcd.setCursor(0, 1);
        lcd.print(guess);
      	char key;
    	while(guess.length() < 4){
          key = NULL;
          if((key = pilotKey()) != NULL){
            if(key == 'D') guess.remove(guess.length()-1, 1);
            else guess += key;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Prosze podac PIN");
            lcd.setCursor(0, 1);
            lcd.print(guess);
          }
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Prosze podac PIN");
        lcd.setCursor(0, 1);
        lcd.print(guess);
      	receiver.resume();
        delay(500);
  	
  	return guess;
}

bool check(String a){
  	if(a.equals(passwd)){
      digitalWrite(LedR, LOW);
      flag = true;
      return true;
    }
    else return false;
}

void change(){
  	unlock();
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Zmiana obecnego");
    lcd.setCursor(0, 1);
    lcd.print("PINu");
    delay(500);
  	passwd = accessMode();
	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PIN pomyslnie");
    lcd.setCursor(0, 1);
    lcd.print("zmieniony");
    delay(500);
}


void pilotInput(){
  if(results.value == 0xFD00FF){			//POWER
    if(check(accessMode())) unlock();
    else error();
  } else if(results.value == 0xFDB04F){		//EQ
    if(check(accessMode())) change();
    else error();
  }
  lcd.clear();
  lock();
  receiver.resume();
}

int sonicDist() {
  long czas, dystans;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 29;				//normally 58 but here 29 works

  return dystans;
}

unsigned long checkTime(){
  	unsigned long newTime = millis();
 	return newTime - startTime;
}

void allert(){
  	startTime = millis();
  	int sec = 10;
  	int last = 0;
	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wykryto ruch");
    lcd.setCursor(0, 1);
    lcd.print("Podaj PIN 10s");
  	while(sec != 10){
      if(receiver.decode(&results)) pilotInput();
      if(last != (checkTime() / 1000)){
        sec--;
      }
    }
  if(flag){
    flag = false;
  }else{
    alarm();
  }
}

void setup()
{
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  receiver.enableIRIn();
  lock();
  flag = false;
}

void loop()
{  
  	if(receiver.decode(&results)) pilotInput();
  	if(sonicDist() < 200 || digitalRead(infraPin) == 1) allert();
  
}