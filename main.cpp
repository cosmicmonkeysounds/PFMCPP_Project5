/*
 Project 5: Part 4 / 4
 video: Chapter 3 Part 7

 Create a branch named Part4
 
 Don't #include what you don't use
 
 1) Your task is to refactor your Chapter 3 Part 4 task into separate source and header files.
         Add files via the pane on the left.
 
 2) Put all of your declarations for each class in .h files
         One header file per class ( i.e. Raider.h for a class named "Raider" )
 
 3) Put all of your implementations in .cpp files.
         one cpp file per class ( i.e. Raider.cpp for a class named "Raider" )
 
 4) Put all of your Wrapper classes in a single Wrappers.h file
         if you implemented your wrapper class functions in-class, you'll need to move them to Wrappers.cpp
 
 5) NO IN-CLASS IMPLEMENTATION ALLOWED.
         the only exception is the existing Atomic.h and LeakedObjectDetector.h
 
 6) for every .cpp file you have to make, insert it into the .replit file after 'main.cpp'.  Don't forget the spaces between file names.
 If you need help with this step, send me a DM.
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 Remember, your Chapter 3 Part 4 task worked when it was all in one file. so you shouldn't need to edit any of it.  
         just split it up into source files and provide the appropriate #include directives.
 */












/*
 example:
 */
#include <iostream>
#include "LeakedObjectDetector.h"

namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}



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
        this->FMEnable = fm;
        this->numOfVoices = voices;
    }

    ~Oscillator()
    {
        std::cout << "Deleting oscillator with frequency " << frequency << std::endl;
    }

    void printStuff()
    {
        std::cout << "A " << numOfVoices << " voice " << (FMEnable ? "FM " : "") << "oscillator" << std::endl; 
    } 

    JUCE_LEAK_DETECTOR(Oscillator)
};

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

struct OscillatorWrapper
{
    Oscillator* osc = nullptr;
    OscillatorWrapper( Oscillator* _osc ) : osc(_osc) {}
    ~OscillatorWrapper(){ delete osc; }
};

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
        this->clipThresh = clip;
    }

    ~VCA()
    {
        std::cout << "Destructing VCA with gain of " << this->currentGain << std::endl;
    }

    void printStuff()
    {
        std::cout << "Gain before clipping VCA with current signal: " << this->gainBeforeClipping() << "dB" << std::endl;
    }

    JUCE_LEAK_DETECTOR(VCA)
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

struct VCAWrapper
{
    VCA* vca = nullptr;
    VCAWrapper( VCA* _vca ) : vca(_vca) {}
    ~VCAWrapper(){ delete vca; }
};

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
        std::cout << "Low pass transfer function outputing: " << this->lowPass.transferFunction(1.f) << std::endl;
    }

    ~Filter();


    JUCE_LEAK_DETECTOR(Filter)
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

    std::cout << str << " filter with cutoff freq of " << cutoffFreq << " and Q of " << resonance << std::endl;
}

struct FilterWrapper
{
    Filter* filter = nullptr;
    FilterWrapper( Filter* _f ) : filter(_f) {}
    ~FilterWrapper(){ delete filter; }
};

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


    JUCE_LEAK_DETECTOR(SingleVoiceSynth)
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

struct SingleVoiceSynthWrapper
{
    SingleVoiceSynth* synth = nullptr;
    SingleVoiceSynthWrapper( SingleVoiceSynth* _sy ) : synth(_sy) {}
    ~SingleVoiceSynthWrapper(){ delete synth; }
};

/*
 new UDT 5:
 */
struct StateVariableFilter
{
    Filter lp { true, false, false }, 
    bp { false, true, false }, 
    hp { false, false, true };

    void sweepAll();

    ~StateVariableFilter()
    {
        std::cout << "Say goodbye to your filters!" << std::endl;
    }


    JUCE_LEAK_DETECTOR(StateVariableFilter)

};

void StateVariableFilter::sweepAll()
{
    lp.filterSweep(40.f, 20000.f);
    bp.filterSweep(40.f, 20000.f);
    hp.filterSweep(40.f, 20000.f);
}

struct StateVariableFilterWrapper
{
    StateVariableFilter* svf = nullptr;
    StateVariableFilterWrapper( StateVariableFilter* _svf ) : svf(_svf) {}
    ~StateVariableFilterWrapper(){ delete svf; }
};

int main()
{
    std::cout << "good to go!" << std::endl;

    std::cout << std::endl << "Contructor Calls and Member Function Printing: " << std::endl << std::endl;
    
    OscillatorWrapper oscWrap( new Oscillator(4, true) );
    oscWrap.osc->printStuff();
    oscWrap.osc->sweepFrequency();

    VCAWrapper vcaWrap( new VCA(40.f) );
    vcaWrap.vca->printStuff();
    std::cout << "Gain before clipping VCA with current signal: " << vcaWrap.vca->gainBeforeClipping() << "dB" << std::endl;

    FilterWrapper filterWrap( new Filter(true, false, false) );
    filterWrap.filter->filterSweep(440.f, 12000.f);
    std::cout << "Low pass transfer function outputing: " << filterWrap.filter->lowPass.transferFunction(1.f) << std::endl;
    filterWrap.filter->printStuff();


    SingleVoiceSynthWrapper synthWrap( new SingleVoiceSynth() );

    StateVariableFilterWrapper svfWrap( new StateVariableFilter() );

    std::cout << std::endl << "Destructor Calls: " << std::endl << std::endl;
}
