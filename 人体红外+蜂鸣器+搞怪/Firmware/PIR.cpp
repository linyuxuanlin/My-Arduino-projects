#include "PIR.h"


PIR::PIR(int PIRPin) : signalPin(PIRPin)
{
	pinMode(signalPin, INPUT_PULLUP);
 
}
bool PIR::read()
{
	return !digitalRead(signalPin);
}



