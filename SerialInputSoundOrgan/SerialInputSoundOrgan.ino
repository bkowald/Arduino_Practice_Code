
// serial input sound organ

// receives serial data and translates it to a sound

#include "pitches.h"

// input character to notes map
// note that 0 is the highest note because that is how they are laid out on the keyboard
int notes[] = {
  NOTE_E5, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5  };

// led to blink when a note is played
#define LED 13


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Welcome to serial sound organ. Press 1-0 (number keys) to play sounds");
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 

  // see if a character is available
  if (Serial.available() > 0) {
    int c = Serial.read();

    // check for a valid character '0' to '9'
    if (c < '0' || c > '9') {
      Serial.write("INV\n");
    }
    else {  
      // convert to a number from 0-9
      c -= '0';

      // turn on led while the note plays
      digitalWrite(LED, HIGH);

      // make all notes a quarter note
      int noteDuration = 1000/4;

      tone(8, notes[c],noteDuration);
      
      // turn off led
      digitalWrite(LED, LOW);

      // Q: does the tone generator need an "off" command between notes?
      // A: No - it turns off by itself
      //noTone(8);

      Serial.write("OK\n");

    }  // end valid character
  }  // end serial data is available

}

