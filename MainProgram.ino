
#include<Servo.h>
#include<NewPing.h>

//ultrasonic sensor***************************************
int trig_pin = A5;
int echo_pin = A4;
NewPing sonar(trig_pin, echo_pin, 300);
int distance = 100;

//Line Tracking IO define*********************************
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 130

//robot arm**********************************************
int shoulder = 0;
int elbow = 1;
int wrist = 2;
int gripper = 3;
Servo myServo[4] = {};
Servo myserv;

//functions & methods*************************************

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
Serial.println(cm);
}

  void stow() {
  moveTo(30, 25, myServo[shoulder]);
  moveTo(0, 15, myServo[elbow]);
  moveTo(170, 15, myServo[wrist]);
  moveTo(0, 15, myServo[gripper]);
}

void forward() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}
 
void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}
 
void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}
 
void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 
 
void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println(distance);
   Serial.println("Stop!");
} 

int pos = 0;
int pos1 = 0;
void moveTo(int position, int speed, Servo lserv){
  if(position > pos){
    for(pos = pos1; pos <= position; pos+=1){
      lserv.write(pos);
      pos1 = pos;
      delay(speed);
    }
  }
  else {
    for (pos = pos1; pos >= position; pos -= 1){
      lserv.write(pos);
      pos1 = pos;
      delay(speed);
    }
  }
}

void setup() {
  //ultrasonic sensor***************************************
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);

  //test sensor readings***********************************
   distance = readPing();
  delay(100);
  Serial.println(distance);
  distance = readPing();
  delay(100);
  Serial.println(distance);
  distance = readPing();
  delay(100);
  Serial.println(distance);
  distance = readPing();
  delay(100);
  Serial.println(distance);

  //robot arm setup***************************************
  myServo[shoulder].attach(25);
  myServo[elbow].attach(27);
  myServo[wrist].attach(31);
  myServo[gripper].attach(33);



  //initialize a postion**********************************
  stow();
}

void loop() {
  distance = readPing();
  //Serial.println(distance);
  
  if(distance > 20){
    if(LT_M){
      forward();
    }
    else if(LT_R) { 
      right();
      while(LT_R);                             
    }   
    else if(LT_L) {
      left();
      while(LT_L);  
    }
  }
  
 
 
 
 if(distance <= 20){ 
    moveTo(100, 15, myServo[wrist]);
    delay(1000);
    moveTo(80, 15, myServo[gripper]);
    delay(1000);
    moveTo(150, 15, myServo[elbow]);
    delay(1000);
    moveTo(20, 35, myServo[shoulder]);
    delay(1000);
    moveTo(33, 15, myServo[gripper]);
    delay(1000);
    moveTo(90, 25, myServo[elbow]);
    delay(1000);
    moveTo(40, 30, myServo[shoulder]);
    delay(1000);

    moveTo(140, 20, myServo[shoulder]);
    delay(1000);
    moveTo(35, 20, myServo[elbow]);
    delay(1000);
    moveTo(90, 20, myServo[wrist]);
    delay(1000);
    moveTo(80, 15, myServo[gripper]);
    delay(1000);

    stow();
 }
 
 
  
}
  
