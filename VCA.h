#pragma once
#include "LeakedObjectDetector.h"

struct VCA
{
    unsigned int numOfInputs = 2, 
    numOfOutputs = 1;

    float maxGainOut = 100.f, 
    minGainOut = -100.f, 
    clipThresh, 
    currentGain = 50.f, 
    currentSignal = 10.f, 
    amplifiedSignal = 10.f;


    VCA( float clip = 60.5f );
    ~VCA();
    void applyGain();
    float gainBeforeClipping();
    void saturate( float clipAmount );
    float readCV();
    void printStuff();

    JUCE_LEAK_DETECTOR(VCA)
};
