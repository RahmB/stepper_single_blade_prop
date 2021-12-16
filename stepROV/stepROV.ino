//acts as a single bladed propellor on an Remote Operated Vehicle
//changign the speed of propellor through rotation creates turning moment
//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 64;

//connect buttons to these analog inputs
//the other pin on same side of the button to ground 
const int b0 = A0;
const int b1 = A1;
const int b2 = A2;

//initializes button state readings
int b0state = 0;
int b1state = 0;
int b2state = 0;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
//plug stepper pins into digital 8,9,10,11
//connect 5v and ground to driver
Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  //(Stepper Library sets pins as outputs)
  Serial.begin(9600);
  //using INPUT_PULLUP utilizes built in resistor
  //stablizes readings
  pinMode(b0, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
}

void loop() {
b1state = digitalRead(b1);
b0state = digitalRead(b0);
b2state = digitalRead(b2);
forward();
while(b1state == LOW){
  Serial.println("turning right");
  Serial.println("b1 is " + String(b1state));
  Serial.println("b0 is " + String(b0state));
  right();
  //have to check variable again in order to break loop
  b1state = digitalRead(b1);

}
while(b0state == LOW){
  Serial.println("turning left");
  Serial.println("b1 is " + String(b1state));
  Serial.println("b0 is " + String(b0state));
  left();
  //have to check variable again in order to break loop
  b0state = digitalRead(b0);

}
while(b2state == LOW){
  Serial.println("Stop");
  Serial.println("b1 is " + String(b1state));
  Serial.println("b0 is " + String(b0state));
  halt();
  //have to check variable again in order to break loop
  //hit arduino reset button to start again
  b2state = digitalRead(b2);

}
}


void left(){  
  Serial.println("left called");
  //turns faster on right side of rotation
  //pushes craft left
    myStepper.setSpeed(300);
    myStepper.step(-1019);
    myStepper.setSpeed(150);
    myStepper.step(-1019);
  }

void right(){
    Serial.println("right called");
  //turns faster on left side of rotation
  //pushes craft right
    myStepper.setSpeed(150);
    myStepper.step(-1019);
    myStepper.setSpeed(300);
    myStepper.step(-1019);

}

void forward(){
    Serial.println("forward called");
    myStepper.setSpeed(300);
    myStepper.step(-2038);
}

void halt(){
      Serial.println("Stop");
    myStepper.setSpeed(0);

}
