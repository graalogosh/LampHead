#include "LEDStrip.h"
#include "RangeSensor.h"

//LED pins
const unsigned int redPin = 10;
const unsigned int greenPin = 11;
const unsigned int bluePin = 9;

//range sensor signal
const unsigned int rangePin = A7;

//minimal and maximum height in sm
const unsigned int minHeight = 8;//TODO - change to real value
const unsigned int maxHeight = 40;

//light increase and reduce speed
const unsigned int reduceSpeed = 5;
const unsigned int increaceSpeed = 5;

LEDStrip* ledStrip;
RangeSensor* rangeSensor;

void setup(){
	ledStrip = new LEDStrip(redPin, greenPin, bluePin);
	ledStrip->setColor(255,255,255);

	// rangeSensor = new RangeSensor(rangePin, minHeight, maxHeight);
	rangeSensor = new RangeSensor(rangePin);

}

void loop(){

}

