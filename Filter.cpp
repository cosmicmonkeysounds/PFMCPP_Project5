#include "Filter.h"

Filter::Filter( bool lp, bool bp, bool hp )
{
    isLowPass = lp;
    isBandPass = bp;
    isHighPass = hp;
}

Filter::~Filter()
{
    std::string str = "Destryoing a ";

    if( isLowPass )
    {
        str += "low pass";
    }
    else if( isBandPass )
    {
        str += "band pass";
    }
    else
    {
        str += "high pass";
    }

    std::cout << str << " filter with cutoff freq of " << cutoffFreq << " and Q of " << resonance << "\n";
}

void Filter::printStuff()
{
    std::cout << "Low pass transfer function outputing: " << this->lowPass.transferFunction(1.f) << "\n";
}

float Filter::LowPass::transferFunction(float input)
{
    // DSP stuff; not implemented 
    return input;
}

float Filter::applyFilter(float input)
{
    float filtered = input; // this will be a vector
    if ( isLowPass )
    {
        filtered = lowPass.transferFunction(input);
    }
    return filtered;
}

void Filter::filterSweep(float low, float high)
{
    for ( float i = low; i <= high; i += 1.f )
    {
        cutoffFreq = i;
    }
}
