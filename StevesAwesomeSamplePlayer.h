#ifndef STEVES_AWESOME_SAMPLE_PLAYER
#define STEVES_AWESOME_SAMPLE_PLAYER

#include "Arduino.h"
#include "AudioStream.h"

class StevesAwesomeSamplePlayer : public AudioStream 
{      

public:
    // constructor
    StevesAwesomeSamplePlayer(void) : AudioStream(1, inputQueueArray) {
          playing = false;
          currentSample = 0;
          startPercent = 0.0;
          endPercent = 1.0;
          looping = false;
          sampleSpeed = 1;
          length = 0;
          backwards = false;
          format = 0;
    }

    // inhereted update function 
    virtual void update(void);

    void setSampleArray(unsigned int* _sampleArray);
    void setMaxSampleLength(double _length);
    void startPlaying();
    void loadFromSD(const char* _fileName);
    void useExternalRAMChip();
    void play(const unsigned int* _sampleArray);
    void play(unsigned int* _sampleArray);
    void play();
    void stop();
    void pitchShift(float _semitones);
    void startRecording();
    void stopRecording();
    volatile double startPercent;
    volatile double endPercent;
    bool isPlaying();
    bool looping;
    bool backwards;
    uint32_t positionMillis(void);
	uint32_t lengthMillis(void);

private:
    audio_block_t* inputQueueArray[1];
    void playUpdate();
    void recordUpdate();
    int16_t getNextSample();    
    volatile float sampleSpeed;
    unsigned int* sampleArray;
    volatile double length;
    volatile double maxSampleLength;
    volatile double currentSample;
    volatile bool playing;
    volatile bool recording;
    int format;
    bool usingExternalRAMChip = false;
    int stepsPerSample;
    int currentStep;
    int recordingArrayIndex;
};

#endif