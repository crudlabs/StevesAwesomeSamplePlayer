#include "StevesAwesomeSamplePlayer.h"

extern "C" {
    extern const int16_t ulaw_decode_table[256];
};

void StevesAwesomeSamplePlayer::update()
{    
    if(!playing) return;
    
    block = allocate();
    if (block == NULL) return;
    if(format == 0) return;

    for (int i = 0; i < 128; i++)
    {
        if(playing) block->data[i] = getNextSample();
        else block->data[i] = 0;
    }

  transmit(block, 0);
  release(block);
}

void StevesAwesomeSamplePlayer::play(const unsigned int* _sampleArray) {
    setSampleArray(_sampleArray);
    startPlaying();
}

int16_t StevesAwesomeSamplePlayer::getNextSample()
{
    int16_t cs = 0;

    __disable_irq();

    // increment the current sample step
    currentStep++;

    // if its time to go to the next sample, go for it
    if(currentStep >= stepsPerSample) {

        // reset sample step
        currentStep = 0;

        // go to the next sample
        if(backwards == true) {
            currentSample -= sampleSpeed;
        } else {
            currentSample += sampleSpeed;
        }
    }


        
    // if forwards
    if(backwards == false and currentSample >= length * endPercent) {

        // if looping start over
        if(looping) {
            currentSample = length * startPercent + 1;

        // if not, stop playing
        } else {
            playing = false;
            return 0;
        }
    }

    // if backwards
    if(backwards == true and currentSample < length * startPercent) {

        // if looping start over
        if(looping) {
            currentSample = length * endPercent;
        
        // if not, stop playing
        } else {
            playing = false;
            return 0;
        }
    }

    long sampleIndex;
    int sample32BitContainer;

    // if it's 16 bit PCB
    if(format == 0x81 or format == 0x82 or format == 0x83) {

        sampleIndex = currentSample / 2;    // two samples per int
        sample32BitContainer = sampleArray[(int)sampleIndex];

        if((int)currentSample % 2 == 0) cs = (int16_t)(sample32BitContainer & 65535);
        else cs = (int16_t)(sample32BitContainer >> 16);
    }
    // if its u-law
    else if(format == 0x01 or format == 0x02 or format == 0x03) {
        sampleIndex = currentSample / 4;    // 4 samples per int
        sample32BitContainer = sampleArray[(int)sampleIndex];
        cs = (int16_t)((sample32BitContainer >> (((int)currentSample % 4) * 8)) & 255);   // get the 8 bit sample
        cs = ulaw_decode_table[(int)cs];                                            // decode
    }

    __enable_irq();

    return cs;
}

void StevesAwesomeSamplePlayer::setSampleArray(const unsigned int* _sampleArray)
{
    __disable_irq();
    sampleArray = _sampleArray;
    length = *_sampleArray & 0xFFFFFF;
    format = *_sampleArray  >> 24;
    if(format == 0x81)      stepsPerSample = 1;     // 16 bit PCM, 44100 Hz
    else if(format == 0x82) stepsPerSample = 2;     // 16 bit PCM, 22050 Hz
    else if(format == 0x83) stepsPerSample = 4;     // 16 bit PCM, 11025 Hz
    else if(format == 0x01) stepsPerSample = 1;     // 8 bit u-law, 44100 Hz
    else if(format == 0x02) stepsPerSample = 2;     // 8 bit u-law, 22050 Hz
    else if(format == 0x03) stepsPerSample = 4;     // 8 bit u-law, 11025 Hz
    currentStep = 0;
    __enable_irq();
}

 bool StevesAwesomeSamplePlayer::isPlaying() 
 {
    return playing;
 }
 
void StevesAwesomeSamplePlayer::startPlaying()
{
    playing = true;
    if(backwards == false) {
        currentSample = length * startPercent;
    } else {
        currentSample = length * endPercent;
    }
}

void StevesAwesomeSamplePlayer::stop()
{
    playing = false;
}

void StevesAwesomeSamplePlayer::pitchShift(float _semitones)
{
    sampleSpeed = pow(2, _semitones / 12.0);
}

uint32_t StevesAwesomeSamplePlayer::lengthMillis(void)
{
    return (uint32_t)(length  / (float)44100 * 1000.0);
}

uint32_t StevesAwesomeSamplePlayer::positionMillis(void) {
    return (uint32_t)(currentSample  / (float)44100 * 1000.0);
}