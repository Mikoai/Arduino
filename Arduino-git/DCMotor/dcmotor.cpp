#define leftBtn 2
#define stopBtn 3
#define rightBtn 4
#define rightL 6
#define leftL 5
#define rightDip 8
#define leftDip 9

int i = 0;

void moveRight(){
  digitalWrite(leftL, LOW);
  digitalWrite(rightL, HIGH);
  i = 2;
}

void moveLeft(){
 digitalWrite(rightL, LOW);
 digitalWrite(leftL, HIGH);
 i = 1;
}

void stop(){
  digitalWrite(rightL, LOW);
  digitalWrite(leftL, LOW);
  i = 0;
}

void setup()
{
  pinMode(leftBtn, INPUT);
  pinMode(stopBtn, INPUT);
  pinMode(rightBtn, INPUT);
  pinMode(rightL, OUTPUT);
  pinMode(leftL, OUTPUT);
  pinMode(rightDip, INPUT);
  pinMode(leftDip, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(stopBtn) == HIGH || (digitalRead(rightDip) == HIGH && i == 2) || (digitalRead(leftDip) == HIGH && i == 1)){
   stop();
  }
  if(digitalRead(rightBtn) == HIGH && digitalRead(rightDip) == LOW){
    moveRight();
  }
  if(digitalRead(leftBtn) == HIGH && digitalRead(leftDip) == LOW){
    moveLeft();
  }
}