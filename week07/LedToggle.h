#ifndef LedToggle_h
#define LedToggle_h

#include "Arduino.h"

class LedToggle {
	public:
		LedToggle(int pin);
		void toggle();
	
	private:
		int _pin;
		bool _state;
};

#endif
