/*
  This is a program for Robot Cleaner
  Program function
  
  1. App inventor's Bluetooth data process
  2. Manual mode's Motor & CPU fan control with bluetooth data
  3. Auto mode's Self Driving

  programmed by 21960011 Kim Sung Kyu

  version 1.4
  1.3 -> motor driver changed | Arduino UNO -> Arduino Mega
*/
  
// bluetooth library
#include<SoftwareSerial.h>
// motor driver library
#include<AFMotor.h>

// error? Arduino Mega can't bluetooth data get.
#define blueTooth Serial3


// bluetooth Object pin set RX,TX
//SoftwareSerial blueTooth(14, 15);

// data from App Inventor
char command;

// motorDrive
AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

// UltraSonicSensor
int trig[] = { 22, 23, 24, 25 };
int echo[] = { A8, A9, A10, A11 };
unsigned long duration[] = {};

// AutoControl or ManualControl Flag
bool autoManual = false;

// distance measurement's values
float distance1;
float distance2;
float distance3;
float distance4;

void setup() {
  // bluetoothSerialMonitor
  blueTooth.begin(9600);
  Serial.begin(9600);
  
  // motor drive set up
  motorLeft.setSpeed(255);       
  motorLeft.run(RELEASE);
  motorRight.setSpeed(255);
  motorRight.run(RELEASE); 

  // Ultra Sonic Sensor pin set
  for(int i = 0; i < 4; i++) {
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT_PULLUP);
  }
}

// turn Left
void turnLeft() {
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
}

// turn Right
void turnRight() {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
}

// Drive
void drive() {
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

// Return
void Return() {
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
}

// Stop
void Stop() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void loop() {
  // if bluetooth Serial data received
  if(blueTooth.available()) {
    // assign the data at command variable
    command = blueTooth.read();
    Serial.write(command);
  }

// Manual Control Wheel with command data
  switch(command) {
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'F':
      drive();
      break;
    case 'B':
      Return();
      break;
    case 'S':
      Stop();
      break;
  }

  // if command's value is 'A'
  if(command == 'A') {
    // Auto Manual Flag is true
    autoManual = true;
  }

  // while Auto Manual Flag is true Auto Control start
  while(autoManual) {
    // Receive command in while statement
    if(blueTooth.available()) {
      command = blueTooth.read();
    }
    // if command data is 'M', end auto Control mode and do Manual Control Mode
    if(command == 'M') {
      autoManual = false;
      Stop();
      continue;
    }

    // distance measurement function

    for (int i = 0; i < 4; i++) {
      digitalWrite(trig[i], LOW);
      digitalWrite(echo, LOW);
    }
    delayMicroseconds(2);
    for (int i = 0; i < 4; i++) {
      digitalWrite(trig[i], HIGH);
    }
    delayMicroseconds(10);
    for (int i = 0; i < 4; i++) {
      digitalWrite(trig[i], LOW);
    }
  
    for (int i = 0; i < 4; i++) {
      duration[i] = pulseIn(echo[i], HIGH);
    }
  
    distance1 = duration[0] / 29.0 / 2.0;
    distance2 = duration[1] / 29.0 / 2.0;
    distance3 = duration[2] / 29.0 / 2.0;
    distance4 = duration[3] / 29.0 / 2.0;

    Serial.println("distance1 : " + String(distance1) + ", distance2 : " + String(distance2) + "distance3) : " + String(distance3)); 
    // if front distance is less than 5cm or left or right distance is less than 3cm and front distance is less than 10cm
    // turn right
    if(distance1 < 5 || distance2 < 3 && distance1 < 10 || distance3 < 3 && distance1 < 10) {
      Stop();
      turnRight();
      delay(1000);
      Stop();
    }

    // if distance from bottom is greater than 5cm, Return
    if(distance4 > 5) {
      Stop();
      Return();
      delay(500);
      turnRight();
      delay(1000);
      Stop();
    }

    // if nothing is happen, continue driving
    drive();
  }
}
