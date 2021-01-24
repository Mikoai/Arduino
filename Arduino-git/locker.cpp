#include <LiquidCrystal.h>
#include <Keypad.h>
#include <IRremote.h>
#define LedR 6
#define LedG 7
#define RECEIVER_PIN 3

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const byte ROWS = 4;
const byte COLS = 4;
char hexKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte colPins[COLS] = {A3, A2, A1, A0};
byte rowPins[ROWS] = {4, 5, A5, A4};
Keypad keys = Keypad(makeKeymap(hexKeys), rowPins, colPins, ROWS, COLS);

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
  	digitalWrite(LedR, HIGH);
	digitalWrite(LedG, LOW);
  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Zamek zamkniety");
  	lcd.setCursor(0, 1);
  	lcd.print("A-klaw POW-pilot");
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

String accessMode(bool klaw){
  	String guess = "";
  	if(klaw){
    	char key = keys.getKey();
      
        while(guess.length() < 4){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Prosze podac PIN");
            lcd.setCursor(0, 1);
            lcd.print(guess);
            if((key = keys.waitForKey()) == 'D') guess.remove(guess.length()-1, 1);
            else guess += key;
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Prosze podac PIN");
        lcd.setCursor(0, 1);
        lcd.print(guess);
        delay(500);
  	}
  
  	if(!klaw){
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
  	}
  	
  	return guess;
}

bool check(String a){
    if(a.equals(passwd)) return true;
    else return false;
}

void change(bool klaw){
  	unlock();
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Zmiana obecnego");
    lcd.setCursor(0, 1);
    lcd.print("PINu");
    delay(500);
  	passwd = accessMode(klaw);
	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PIN pomyslnie");
    lcd.setCursor(0, 1);
    lcd.print("zmieniony");
    delay(500);
}

void keyInput(char key){
 if((key = keys.waitForKey()) == 'A'){
    if(check(accessMode(true))) unlock();
    else error();
  } else if((key = keys.waitForKey()) == 'C'){
    if(check(accessMode(true))) change(true);
    else error();
  }
  lcd.clear();
  lock();
}

void pilotInput(){
  if(results.value == 0xFD00FF){
    if(check(accessMode(false))) unlock();
    else error();
  } else if(results.value == 0xFDB04F){
    if(check(accessMode(false))) change(false);
    else error();
  }
  lcd.clear();
  lock();
  receiver.resume();
}

void setup()
{
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  receiver.enableIRIn();
  lock();
}

void loop()
{
  	char key = keys.getKey();
  
  	if(receiver.decode(&results)) pilotInput();
	if(key != NULL) keyInput(key);
  
}