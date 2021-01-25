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

int counter = 53;
bool flag;

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
  if(counter < 99){
 	counter++; 
  }
}

void subs(){
 if(counter > 0){
 	counter--; 
  }
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
  attachInterrupt(digitalPinToInterrupt(BtnUp), add, FALLING);
  attachInterrupt(digitalPinToInterrupt(BtnDwn), subs, FALLING);
  

  //set timer0 interrupt at 1kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR0A = 249;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

sei();//allow interrupts

}
 
void loop() {

}

ISR(TIMER0_COMPA_vect){
  digitalWrite(WYSW_1, HIGH);
  digitalWrite(WYSW_2, HIGH);
  if(flag){
    display(counter / 10);
  	    digitalWrite(WYSW_1, LOW);
    flag = !flag;
  } else{
    display(counter % 10);
    digitalWrite(WYSW_2, LOW);
    flag = !flag;
  }
}