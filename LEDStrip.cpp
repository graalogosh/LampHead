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
	else{
		writeRGB(0,0,0);
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
	// else if (number == colorCount){
	// 	number--;
	// }
	setColor(predefinedColors[number-1].red, predefinedColors[number-1].green, predefinedColors[number-1].blue);
}

State LEDStrip::getLightState(){
	return lightState;
}

void LEDStrip::reduceBrightness(){
	bool stop = false;
	const unsigned int redStep = currentColor.red / reduceSpeed;
	if (currentColor.red >= redStep){
		currentColor.red -= redStep;
	}
	else{
		stop = true;
	}
	const unsigned int greenStep = currentColor.green / reduceSpeed;
	if (currentColor.green >= greenStep){
		currentColor.green -= greenStep;
	}
	else{
		stop = true;
	}
	const unsigned int blueStep = currentColor.blue / reduceSpeed;
	if (currentColor.blue >= blueStep){
		currentColor.blue -= blueStep;
	}	
	else{
		stop = true;
	}

	#ifdef DEBUG
		Serial.print("Stop: "); Serial.println(stop);
	#endif
	
	if (!stop){
		setColor(currentColor.red, currentColor.green, currentColor.blue);
	}
	// else{
	// 	turnOff();
	// }
}

void LEDStrip::increaceBrightness(){
	bool stop = false;
	const unsigned int redStep = currentColor.red / increaceSpeed;
	if (currentColor.red + redStep < 254){
		currentColor.red += redStep;
	}
	else{
		currentColor.red = 254;
		stop = true;
	}
	const unsigned int greenStep = currentColor.green / increaceSpeed;
	if (currentColor.green + greenStep < 254){
		currentColor.green += greenStep;
	}
	else{
		currentColor.green = 254;
		stop = true;
	}
	const unsigned int blueStep = currentColor.blue / increaceSpeed;
	if (currentColor.blue + blueStep < 254){
		currentColor.blue += blueStep;
	}	
	else{
		currentColor.blue = 254;
		stop = true;
	}

	#ifdef DEBUG
		Serial.print("Stop: "); Serial.println(stop);
	#endif
	
	if (!stop){
		setColor(currentColor.red, currentColor.green, currentColor.blue);
	}
}

	void LEDStrip::setColorOfPalette(unsigned int number, unsigned int paletteStart, unsigned int paletteFinish){
	
	const unsigned int red1Level = paletteStart;
	const unsigned int greenLevel = paletteStart + (paletteFinish - paletteFinish) / 3;
	const unsigned int blueLevel = paletteStart + (paletteFinish - paletteStart) / 3 * 2;
	const unsigned int red2Level = paletteFinish; 

	#ifdef DEBUG
		Serial.print("red1Level: "); Serial.println(red1Level);
		Serial.print("greenLevel: "); Serial.println(greenLevel);
		Serial.print("blueLevel: "); Serial.println(blueLevel);
		Serial.print("red2: "); Serial.println(red2Level);

	#endif

	unsigned int  red;
	unsigned int green;
	unsigned int blue;

	if (number <= greenLevel){//red-green
		red = map(number, red1Level, greenLevel, 0, 254);
		green = map(number, red1Level, greenLevel, 254, 0);
		blue = 0;
	}
	else if (number <= blueLevel){ //green-blue
		red = 0;
		green = map (number, greenLevel, blueLevel, 0, 254);
		blue = map (number, greenLevel, blueLevel, 254, 0);
	}
	else{ //number < red2Level blue-red
		red = map (number, blueLevel, red2Level, 254, 0);
		green = 0;
		blue = map (number, blueLevel, red2Level, 0, 254);
	}

	
	setColor(red, green, blue);
}
