/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via 'this->' and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
        d) you should see 2 (almost) identical messages in the program output for each member function you add:
            one for the std::cout line, and one for the member function's output
 
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

/*
 example:
 */
#include <iostream>
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
    Filter lp { true, false, false }, 
    bp { false, true, false }, 
    hp { false, false, true };

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
