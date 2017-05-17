#include "RangeSensor.h"

// RangeSensor::RangeSensor(unsigned int rangePin, unsigned int minHeight, unsigned int maxHeight){
// 	RangeSensor(rangePin);
// 	this->minHeight = minHeight;
// 	this->maxHeight = maxHeight;
// }

RangeSensor::RangeSensor(unsigned int rangePin){
	this->rangePin = rangePin;
	//TODO fix
	this->minHeight = 8;
	this->maxHeight = 40;
}

unsigned int RangeSensor::getRange(){
	float currentVoltage = getVoltage();

	currentVoltage *= 0.00488758553; //  5 / 1023 = 0.00488758553
	if (currentVoltage > voltageArray[0]) {
		currentVoltage = voltageArray[0];
	}
	else if (currentVoltage < voltageArray[arrayLength - 1]) {
		currentVoltage = voltageArray[arrayLength - 1];
	}

	int position = 0;
	for (int i = 0; i < arrayLength - 1; i++) {
		if (currentVoltage >= voltageArray[i + 1]) {
			position = i;
			break;
		}
	}

	float y1 = voltageArray[position];
	float x1 = distanceArray[position];
	float y2 = voltageArray[position + 1];
	float x2 = distanceArray[position + 1];
	float currentDistance = (x2 - x1) * (y1 - currentVoltage) / (y1 - y2) + x1;

	return (unsigned int) currentDistance;
}

unsigned int RangeSensor::getVoltage(){
	int voltage = 0;
	for (int i = 0; i < 10; i++){
		voltage += analogRead(rangePin);
	}
	return voltage / 10;
}

bool RangeSensor::rangeIsValid(unsigned int range){
		return range >= minHeight && range<=maxHeight;
	}