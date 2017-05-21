#ifndef RANGE_SENSOR
#define RANGE_SENSOR

#include "Arduino.h"

class RangeSensor{
private:
	#define LENGHT 11
		const float voltageArray[LENGHT] = { 2.75f, 2.3f, 1.65f, 1.3f, 1.1f, 0.92f, 0.75f, 0.6f, 0.5f, 0.45f, 0.4f };
		const float distanceArray[LENGHT] = { 8.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f };
		const unsigned int arrayLength = LENGHT;
	#undef LENGHT

	unsigned int rangePin;

	unsigned int minHeight;
	unsigned int maxHeight;

	bool rangeIsValid(unsigned int range);
public:
	// RangeSensor(unsigned int rangePin, unsigned int minHeight, unsigned int maxHeight);
	RangeSensor(unsigned int rangePin);

	int getRange();
	unsigned int getAnalogValue();
};

#endif //RANGE_SENSOR