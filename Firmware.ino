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
	// Serial.println(rangeSensor->getRange());
	// delay(200);
	const unsigned int distance1 = rangeSensor->getRange();
	if (distance1==-1){
		//do nothing
		return;
	}

	delay(1000);
	const unsigned int distance2 = rangeSensor->getRange();
	if (distance2==-1){
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Fast move - toogle light");
		#endif //DEBUG

		ledStrip->toogleLightSmoothly(fadingSteps);
		return;
	}

	const float distance1WithNegativeHysteresis = (float)distance1 - (float)distance1/100.0f * (float) hysteresisPercent;
	const float distance1WithPositiveHysteresis = (float)distance1 + (float)distance1/100.0f * (float) hysteresisPercent;

	if ((float)distance2 < distance1WithNegativeHysteresis){
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1-NegHystPerc: "); Serial.println(distance1WithNegativeHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 < DistWithNegHyst - reduce brightness");
		#endif //DEBUG

	}
	else if((float) distance2 > distance1WithPositiveHysteresis){
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1+PosHystPerc: "); Serial.println(distance1WithPositiveHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 > DistWithPosHyst - increase brightness");
		#endif //DEBUG

	}
	else{
		#ifdef DEBUG
			Serial.print("Dist1: "); Serial.println(distance1);
			Serial.print("Dist1-NegHystPerc: "); Serial.println(distance1WithNegativeHysteresis);
			Serial.print("Dist1+PosHystPerc: "); Serial.println(distance1WithPositiveHysteresis);
			Serial.print("Dist2: "); Serial.println(distance2);
			Serial.println("Dist2 == Dist1 - change color");
		#endif //DEBUG
			
	}
}

