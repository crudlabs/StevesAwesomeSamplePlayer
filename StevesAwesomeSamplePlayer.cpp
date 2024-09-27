#include "StevesAwesomeSamplePlayer.h"

void StevesAwesomeSamplePlayer::update()
{    
    if(!playing) return;
    
    block = allocate();
    if (block == NULL) return;

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

    if(backwards == true) {
        currentSample -= sampleSpeed;
    } else {
        currentSample += sampleSpeed;
    }
        
    // if forwards
    if(backwards == false and currentSample >= length * endPercent) {

        // if looping start over
        if(looping) {
            currentSample = length * startPercent;

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
    length = (*_sampleArray & 0xFFFFFF);
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