/*
This program plays a .raw file stored on an SD card, which is plugged
into the audio adapter's SD card slot. The file - "cowbell.raw" -
is included in the same directory as this example sketch

Definitely read all these notes before trying to use this:

-You have to put the SD card into the audio adapter's SD card slot,
not the Teensy 4.1s
-It currently only plays 16 bit PCM encoded .raw files
-To make a 16 bit PCM encoded .raw file, drag any mono audio file into
Audacity and File > Export > Export Audio, and select...
File Type: Other uncompressed files
Header: RAW (header-less)
Encoding: Signed 16-bit PCM
-The Teensy can only hold a few seconds of samples
-the SD card uses SPI communication on digital pins 10, 11, 12, 13. 
So you can't have pin 10 plugged into anything else, and pins 11, 12,
and 13 can *only* be plugged into other SPI devices. You can't use
them for anything else, or the SD card won't work.
*/

#include <StevesAwesomeSamplePlayer.h>

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

void setup() {

  // audio memory
  AudioMemory(12);

  // init audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  // init sample player and start playing
  samplePlayer.looping = true;
  samplePlayer.loadFromSD("cowbell.raw");
  samplePlayer.play();
}

void loop() {

}

