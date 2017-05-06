#include "BaseSpeaker.h"
#include <Arduino.h>

// Constructor :
BaseSpeaker::BaseSpeaker(const int pin) : m_pin(pin)
{

}

void BaseSpeaker::tone(unsigned int frequency)
{
  // call Arduino's global tone function
  ::tone(m_pin, frequency); 
}

void BaseSpeaker::tone(unsigned int frequency, unsigned long duration)
{
  ::tone(m_pin, frequency, duration); //call Arduino's global tone function
}

void BaseSpeaker::off()
{
  ::noTone(m_pin);
}

void BaseSpeaker::playMelody(unsigned int len, unsigned int *melody, unsigned int *noteDurations)
{
  // Based on https://www.arduino.cc/en/Tutorial/toneMelody
  for (int thisNote = 0; thisNote < len; thisNote++) {
    
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(melody[thisNote], noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    off();
  }
}