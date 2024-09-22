#ifndef STEVES_AWESOME_SAMPLE_PLAYER
#define STEVES_AWESOME_SAMPLE_PLAYER

// this library currently only works with WAVS converted with wav2sketch using 16 bit PCB encoding and 44100 sample rate !

#include "Arduino.h"
#include "AudioStream.h"

class StevesAwesomeSamplePlayer : public AudioStream {

    private:
    #if defined(__IMXRT1062__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
        static const unsigned int MAX_BUFFERS = 80;
    #else
        static const unsigned int MAX_BUFFERS = 32;
    #endif        

    public:
    // constructor
    // (note for later: in theory I shouldn't need the inputQueueArray and the args should be (0, NULL), but this works fine so I'm leaving it for now
    StevesAwesomeSamplePlayer() : AudioStream(1, inputQueueArray) {
          playing = false;
          currentSample = 0;
          startPercent = 0.0;
          endPercent = 1.0;
          looping = false;
          sampleSpeed = 1;
    }

    // inhereted update function 
    virtual void update(void);

    void setSampleArray(const unsigned int* _sampleArray);
    void startPlaying();
    void stop();
    void pitchShift(float _semitones);
    volatile double startPercent;
    volatile double endPercent;
    bool isPlaying();
    bool looping;

    private:
    int16_t getNextSample();    
    volatile float sampleSpeed;
    const unsigned int* sampleArray;
    volatile double length;
    volatile double currentSample;
    bool playing;
    audio_block_t* block;
    audio_block_t* inputQueueArray[1];
};

#endif