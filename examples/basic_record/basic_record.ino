/*
this sketch allows the user to record a sample from the Teensy audio adapter's microphone 
input and play it back. the sample length is limited by the length of the sampleArray. It
is currently set to record one second at the default sample rate of 44100 samples per second.
you can increase the size of the array for longer samples, though you're of course limited
by the Teensy's memory
*/

#include <StevesAwesomeSamplePlayer.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
StevesAwesomeSamplePlayer samplePlayer;  //xy=248.1999969482422,146.1999969482422
AudioInputI2S i2s1;                     //xy=463.7000274658203,146.4500036239624
AudioOutputI2S i2s2;                     //xy=463.7000274658203,146.4500036239624
AudioConnection patchCord1(i2s1, 0, samplePlayer, 0);
AudioConnection patchCord2(samplePlayer, 0, i2s2, 0);
AudioConnection patchCord3(samplePlayer, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=351.4500198364258,269.7000198364258
// GUItool: end automatically generated code

#define MAX_SAMPLES 88200
#define SAMPLE_ARRAY_LENGTH (MAX_SAMPLES / 2)
unsigned int sampleArray[SAMPLE_ARRAY_LENGTH];

int recordButtonPin = 33;
int playButtonPin = 34;
bool recordButtonState = false;
bool lastRecordButtonState = false;
bool playButtonState = false;
bool lastPlayButtonState = false;
int recordLedPin = 31;
int playLedPin = 32;

void setup() {
  // audio memory
  AudioMemory(12);

  samplePlayer.setMaxSampleLength(MAX_SAMPLES);
  samplePlayer.setSampleArray(sampleArray);

  pinMode(recordButtonPin, INPUT);
  pinMode(playButtonPin, INPUT);
  pinMode(recordLedPin, OUTPUT);
  pinMode(playLedPin, OUTPUT);

    // init audio shield
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(30);
  sgtl5000_1.volume(0.5);
}

void loop() {
  checkRecordButton();
  checkPlayButton();
}

void checkRecordButton() {
  lastRecordButtonState = recordButtonState;
  recordButtonState = digitalRead(recordButtonPin);
  if(recordButtonState == HIGH and lastRecordButtonState == LOW) {
    samplePlayer.startRecording();  // start recording
    Serial.println("start recording");
    digitalWrite(recordLedPin, HIGH);
    delay(5);
  } else if(recordButtonState == LOW and lastRecordButtonState == HIGH) {
    samplePlayer.stopRecording();  // stop recording
    Serial.println("stop recording");
    Serial.println(samplePlayer.lengthMillis());
    digitalWrite(recordLedPin, LOW);
    delay(5);
  }
}

void checkPlayButton() {
  lastPlayButtonState = playButtonState;
  playButtonState = digitalRead(playButtonPin);
  if(playButtonState == HIGH and lastPlayButtonState == LOW) {
    samplePlayer.play();  // start playing
    digitalWrite(playLedPin, HIGH);
    delay(5);
  } else if(playButtonState == LOW and lastPlayButtonState == HIGH) {
    samplePlayer.stop();  // stop playing
    digitalWrite(playLedPin, LOW);
    delay(5);
  }
}