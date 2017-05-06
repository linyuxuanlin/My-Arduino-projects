#include "Global.h"

unsigned int HoorayLength          = 6;                                                      // amount of notes in melody
unsigned int HoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int HoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!

void setup() {
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    Serial.println("start");
    
    
}

void loop() {
    
    if (pir.read()) {
        // This example shows the tone function.
        // Uncomment it to use it.
        //piezoSpeaker.tone(400); // play a 400Hz tone
        //delay(500);            // keep playing it for 500ms
        //piezoSpeaker.off();     // stop the sound
        //delay(500);            // and wait 500ms
        
        // This example uses the playMelody function, which plays complete melodies.
        // Edit the melody by modifying the Hooray variables at the top of the file.
        piezoSpeaker.playMelody(HoorayLength, HoorayMelody, HoorayNoteDurations);
    }
}