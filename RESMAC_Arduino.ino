#include <Stepper.h>
#include <Servo.h>


//Stepper Information
#define limitswitch 7
const float STEPS_PER_REV = 32;
const float GEAR_RED =64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
Stepper steppermotor(STEPS_PER_REV,2,4,3,5);

//Servo Information
Servo myservo;
int pos = 0;

//Relay Information
#define RelayWater A4
int waterpumpTimeRun = 5000;
#define RelayDrill A5
int drillTimeRun= 5000;

//DC Motor Information
int enB=12;
#define in3 A3
#define in4 A2
int BotTimeRun = 5000;
int BotSpeed = 1000;
int motorSpeedB=1000;

//Stepper Home Position
void StepperHome(){
  while(digitalRead(limitswitch) == HIGH){
    StepsRequired=(-5);
    steppermotor.setSpeed(400);
    steppermotor.step(StepsRequired);
    delay(10);
    //Serial.println(digitalRead(limitswitch)); 
  }
  delay(5000);

}

void SeedandWater(){

  //myservo.write(pos);

  delay(100);
  myservo.write(35);
  delay(300);
  myservo.write(pos);
  //delay(1000);

  digitalWrite(RelayWater,HIGH);
  delay(waterpumpTimeRun);
  digitalWrite(RelayWater,LOW);
  
}

void StepperDown(){
  StepsRequired=(STEPS_PER_OUT_REV/2);
  steppermotor.setSpeed(700);
  steppermotor.step(StepsRequired);
}

void StepperUp(){
  StepsRequired=-(STEPS_PER_OUT_REV/2);
  steppermotor.setSpeed(700);
  steppermotor.step(StepsRequired);
}

void DrillingMotio(){
  digitalWrite(RelayDrill,HIGH);
  StepperDown();
  delay(drillTimeRun);
  StepperUp();
  digitalWrite(RelayDrill,LOW);
}

void ForwardBotMotion(){
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,BotSpeed);
  Serial.print("in3 is ...");
  Serial.println(digitalRead(in3));
  delay(BotTimeRun);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(BotTimeRun);
  Serial.print("in3 is ...");
  Serial.println(digitalRead(in3));
}

void forwardOne(){
  /*Turn on Motor A
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,motorSpeedA);*/

  // Turn on Motor B
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,motorSpeedB);

  delay (5000);

  //digitalWrite(in1,LOW);
  //digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay (5000);
}



void setup(){
  Serial.begin(9600);

  //Servo
  myservo.attach(9);
  myservo.write(pos);

  //Stepper
  pinMode(limitswitch,INPUT);
  StepperHome();

  //WaterPump
  pinMode(RelayWater,OUTPUT);
  pinMode(RelayDrill,OUTPUT);

  //DC Motor
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enB,OUTPUT);
 

}


void loop(){
if (digitalRead(limitswitch)==LOW){
  ForwardBotMotion();
  delay(2000);
  DrillingMotio();
  delay(500);
  SeedandWater();
  delay(1000);
} 
}
