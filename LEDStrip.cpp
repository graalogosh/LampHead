#include "LEDStrip.h"

LEDStrip::LEDStrip(unsigned int redPin, unsigned int greenPin, unsigned int bluePin){
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	pinMode (redPin, OUTPUT);
	pinMode (greenPin, OUTPUT);
	pinMode (bluePin, OUTPUT);

	setColor(255,255,255);//TODO delete
	lightState = OFF;
}
	
LEDStrip::LEDStrip(unsigned int redPin, unsigned int redColor, unsigned int greenPin, unsigned int greenColor, unsigned int bluePin, unsigned int bluePower){
	LEDStrip(redPin, greenPin, bluePin);
	setColor(redColor, greenColor, bluePower);
}

void LEDStrip::setColor (unsigned int red, unsigned int green, unsigned int blue){
	currentColor.red = red;
	currentColor.green = green;
	currentColor.blue = blue;

	if (lightState == ON){
		analogWrite(redPin, currentColor.red);
		analogWrite(greenPin, currentColor.green);
		analogWrite(bluePin, currentColor.blue);
	}
}

