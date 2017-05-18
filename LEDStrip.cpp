#define DEBUG
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

	#ifdef DEBUG
		Serial.print("RGB: "); 
		Serial.print(currentColor.red);
		Serial.print(", ");
		Serial.print(currentColor.green);
		Serial.print(", ");
		Serial.println(currentColor.blue);
	#endif

	if (red == 0 && green == 0 && blue == 0){
		lightState = OFF;
	}

	if (lightState == ON){
		writeRGB(currentColor.red, currentColor.green, currentColor.blue);
	}
}

void LEDStrip::blink(const unsigned int count){
	int doubleCount = count * 2;
	for (int i = 0; i < doubleCount; i++){
		toogleLightImmediately();
		delay(100);
	}
}

void LEDStrip::fadeOff(const unsigned int steps){
	
	int red = currentColor.red;
	int green = currentColor.green;
	int blue = currentColor.blue;

	int redStep = currentColor.red / steps;
	int greenStep = currentColor.green / steps;
	int blueStep = currentColor.blue / steps;

	for (int i = 0; i< steps; i++){
		red -= redStep;
		green -= greenStep;
		blue -= blueStep;

		writeRGB(red, green, blue);
		delay(30);
	}
	//floor fix
	writeRGB(0,0,0);
	lightState = OFF;
}

void LEDStrip::fadeOn(const unsigned int steps){

	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;

	int redStep = currentColor.red / steps;
	int greenStep = currentColor.green / steps;
	int blueStep = currentColor.blue / steps;

	for (int i = 0; i< steps; i++){
		red += redStep;
		green += greenStep;
		blue += blueStep;

		writeRGB(red, green, blue);
		delay(30);
	}
	//floor fix
	writeRGB(currentColor.red, currentColor.green, currentColor.blue);
	lightState = ON;
}

void LEDStrip::toogleLightSmoothly(const unsigned int steps){
	if (lightState==OFF){
		fadeOn(steps);
	}
	else{
		fadeOff(steps);
	}
}

void LEDStrip::toogleLightImmediately(){
	if (lightState==ON){
		turnOff();
	}
	else{
		turnOn();
	}
}

void LEDStrip::turnOn(){
	lightState = ON;
	setColor(currentColor.red, currentColor.green, currentColor.blue);
}

void LEDStrip::turnOff(){
	lightState = OFF;
	writeRGB(0,0,0);
}

void LEDStrip::writeRGB(unsigned int red, unsigned int green, unsigned int blue){
	analogWrite(redPin, red);
	analogWrite(greenPin, green);
	analogWrite(bluePin, blue);
}

unsigned int LEDStrip::getPredefinedColorCount(){
	return colorCount;
}

void LEDStrip::setPredefinedColor(unsigned int number){
	if (number > colorCount){
		return;
	}
	else if (number == colorCount){
		number--;
	}
	setColor(predefinedColors[number].red, predefinedColors[number].green, predefinedColors[number].blue);
}