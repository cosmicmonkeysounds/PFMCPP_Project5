#include "Oscillator.h"

Oscillator::Oscillator( unsigned int voices, bool fm )
{
    this->FMEnable = fm;
    this->numOfVoices = voices;
}

Oscillator::~Oscillator()
{
    std::cout << "Deleting oscillator with frequency " << frequency << "\n";
}

void Oscillator::printStuff()
{
    std::cout << "A " << numOfVoices << " voice " << (FMEnable ? "FM " : "") << "oscillator" << "\n"; 
} 

void Oscillator::sweepFrequency()
{
    for ( float i = minFreq; i <= maxFreq; i += 1.f )
    {
        this->frequency = i;
        this->outputSound();
    }
}

float Oscillator::readCV()
{
    // returns a stream from the inputs
    return 0.f;

    /*
    std::vector<float> CVInputs;
    for ( int i = 1; i <= numOfCVInputs; ++i )
    {
        CVInputs.push_back( CVInputPorts[i].read() );
    }
    return CVInputs;
    */
}

float Oscillator::mixVoices( float voiceSignal )
{
    return voiceSignal;

    // voiceSignal would be array that holds all the data for each voice
    
    // float mixedSignals = 0;
    
    // for ( int i = 1; i <= numOfVoices; ++i )
    // {
    //     mixedSignals += voiceSignal[i];
    // }

    // return mixedSignals;
}

void Oscillator::outputSound()
{
    /*
    std::vector<float> voiceSignals;
    for ( int i = 1; i <= numOfVoices; ++i )
    {
        voiceSignals.push_back(voice[i]);
    }
    audioOutputPort.output( mixVoices(voiceSignals) )
    */
}
