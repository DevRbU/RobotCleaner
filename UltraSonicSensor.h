#ifndef _UltraSonicSensor_h_
#define _UltraSonicSensor_h_

class UltraSonicSensor {
	private:
		int _triggerFront;
		int _triggerLeft;
		int _triggerRight;
		int _triggerBottom;
		
		int _echoFront;
		int _echoLeft;
		int _echoRight;
		int _echoBottom;
	
	public:
		float _distanceFront;
		float _distanceLeft;
		float _distanceRight;
		float _distanceBottom;
		
		void pinSet(int triggerFront, int triggerLeft, int triggerRight, int triggerBottom, int echoFront, int echoLeft, int echoRight, int echoBottom);
		void distanceMeasurement();
};

#endif