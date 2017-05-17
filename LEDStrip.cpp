#include "LEDStrip.h"

LEDStrip::LEDStrip(unsigned int redPin, unsigned int greenPin, unsigned int bluePin){
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	pinMode (redPin, OUTPUT);
	pinMode (greenPin, OUTPUT);
	pinMode (bluePin, OUTPUT);

	setColor(255,255,255);//TODO delete
}
	
LEDStrip::LEDStrip(unsigned int redPin, unsigned int redColor, unsigned int greenPin, unsigned int greenColor, unsigned int bluePin, unsigned int bluePower){
	LEDStrip(redPin, greenPin, bluePin);
	setColor(redColor, greenColor, bluePower);
}

void LEDStrip::setColor (unsigned int red, unsigned int green, unsigned int blue){
	currentState.red = red;
	currentState.green = green;
	currentState.blue = blue;

	analogWrite(redPin, currentState.red);
	analogWrite(greenPin, currentState.green);
	analogWrite(bluePin, currentState.blue);
}

