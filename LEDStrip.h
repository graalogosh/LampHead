#ifndef LED_STRIP
#define LED_STRIP

#include "Arduino.h"

struct Color{
		unsigned int red;
		unsigned int green;
		unsigned int blue;
};

class LEDStrip{
private:
	unsigned int redPin;
	unsigned int greenPin;
	unsigned int bluePin;

	Color currentColor;

	#define COLOR_COUNT 7
	Color predefinedColors[COLOR_COUNT] ={
		{255,0,0},
		{255,128,0},
		{255,255,0},
		{0,255,0},
		{0,191,255},
		{0,0,255},
		{90,0,157}
	};
	const unsigned int colorCount = COLOR_COUNT;
	#undef COLOR_COUNT

enum { OFF, ON } lightState;

public:
	LEDStrip(unsigned int redPin, unsigned int greenPin, unsigned int bluePin);
	LEDStrip(unsigned int redPin, unsigned int redColor, unsigned int greenPin, unsigned int greenColor, unsigned int bluePin, unsigned int bluePower);

	void setColor (unsigned int red, unsigned int green, unsigned int blue);
};

#endif //LED_STRIP