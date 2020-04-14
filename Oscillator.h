#pragma once
#include "LeakedObjectDetector.h"

struct Oscillator
{
    unsigned int waveform = 0;
    float frequency = 440.f, minFreq = 20.f, maxFreq = 20000.f;
    float amplitude = 1.f;
    bool FMEnable;
    unsigned int numOfVoices;

    Oscillator( unsigned int voices = 2, bool fm = false );
    
    ~Oscillator();

    void printStuff();

    float readCV();
    void outputSound();
    float mixVoices(float voiceSignal);
    void sweepFrequency();

    JUCE_LEAK_DETECTOR(Oscillator)
};
