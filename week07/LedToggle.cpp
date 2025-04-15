#include "LedToggle.h"

LedToggle::LedToggle(int pin) {
	_pin = pin;
	_state = false;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

void LedToggle::toggle() {
	_state = !_state;
	digitalWrite(_pin, _state ? HIGH : LOW);
}
