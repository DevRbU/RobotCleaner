/*
  This is a program for Robot Cleaner
  Program function
  
  1. App inventor's Bluetooth data process
  2. Manual mode's Motor & CPU fan control with bluetooth data
  3. Auto mode's Self Driving

  programmed by 21960011 Kim Sung Kyu

  version 1.1
  1.0 -> can receive command in while statement
*/

// bluetooth library
#include<SoftwareSerial.h>

// bluetooth Object pin set RX,TX
SoftwareSerial blueTooth(2, 3);

// data from App Inventor
char command;

// motorDrive
int motorA1 = 8;
int motorA2 = 9;
int motorB1 = 10;
int motorB2 = 11;

// UltraSonicSensor
int trig[] = { 4, 5, 6, 7 };
int echo[] = { A1, A2, A3, A4 };
unsigned long duration[] = {};

// AutoControl or ManualControl Flag
bool autoManual = false;

// distance measurement's values
float distance[] = {};

void setup() {
  // bluetoothSerialMonitor
  blueTooth.begin(9600);

  // motor pin set
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // Ultra Sonic Sensor pin set
  for(int i = 0; i < 4; i++) {
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT_PULLUP);
  }
}

// left wheel drive function
void leftDrive() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
}

// left wheel return function
void leftReturn() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
}

// left wheel stop function
void leftStop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
}

// right wheel drive function
void rightDrive() {
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

// right wheel return function
void rightReturn() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

// rigth wheel stop function
void rightStop() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

// turn Left
void turnLeft() {
  leftReturn();
  delay(50);
  rightDrive();
}

// turn Right
void turnRight() {
  rightReturn();
  delay(50);
  leftDrive();
}

// Drive
void drive() {
  leftDrvie();
  delay(50);
  rightDrive();
}

// Return
void Return() {
  leftReturn();
  delay(50);
  rightReturn();
}

// Stop
void Stop() {
  leftStop();
  delay(50);
  rightStop();
}

// distance measurement function
float measurement() {
  float distance[] = {};

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

  for (int i = 0; i < 4; i++) {
    distance[i] = duration[i] / 29.0 / 2.0;
  }

  return distance;
}

void loop() {
  // if bluetooth Serial data received
  if(blueTooth.available()) {
    // assign the data at command variable
    command = blueTooth.read();
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
    if(bluetooth.available()) {
      command = bluetooth.read();
    }
    // if command data is 'M', end auto Control mode and do Manual Control Mode
    if(command == 'M') {
      autoManual = false;
      Stop();
      continue;
    }

    distance = measurement();

    // if front distance is less than 5cm or left or right distance is less than 3cm and front distance is less than 10cm
    // turn right
    if(distance[0] < 5 || distance[1] < 3 && distance[0] < 10 || distance[2] < 3 && distance[0] < 10) {
      Stop();
      turnRight();
      delay(1000);
      Stop();
    }

    // if distance from bottom is greater than 5cm, Return
    if(distance[4] > 5) {
      Stop();
      Return();
      delay(500);
      Stop();
    }

    // if nothing is happen, continue driving
    drive();
  }
}
