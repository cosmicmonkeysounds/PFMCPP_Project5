/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3 and will take you through how to write code that doesn't leak as well as how to refactor. 

 Destructors

 If you didn't do Project3, write 3 UDTs below (where it asks for Copied UDTs) that have: 
        member functions,
        member variables, 
        constructors that initialize the members. 
        for() or while() loops that modify member variables
        
 Define your implementations of all functions OUTSIDE of the class. 
 Then do instruction 2)
 
 If you DID do Project 3, do instruction 1)
 
 1) Copy a few of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

	If you already did Chapter2 part 10 on Coliru and don't have a Project3, just grab some UDTs from your Coliru Ch2P10 submission. 
 
 3) add 2 new UDTs that use only the types you copied above.
 4) Add destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 5) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 6) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 7) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>

/*
 copied UDT 1:
 */

struct Oscillator
{
    unsigned int waveform = 0;
    float frequency = 440.f, minFreq = 20.f, maxFreq = 20000.f;
    float amplitude = 1.f;
    bool FMEnable;
    unsigned int numOfVoices;

    float readCV();
    void outputSound();
    float mixVoices(float voiceSignal);
    void sweepFrequency();

    Oscillator(unsigned int voices = 2, bool fm = false)
    {
        FMEnable = fm;
        numOfVoices = voices;
    }

    ~Oscillator()
    {
        std::cout << "Deleting oscillator with frequency " << frequency << std::endl;
    }

    void printStuff()
    {
        std::cout << "A " << numOfVoices << " voice " << (FMEnable ? "FM " : "") << "oscillator" << std::endl; 
    } 
};

void Oscillator::sweepFrequency()
{
    for ( float i = minFreq; i <= maxFreq; i += 1.f )
    {
        frequency = i;
        outputSound();
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

float Oscillator::mixVoices(float voiceSignal)
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

/*
 copied UDT 2:
 */

struct VCA
{
    unsigned int numOfInputs = 2, numOfOutputs = 1;
    float maxGainOut = 100.f, minGainOut = -100.f, clipThresh, currentGain = 50.f, currentSignal = 10.f, amplifiedSignal;


    void applyGain();
    float gainBeforeClipping();
    void saturate(float clipAmount);
    float readCV();

    VCA(float clip = 60.5f)
    {
        clipThresh = clip;
    }

    ~VCA()
    {
        std::cout << "Destructing VCA with gain of " << currentGain << std::endl;
    }

    void printStuff()
    {
        std::cout << "Currently at " << currentGain << " dB of gain" << std::endl;
    }
};

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

/*
 copied UDT 3:
 */

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

    Filter(bool lp = true, bool bp = false, bool hp = false)
    {
        isLowPass = lp;
        isBandPass = bp;
        isHighPass = hp;
    }

    void printStuff()
    {
        std::cout << "A " << (isLowPass ? "low pass" : "") << (isBandPass ? "bandpass" : "") << (isHighPass ? "highpass" : "") << " filter" << std::endl;
    }

    ~Filter();
};

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

Filter::~Filter()
{
    std::cout << "Destroying a " << (isLowPass ? "low pass" : (isBandPass ? "band pass" : (isHighPass ? "high pass" : ""))) << " filter with cutoff freq of " << cutoffFreq << " and Q of " << resonance << std::endl;
}

/*
 new UDT 4:
 */

struct SingleVoiceSynth
{
    Oscillator osc;
    VCA vca;
    Filter filter;

    void noiseSequence();
    ~SingleVoiceSynth();
};

void SingleVoiceSynth::noiseSequence()
{
    osc.sweepFrequency();
    filter.filterSweep(100.f, 2000.f);
}

SingleVoiceSynth::~SingleVoiceSynth()
{
    noiseSequence();
    std::cout << "Destroying the synth..." << std::endl;
}

/*
 new UDT 5:
 */
struct StateVariableFilter
{
    Filter lp = Filter(true, false, false), bp = Filter(false, true, false), hp = Filter(false, false, true);

    void sweepAll();

    ~StateVariableFilter()
    {
        std::cout << "Say goodbye to your filters!" << std::endl;
    }

};

void StateVariableFilter::sweepAll()
{
    lp.filterSweep(40.f, 20000.f);
    bp.filterSweep(40.f, 20000.f);
    hp.filterSweep(40.f, 20000.f);
}

int main()
{
    std::cout << "good to go!" << std::endl;

    std::cout << std::endl << "Contructor Calls and Member Function Printing: " << std::endl << std::endl;
    
    Oscillator osc(4, true);
    osc.printStuff();
    osc.sweepFrequency();

    VCA vca(40.f);
    vca.printStuff();
    std::cout << "Gain before clipping VCA with current signal: " << vca.gainBeforeClipping() << "dB" << std::endl;

    Filter filter(true, false, false);
    filter.printStuff();
    filter.filterSweep(440.f, 12000.f);
    std::cout << "Low pass transfer function outputing: " << filter.lowPass.transferFunction(1.f) << std::endl;

    SingleVoiceSynth synth;

    StateVariableFilter svf;

    std::cout << std::endl << "Destructor Calls: " << std::endl << std::endl;
}
