#include "Arduino.h"
#include "Relay.h"

void Relay::pinSet(int motorPin, int fanPin) {
	_motorPin = motorPin;
	_fanPin = fanPin;

	pinMode(_motorPin, OUTPUT);
	digitalWrite(_motorPin, LOW);
	pinMode(_fanPin, OUTPUT);
	digitalWrite(_fanPin, HIGH);
}

void Relay::fanOn() {
	digitalWrite(_fanPin, LOW);
}

void Relay::fanOff() {
	digitalWrite(_fanPin, HIGH);
}
