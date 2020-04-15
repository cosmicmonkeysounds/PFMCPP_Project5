#pragma once
#include "LeakedObjectDetector.h"

struct Filter
{
    bool isLowPass, isBandPass, isHighPass;
    float cutoffFreq = 1000.f, resonance = 0.7f;

    struct LowPass
    {
        float cutoffFreq, resonance;
        unsigned int topology;

        float transferFunction(float input);
    } lowPass;

    float applyFilter(float input);
    void filterSweep(float low, float high);

    Filter(bool lp = true, bool bp = false, bool hp = false);

    void printStuff();

    ~Filter();

    JUCE_LEAK_DETECTOR(Filter)
};
