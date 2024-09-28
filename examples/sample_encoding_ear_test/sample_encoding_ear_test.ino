/*
this sketch plays the same 808 cowbell sample, encoded in all 6 possible ways -
u-law (8 bit compressed) and pcm (16 bit), both in 44100, 22050, and 11025 bitrates
using wav2sketch http://crudlabs.org/wav2sketch/
*/

#include <StevesAwesomeSamplePlayer.h>
#include "AudioSampleCowbell11025ulaw.h"
#include "AudioSampleCowbell22050ulaw.h"
#include "AudioSampleCowbell44100ulaw.h"
#include "AudioSampleCowbell11025pcm.h"
#include "AudioSampleCowbell22050pcm.h"
#include "AudioSampleCowbell44100pcm.h"

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
  sgtl5000_1.volume(0.5);
}

void loop() {

  samplePlayer.play(AudioSampleCowbell44100pcm);
  delay(1000);
  samplePlayer.play(AudioSampleCowbell22050pcm);
  delay(1000);
  samplePlayer.play(AudioSampleCowbell11025pcm);
  delay(1000);

  samplePlayer.play(AudioSampleCowbell44100ulaw);
  delay(1000);
  samplePlayer.play(AudioSampleCowbell22050ulaw);
  delay(1000);
  samplePlayer.play(AudioSampleCowbell11025ulaw);
  delay(3000);  
}

