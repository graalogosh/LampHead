#ifndef LED_STRIP
#define LED_STRIP

#include "Arduino.h"

class LEDStrip{
private:
	unsigned int redPin;
	unsigned int greenPin;
	unsigned int bluePin;

	struct{
		unsigned int red;
		unsigned int green;
		unsigned int blue;
	} currentColor; //RGB

enum { OFF, ON } lightState;

public:
	LEDStrip(unsigned int redPin, unsigned int greenPin, unsigned int bluePin);
	LEDStrip(unsigned int redPin, unsigned int redColor, unsigned int greenPin, unsigned int greenColor, unsigned int bluePin, unsigned int bluePower);

	void setColor (unsigned int red, unsigned int green, unsigned int blue);
};

#endif //LED_STRIP