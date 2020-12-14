
#include<NewPing.h>
int trig_pin = A5;
int echo_pin = A4;
NewPing sonar(trig_pin, echo_pin, 300);

int distance = 100;

//Line Tracking IO define
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
 



void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);

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

}

void loop() {
  // put your main code here, to run repeatedly:

distance = readPing();
Serial.println(distance);



  if(distance > 10){
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
  if(distance <= 10){
       stop();
       
  }
  
}

void forward(){
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

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
