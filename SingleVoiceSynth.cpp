#include "SingleVoiceSynth.h"

SingleVoiceSynth::~SingleVoiceSynth()
{
    noiseSequence();
    std::cout << "Destroying the synth..." << std::endl;
}

void SingleVoiceSynth::noiseSequence()
{
    osc.sweepFrequency();
    filter.filterSweep(100.f, 2000.f);
    vca.applyGain();
}

void SingleVoiceSynth::printStuff()
{
    std::cout << "Osc freq is " << this->osc.frequency << "Hz at " << this->vca.amplifiedSignal << "db\n";
}
