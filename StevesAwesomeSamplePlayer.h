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
          looping = false;
          sampleSpeed = 1;
          length = 0;
          backwards = false;
          format = 0;
    }

    // inhereted update function 
    virtual void update(void);

    void setSampleArray(unsigned int* _sampleArray);
    void startPlaying();
    void loadFromSD(const char* _fileName);
    void useExternalRAMChip();
    void play(const unsigned int* _sampleArray);
    void play(unsigned int* _sampleArray);
    void play();
    void stop();
    void pitchShift(float _semitones);
    volatile double startPercent;
    volatile double endPercent;
    bool isPlaying();
    bool looping;
    bool backwards;
    uint32_t positionMillis(void);
	uint32_t lengthMillis(void);

    private:
    int16_t getNextSample();    
    volatile float sampleSpeed;
    unsigned int* sampleArray;
    volatile double length;
    volatile double currentSample;
    bool playing;
    int format;
    bool usingExternalRAMChip = false;
    int stepsPerSample;
    int currentStep;
    audio_block_t* block;
    audio_block_t* inputQueueArray[1];
};

#endif