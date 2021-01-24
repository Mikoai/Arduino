#define SEG_C 4
#define SEG_E 6
#define SEG_D 5
#define SEG_B 12
#define SEG_G 8
#define SEG_A 11
#define SEG_F 7
#define WYSW_1 10
#define WYSW_2 9
#define BtnUp 2
#define BtnDwn 3

int counter = 50;
unsigned int timer;

void display(int cyfra) {
  switch (cyfra) {
    case 0:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 1:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 2:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 3:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 4:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 5:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 6:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break;
   
    case 7:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break;
    
    case 8:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break;
    
    case 9:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break;
  }
}

void add(){
 counter++; 
}

void subs(){
 counter--; 
}
 
void setup() {
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(WYSW_1, OUTPUT);
  pinMode(WYSW_2, OUTPUT);
  pinMode(BtnUp, INPUT);
  pinMode(BtnDwn, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BtnUp), add, RISING);
  attachInterrupt(digitalPinToInterrupt(BtnDwn), subs, RISING);
}
 
void loop() {
    digitalWrite(WYSW_1, LOW);
    digitalWrite(WYSW_2, HIGH);
    display(counter / 10);
    delay(400);
    digitalWrite(WYSW_1, HIGH);
    digitalWrite(WYSW_2, LOW);
    display(counter % 10);
    delay(400);
  Serial.println(counter);
}

