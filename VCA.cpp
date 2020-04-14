#include "VCA.h"

VCA::VCA( float clip )
    {
        this->clipThresh = clip;
        this->applyGain();
    }

VCA::~VCA()
{
    std::cout << "Destructing VCA with gain of " << this->currentGain << "\n";
}

void VCA::printStuff()
{
    std::cout << "Current amplitude of signal: " << this->amplifiedSignal << "dB" << "\n";
}

void VCA::saturate(float clipAmount)
{
    amplifiedSignal  = clipThresh + ( (clipAmount * currentGain) / (3.14f * clipAmount) );
}

float VCA::readCV()
{
    return 1.f;
    // not implemented
}

void VCA::applyGain()
{
    amplifiedSignal = currentSignal * ( currentGain - readCV() );
    if ( amplifiedSignal > clipThresh )
    {
        saturate( amplifiedSignal - clipThresh );
    }
}

float VCA::gainBeforeClipping()
{
    float level = currentSignal, gain = 1.f;

    while ( level < clipThresh )
    {
        level *= gain;
        gain += 1.f;
    }
    return gain;
}
