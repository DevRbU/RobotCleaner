/*
  This is a program for Robot Cleaner
  Program function
  
  1. App inventor's Bluetooth data process
  2. Manual mode's Motor & CPU fan control with bluetooth data
  3. Auto mode's Self Driving

  programmed by 21960011 Kim Sung Kyu

  version 1.6
  1.5 -> 
  1. cleaner function added
  2. cleaner motordrive set
  3. fan relay
  4. motordrive relay
  5. selfDriving logic changed
*/

// bluetooth library
#include<SoftwareSerial.h>
// motor driver library
#include<AFMotor.h>

// error? Arduino Mega can't bluetooth data get.
#define blueTooth Serial3


// data from App Inventor
char command;

// motorDrive
AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

// front cleaner motor
AF_DCMotor cleanerLeft(3);
AF_DCMotor cleanerRight(4);

// motor drive relay pin
int motor = 50;

// fan relay pin
int fan = 51;

// UltraSonicSensor
int trig[] = { 22, 23, 24, 25 };
int echo[] = { 26, 27, 28, 29 };

// AutoControl or ManualControl Flag
bool autoManual = false;

// distance measurement's values
float distance[4];

bool backNright = false;

void setup() {
  // bluetoothSerialMonitor
  blueTooth.begin(9600);
  Serial.begin(9600);

  // motor drive on off relay
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
  
  // motor drive set up
  motorLeft.setSpeed(200);       
  motorLeft.run(RELEASE);
  motorRight.setSpeed(200);
  motorRight.run(RELEASE); 

  // cleaner set up
  cleanerLeft.setSpeed(150);
  cleanerLeft.run(RELEASE);
  cleanerRight.setSpeed(150);
  cleanerRight.run(RELEASE);
  // cleaner fan on off relay
  pinMode(fan, OUTPUT);
  digitalWrite(fan, HIGH);
  
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

// Cleaner On
void cleanOn() {
  cleanerLeft.run(FORWARD);
  cleanerRight.run(BACKWARD);

  digitalWrite(fan, LOW);
}

// Cleaner Off
void cleanOff() {
  cleanerLeft.run(RELEASE);
  cleanerRight.run(RELEASE);

  digitalWrite(fan, HIGH);
}

// distance measurement function
float measurement(int trig, int echo){
  float duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 29.0 / 2.0;
  return distance;
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
      break;
    case 'x':
      cleanOff();
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

    for( int i = 0; i < 4; i++) {
      distance[i] = measurement(trig[i], echo[i]);
    }
    
    Serial.println("distance Front : " + String(distance[0]) + ", distance Left : " + String(distance[1]) + "distance Right : " + String(distance[2]) + "distance Bottom : " + String(distance[3])); 
    // if front distance is less than 5cm or left or right distance is less than 3cm and front distance is less than 10cm
    // turn right
    if(distance[3] > 10 && distance[3] < 2000 || distance[3] >= 0 && distance[3] < 2) {
       Return();
       delay(1000);
       turnRight();
       delay(500);
    }
    else if(distance[0] < 20 || distance[1] < 20 || distance[2] < 20) {
      turnRight();
    }
    else {
      drive();
    }
  }
}
