/*
  This is a program for Robot Cleaner
  Program function
  
  1. App inventor's Bluetooth data process
  2. Manual mode's Motor & CPU fan control with bluetooth data
  3. Auto mode's Self Driving

  programmed by 21960011 Kim Sung Kyu

  version 2.0
  1.x -> object oriented programming
*/

// bluetooth library
#include<SoftwareSerial.h>
// motor driver library
#include<AFMotor.h>

// Create Libraries

// Relay Library
#include <Relay.h>
// UltraSonicSensor Library
#include <UltraSonicSensor.h>

// error? Arduino Mega can't bluetooth data get.
#define blueTooth Serial3


// data from App Inventor
char command;


// object declare

// motorDrive
AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

// front cleaner motor
AF_DCMotor cleanerLeft(3);
AF_DCMotor cleanerRight(4);

Relay relay;
UltraSonicSensor sensor;

// AutoControl or ManualControl Flag
bool autoManual = false;

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

// Cleaner On
void cleanOn() {
  cleanerLeft.run(FORWARD);
  cleanerRight.run(BACKWARD);
}

// Cleaner Off
void cleanOff() {
  cleanerLeft.run(RELEASE);
  cleanerRight.run(RELEASE);
}

void setup() {
  // bluetoothSerialMonitor
  blueTooth.begin(9600);
  Serial.begin(9600);

  // Relays' pin setup motor 50, fan 51
  relay.pinSet(50, 51);

  // motor drive set up
  motorLeft.setSpeed(150);       
  motorLeft.run(RELEASE);
  motorRight.setSpeed(150);
  motorRight.run(RELEASE); 

  // cleaner set up
  cleanerLeft.setSpeed(0);
  cleanerLeft.run(RELEASE);
  cleanerRight.setSpeed(0);
  cleanerRight.run(RELEASE);

  // Ultra Sonic Sensor pin set
  sensor.pinSet(22, 23, 24, 25, 26, 27, 28, 29);
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

    case 'o':
      cleanOn();
      relay.fanOn();
      break;
    case 'x':
      cleanOff();
      relay.fanOff();
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
      Serial.write(command);
    }
    
    // if command data is 'M', end auto Control mode and do Manual Control Mode
    if(command == 'M') {
      autoManual = false;
      Stop();
      continue;
    }

    sensor.distanceMeasurement();
    
    if(sensor._distanceBottom > 10 && sensor._distanceBottom < 2000) {
       Return();
       delay(1000);
       turnRight();
       delay(500);
    }
    else if(sensor._distanceFront < 30) {
      Return();
      delay(1000);
      turnRight();
      delay(1000);
    }
    else if(sensor._distanceLeft < 30) {
      turnRight();
      delay(1000);
    }
    else if(sensor._distanceRight < 30) {
      turnLeft();
      delay(1000);
    }
    else {
      drive();
    }
  }
}
