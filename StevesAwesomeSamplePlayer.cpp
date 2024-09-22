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

void record()
{

}

void play()
{

}

int16_t StevesAwesomeSamplePlayer::getNextSample()
{
    double cs;

    __disable_irq();

    currentSample += sampleSpeed;
    
    // the old way without adustable start and end    
    //if(currentSample >= length) currentSample = 0;
    
    // the new way with adjustable start and end
    if(currentSample >= length * endPercent) currentSample = length * startPercent;

    cs = sampleArray[(int)currentSample];

    __enable_irq();

    return cs;
}

void StevesAwesomeSamplePlayer::setSampleArray(volatile int16_t* _sampleArray)
{
    __disable_irq();
    sampleArray = _sampleArray;
    __enable_irq();
}

 void StevesAwesomeSamplePlayer::setSamplePlaybackLength(volatile double _length)
 {
    __disable_irq();
    length = _length;
    __enable_irq();
 }

 void StevesAwesomeSamplePlayer::setSampleSpeed(float _sampleSpeed)
 {
    // Serial.println(_sampleSpeed);
    __disable_irq();
    sampleSpeed = _sampleSpeed;
    __enable_irq();
 }
 
void StevesAwesomeSamplePlayer::startPlaying()
{
    playing = true;
    currentSample = length * startPercent;
}

void StevesAwesomeSamplePlayer::stop()
{
    playing = false;
}