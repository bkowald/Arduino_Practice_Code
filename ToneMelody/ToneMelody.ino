/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8 (chip pin 14 on AtMega328)
 
 created 5/28/2013
 by Brian Kowald 

This example code is in the public domain and based on the tone tutorial:
 
 http://arduino.cc/en/Tutorial/Tone
 
 Brian - I added "Ode To Joy". It has note, duration as pairs
 
 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

// ode to joy. combine note and duration into pairs
// C4 is middle C
int melody_2[] = {
    NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4,
    NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
    NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
    NOTE_E4, 3, NOTE_D4, 8, NOTE_D4, 2,
 
    NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4,
    NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
    NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
    NOTE_D4, 3, NOTE_C4, 8, NOTE_C4, 2,
 
    NOTE_D4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
    NOTE_D4, 4, NOTE_E4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_C4, 4,
    NOTE_D4, 4, NOTE_E4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_D4, 4,
    NOTE_C4, 4, NOTE_D4, 4, NOTE_G3, 2,
    
    NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4,
    NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
    NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
    NOTE_D4, 3, NOTE_C4, 8, NOTE_C4, 2,
  
    0,0}; // marks the end. pretty clever eh?
 
 // added a blinking LED
#define LED 13

 
void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  
  /*
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
  
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    
    // tutorial example - notes and duration are int two different array
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  delay(2000);
   */
   
  // my versino of ode to joy. The notes and duration are pairs in the same array, so increment by two
  for (int i  = 0; melody_2[i] != 0; i =  i + 2) 
  {
      // turn on LED while the note plays
      digitalWrite(LED, HIGH);
      
      int noteDuration = 1000/melody_2[i + 1];
      tone(8, melody_2[i],noteDuration);

      // turn off LED between notes
      digitalWrite(LED, LOW);
      
      // delay between notes
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      
      // stop the tone playing to get ready for the next one
      noTone(8);
  }
 
  // delay before repeat
  delay(2000);
  
}
