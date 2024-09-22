#include <StevesAwesomeSamplePlayer.h>
#include "AudioSampleCowbell.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
StevesAwesomeSamplePlayer samplePlayer;  //xy=248.1999969482422,146.1999969482422
AudioOutputI2S i2s1;                     //xy=463.7000274658203,146.4500036239624
AudioConnection patchCord1(samplePlayer, 0, i2s1, 0);
AudioConnection patchCord2(samplePlayer, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=351.4500198364258,269.7000198364258
// GUItool: end automatically generated code

int samplePitch = -12;

void setup() {

  // audio memory
  AudioMemory(12);

  // init audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

  // init sample player and start playing
  samplePlayer.setSampleArray(AudioSampleCowbell);
  samplePlayer.looping = false;
  samplePlayer.pitchShift(samplePitch);
  samplePlayer.startPercent = 0.25;
  samplePlayer.endPercent = 0.75;
  samplePlayer.startPlaying();
}

void loop() {
  // sit and wait until the current sample finishes playing
  while (samplePlayer.isPlaying()) {}

  // then increment the pitch by one semitone
  samplePitch++;

  // go back to the lowest pitch if we reach the highest
  if (samplePitch > 12) samplePitch = -12;

  // set the pitch
  samplePlayer.pitchShift(samplePitch);

  // and start playing again
  samplePlayer.startPlaying();
}
