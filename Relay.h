#ifndef _Relay_h_
#define _Relay_h_

class Relay {
	private:
		int _motorPin;
		int _fanPin;
	
	public:
		void pinSet(int motorPin, int fanPin);
		void fanOn();
		void fanOff();
};

#endif