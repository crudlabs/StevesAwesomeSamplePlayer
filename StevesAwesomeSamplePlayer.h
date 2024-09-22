#ifndef STEVES_AWESOME_SAMPLE_PLAYER
#define STEVES_AWESOME_SAMPLE_PLAYER

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
    }

    // inhereted update function 
    virtual void update(void);

    void setSampleArray(volatile int16_t* _sampleArray);
    void setSamplePlaybackLength(volatile double _length);
    void startPlaying();
    void stop();
    void setSampleSpeed(float _sampleSpeed);
    volatile double startPercent;
    volatile double endPercent;

    private:
    int16_t getNextSample();    
    volatile float sampleSpeed;
    volatile int16_t* sampleArray;
    volatile double length;
    volatile double currentSample;
    bool playing;
    audio_block_t* block;
    audio_block_t* inputQueueArray[1];
};

#endif
