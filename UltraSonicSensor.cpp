#include "Arduino.h"
#include "UltraSonicSensor.h"

void UltraSonicSensor::pinSet(int triggerFront, int triggerLeft, int triggerRight, int triggerBottom, int echoFront, int echoLeft, int echoRight, int echoBottom) {
	pinMode(triggerFront, OUTPUT);
	pinMode(triggerLeft, OUTPUT);
	pinMode(triggerRight, OUTPUT);
	pinMode(triggerBottom, OUTPUT);
	
	pinMode(echoFront, INPUT_PULLUP);
	pinMode(echoLeft, INPUT_PULLUP);
	pinMode(echoRight, INPUT_PULLUP);
	pinMode(echoBottom, INPUT_PULLUP);
	
	_triggerFront = triggerFront;
	_triggerLeft = triggerLeft;
	_triggerRight = triggerRight;
	_triggerBottom = triggerBottom;
	
	_echoFront = echoFront;
	_echoLeft = echoLeft;
	_echoRight = echoRight;
	_echoBottom = echoBottom;
}

void UltraSonicSensor::distanceMeasurement() {
	float duration;
	
	digitalWrite(_triggerFront, LOW);
	delayMicroseconds(2);
	digitalWrite(_triggerFront, HIGH);
	delayMicroseconds(10);
	digitalWrite(_triggerFront, LOW);
	duration = pulseIn(_echoFront, HIGH);
	_distanceFront = duration / 29.0 / 2.0;
	
	digitalWrite(_triggerLeft, LOW);
	delayMicroseconds(2);
	digitalWrite(_triggerLeft, HIGH);
	delayMicroseconds(10);
	digitalWrite(_triggerLeft, LOW);
	duration = pulseIn(_echoLeft, HIGH);
	_distanceLeft = duration / 29.0 / 2.0;
	
	digitalWrite(_triggerRight, LOW);
	delayMicroseconds(2);
	digitalWrite(_triggerRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(_triggerRight, LOW);
	duration = pulseIn(_echoRight, HIGH);
	_distanceRight = duration / 29.0 / 2.0;
	
	digitalWrite(_triggerBottom, LOW);
	delayMicroseconds(2);
	digitalWrite(_triggerBottom, HIGH);
	delayMicroseconds(10);
	digitalWrite(_triggerBottom, LOW);
	duration = pulseIn(_echoBottom, HIGH);
	_distanceBottom = duration / 29.0 / 2.0;
	
	Serial.println(" distance Front : " + String(_distanceFront) + " distance Left : " + String(_distanceLeft) + " distance Right : " + String(_distanceRight) + " distanceBottom" + String(_distanceBottom));
}