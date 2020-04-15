#pragma once
#include "LeakedObjectDetector.h"
#include "Oscillator.h"
#include "VCA.h"
#include "Filter.h"

struct SingleVoiceSynth
{
    Oscillator osc{ 1, false };
    VCA vca{ 4.f };
    Filter filter{ true, false, false };

    void noiseSequence();
    void printStuff();
    ~SingleVoiceSynth();

    JUCE_LEAK_DETECTOR(SingleVoiceSynth)
};
