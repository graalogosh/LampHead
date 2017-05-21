#define DEBUG
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

//brightness increase and reduce speed
const unsigned int reduceSpeed = 5;
const unsigned int increaceSpeed = 5;

//fading steps
const unsigned int fadingSteps = 20;

//histeresis
const unsigned int hysteresisPercent = 10;

LEDStrip* ledStrip;
RangeSensor* rangeSensor;

void setup(){
	#ifdef DEBUG
		Serial.begin(9600);
	#endif //DEBUG

	ledStrip = new LEDStrip(redPin, greenPin, bluePin);
	ledStrip->setColor(255,255,255);

	// rangeSensor = new RangeSensor(rangePin, minHeight, maxHeight);
	rangeSensor = new RangeSensor(rangePin);


}

void loop(){
	// ledStrip->turnOn();
	// ledStrip->setColorOfPalette(rangeSensor->getRange(), minHeight, maxHeight);
	// Serial.println(rangeSensor->getRange());
	// delay(500);
	// return;

	const int distance1 = rangeSensor->getRange();
	if (distance1==-1){
		//do nothing
		return;
	}

	delay(400);//need to find
	const int distance2 = rangeSensor->getRange();
	if (distance2==-1){
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Fast move - toogle light");
		#endif //DEBUG

		ledStrip->toogleLightSmoothly(fadingSteps);
		delay (1000);
		return;
	}

	const float distance1WithNegativeHysteresis = (float)distance1 - (float)maxHeight/100.0f * (float) hysteresisPercent;
	const float distance1WithPositiveHysteresis = (float)distance1 + (float)maxHeight/100.0f * (float) hysteresisPercent;

	if ((float)distance2 < distance1WithNegativeHysteresis){ //reduce brightness
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1-NegHystPerc: "); Serial.println(distance1WithNegativeHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 < DistWithNegHyst - reduce brightness");
		#endif //DEBUG

		while(rangeSensor->getRange()!=-1 && ledStrip->getLightState()!=OFF){
			ledStrip->reduceBrightness();
			delay(50);
		}
	}
	else if((float) distance2 > distance1WithPositiveHysteresis){ //increace brightness
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1+PosHystPerc: "); Serial.println(distance1WithPositiveHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 > DistWithPosHyst - increase brightness");
		#endif //DEBUG
		while(rangeSensor->getRange()!=-1){
			ledStrip->increaceBrightness();
			delay(50);
		}		
	}
	else{ //change color
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1-NegHystPerc: "); Serial.println(distance1WithNegativeHysteresis);
			Serial.print("Dist1+PosHystPerc: "); Serial.println(distance1WithPositiveHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 == Dist1 - change color");
		#endif //DEBUG
			ledStrip->turnOn();
			ledStrip->blink(2);
			while (rangeSensor->getRange() != -1){
				float distance = rangeSensor->getRange();
				float step = (maxHeight-minHeight)/ledStrip->getPredefinedColorCount();
				float area = round(distance/step);

				#ifdef DEBUG
					Serial.print("Dist: "); Serial.println(distance);
					Serial.print("Step: "); Serial.println(step);
					Serial.print("Area: "); Serial.println(area);
				#endif //DEBUG

				ledStrip->setPredefinedColor(area);
				delay(200);
			}
	}
	delay (1000);
	return;
}

