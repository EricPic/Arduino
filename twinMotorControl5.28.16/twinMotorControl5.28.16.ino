/*
  Arduino Starter Kit example
 Project 10  - Zoetrope

 This sketch is written to accompany Project 10 in the
 Arduino Starter Kit

 Parts required:
 two 10 kilohm resistors
 2 momentary pushbuttons
 one 10 kilohm potentiometer
 motor
 9V battery
 H-Bridge

 Created 13 September 2012
 by Scott Fitzgerald
 Thanks to Federico Vanzati for improvements

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
 */

const int controlPin1A = 3;   // connected to pin 7 on the H-bridge
const int controlPin2A = 6;   // connected to pin 2 on the H-bridge
const int enablePinA = 10;    // connected to pin 1 on the H-bridge

const int controlPin1B = 5;   // connected to pin 10 on the H-bridge
const int controlPin2B = 9;   // connected to pin 15 on the H-bridge
const int enablePinB = 11;    // connected to pin 9 on the H-bridge

const int directionSwitchPinA = 8;         //  connected to A switch for direction
const int directionSwitchPinB = 12;        //  connected to B switch for direction

const int onOffSwitchStateSwitchPinA = 13;   //  connected to the switch for turning the motor on and off
const int onOffSwitchStateSwitchPinB = 7;   //  connected to the switch for turning the motor on and off

const int potPinA = A0;         // connected to the potentiometer's output
const int potPinB = A3;         // connected to the potentiometer's output

// create some variables to hold values from your inputs
int onOffSwitchStateA = 0;         // current state of the On/Off switch
int previousOnOffSwitchStateA = 0; // previous position of the on/off switch
int onOffSwitchStateB = 0;         // current state of the On/Off switch
int previousOnOffSwitchStateB = 0; // previous position of the on/off switch

int directionSwitchStateA = 0;           // current state of the direction switch
int previousDirectionSwitchStateA = 0;   // previous state of the direction switch
int directionSwitchStateB = 0;           // current state of the direction switch
int previousDirectionSwitchStateB = 0;   // previous state of the direction switch


int motorEnabledA = 0;   // Turns the motor on/off
int motorSpeedA = 0;     // speed of the motor
int motorDirectionA = 1; // current direction of the motor
int motorEnabledB = 0;   // Turns the motor on/off
int motorSpeedB = 0;     // speed of the motor
int motorDirectionB = 1; // current direction of the motor

void setup() {
  // intialize the inputs and outputs
  pinMode(directionSwitchPinA, INPUT);
  pinMode(directionSwitchPinB, INPUT);
  
  pinMode(onOffSwitchStateSwitchPinA, INPUT);
  pinMode(onOffSwitchStateSwitchPinB, INPUT);
  
  pinMode(controlPin1A, OUTPUT);
  pinMode(controlPin2A, OUTPUT);
  pinMode(enablePinA, OUTPUT);

  pinMode(controlPin1B, OUTPUT);
  pinMode(controlPin2B, OUTPUT);
  pinMode(enablePinB, OUTPUT);

  // pull the enable pin LOW to start
  digitalWrite(enablePinA, LOW);
  digitalWrite(enablePinB, LOW);
}

void loop() {
  // read the value of the on/off switch
  onOffSwitchStateA = digitalRead(onOffSwitchStateSwitchPinA);
  onOffSwitchStateB = digitalRead(onOffSwitchStateSwitchPinB);
  delay(100);

  // read the value of the direction switch
  directionSwitchStateA = digitalRead(directionSwitchPinA);
  directionSwitchStateB = digitalRead(directionSwitchPinB);
  delay(100);

  // read the value of the pot and divide by 4 to get
  // a value that can be used for PWM
  motorSpeedA = analogRead(potPinA) / 4;
  motorSpeedB = analogRead(potPinB) / 4;

  // if the on/off button changed state since the last loop()
  if (onOffSwitchStateA != previousOnOffSwitchStateA) {
    // change the value of motorEnabled if pressed
    if (onOffSwitchStateA == HIGH) {
      motorEnabledA = !motorEnabledA;
      }
  }
  if (onOffSwitchStateB != previousOnOffSwitchStateB) {
    // change the value of motorEnabled if pressed
    if (onOffSwitchStateB == HIGH) {
      motorEnabledB = !motorEnabledB;
    }
  }

  // if the direction button A changed state since the last loop()
  if (directionSwitchStateA != previousDirectionSwitchStateA) {
    // change the value of motorDirection if pressed
    if (directionSwitchStateA == HIGH) {
      motorDirectionA = !motorDirectionA;
    }
  }
  // if the direction button B changed state since the last loop()
  if (directionSwitchStateB != previousDirectionSwitchStateB) {
    // change the value of motorDirection if pressed
    if (directionSwitchStateB == HIGH) {
      motorDirectionB = !motorDirectionB;
    }
  }
  
  // change the direction the motor spins by talking
  // to the control pins on the H-Bridge
  if (motorDirectionA == 1) {
    digitalWrite(controlPin1A, HIGH);
    digitalWrite(controlPin2A, LOW);
  } else {
    digitalWrite(controlPin1A, LOW);
    digitalWrite(controlPin2A, HIGH);
  }

  if (motorDirectionB == 1) {
    digitalWrite(controlPin1B, HIGH);
    digitalWrite(controlPin2B, LOW);
  } else {
    digitalWrite(controlPin1B, LOW);
    digitalWrite(controlPin2B, HIGH);
  }

  // if the motor is supposed to be on
  if (motorEnabledA == 1) {
    // PWM the enable pin to vary the speed
    analogWrite(enablePinA, motorSpeedA);
     } else { // if the motor is not supposed to be on
    //turn the motor off
    analogWrite(enablePinA, 0);
  }
  if (motorEnabledB == 1) {
    // PWM the enable pin to vary the speed
    analogWrite(enablePinB, motorSpeedA);
     } else { // if the motor is not supposed to be on
    //turn the motor off
    analogWrite(enablePinB, 0);
     }
  // save the current On/Offswitch state as the previous
  previousDirectionSwitchStateA = directionSwitchStateA;
  previousDirectionSwitchStateB = directionSwitchStateB;
    
}




