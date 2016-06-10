#include <Servo.h>  //Load the Servo Library

int trigPin[] = {2,6,9,12};  //Sensor Trig pin connected to AR pin 13
int echoPin[] = {3,7,10,13};  //Sensor Echo pin connected to AR pin 11
int servoControlPin = 11;  //Servo Control pin connected to Ar pin 6

float pingTime[4];  //Time for ping to travel to target and return
float targetDistance[4];  //Distance from sensor to target
float speedOfSound=776.5;  //Speed of sound in Miles per hour (77 degrees F)
float servoAngle;  //Variable for the angle of the servo

Servo myPointer;  //Create a Servo object called myPointer

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //Turn on Serial Port
  pinMode(servoControlPin, OUTPUT);  //Servo control Pin is an output

  int i;
  for(i=0; i<4; i++){
    pinMode(trigPin[i], OUTPUT);  //Sensor trig pin is an output
    pinMode(echoPin[i], INPUT);  //Sensor echo pin is an input

  myPointer.attach(servoControlPin); //Tell AR where the servo is connected
}
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(i=0; i<4; i++){
    digitalWrite(trigPin[i], LOW);  //Set trigger pin low
    delayMicroseconds(2000);  //Pause to let signal settle
    digitalWrite(trigPin[i], HIGH);  //Set trigger pin high
    delayMicroseconds(15);  //Pause in high state
    digitalWrite(trigPin[i], LOW);  //Bring Trig pin back to low

    pingTime[i] = pulseIn(echoPin[i], HIGH);  //Measure pingTime at echoPin in microseconds
    pingTime[i] = pingTime[i]/1000000;  //converts ping time to seconds
    pingTime[i] = pingTime[i]/3600.;  //converts ping time to hours

    targetDistance[i] = speedOfSound * pingTime[i];  //Calculates distance in miles
    targetDistance[i] = targetDistance[i]/2;  //Accounts for round trip of ping to target
    targetDistance[i] = targetDistance[i]*63360;  //Convert targetDistance to inches (63360 inches in a mile)
    
    Serial.print("The distance to the target for sensor");
    Serial.print(i);
    Serial.print(" is:  ");
    Serial.print(targetDistance[i]);
    Serial.println(" inches");
    delay(1000);
  }
}
