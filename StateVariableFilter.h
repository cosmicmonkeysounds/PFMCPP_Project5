#pragma once
#include "LeakedObjectDetector.h"
#include "Filter.h"

struct StateVariableFilter
{
    Filter lp { true, false, false }, 
    bp { false, true, false }, 
    hp { false, false, true };

    ~StateVariableFilter();
    void sweepAll();

    JUCE_LEAK_DETECTOR(StateVariableFilter)

};
