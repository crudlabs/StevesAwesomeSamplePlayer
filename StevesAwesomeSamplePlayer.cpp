#include "StevesAwesomeSamplePlayer.h"

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
    double cs;

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

    long sampleIndex = currentSample / 2;
    int sample32BitContainer = sampleArray[(int)sampleIndex];

    if(sampleIndex % 2 == 0) cs = (int16_t)(sample32BitContainer & 65535);
    else cs = (int16_t)(sample32BitContainer >> 16);

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
    else if(format == 0x82) stepsPerSample = 2;     // 16 bits PCM, 22050 Hz
    else if(format == 0x83) stepsPerSample = 4;     // 16 bit PCM, 11025 Hz
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