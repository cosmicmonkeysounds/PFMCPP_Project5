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

#include <iostream>
#include "LeakedObjectDetector.h"
#include "Oscillator.h"
#include "VCA.h"
#include "Filter.h"
#include "SingleVoiceSynth.h"
#include "StateVariableFilter.h"
#include "Wrappers.h"

int main()
{
    // #1
    std::cout << "\nUDT 1 -------------------: \n\n";
    OscillatorWrapper oscWrap( new Oscillator(2, true) );
    std::cout << "Current frequency of oscillator: " << oscWrap.osc->frequency << "\n\n";
    oscWrap.osc->sweepFrequency();
    
    // #2
    std::cout << "UDT 2 -------------------: \n\n";
    VCAWrapper vcaWrap( new VCA(40.f) );
    vcaWrap.vca->printStuff();
    std::cout << "Gain before clipping VCA with current signal: " << vcaWrap.vca->gainBeforeClipping() << "dB" << "\n\n";

    // #3
    std::cout << "UDT 3 -------------------: \n\n";
    FilterWrapper filterWrap( new Filter(true, false, false) );
    filterWrap.filter->printStuff();
    filterWrap.filter->filterSweep(440.f, 12000.f);
    std::cout << "Frequency of filter: " << filterWrap.filter->cutoffFreq << "\n\n";

    // #4
    std::cout << "UDT 4 -------------------: \n\n";
    SingleVoiceSynthWrapper synthWrap( new SingleVoiceSynth() );
    synthWrap.synth->printStuff();
    std::cout << "Synth filter cutoff is " << synthWrap.synth->filter.cutoffFreq << "Hz\n\n";

    // #5
    std::cout << "UDT 5 -------------------: \n\n";
    StateVariableFilterWrapper svfWrap( new StateVariableFilter() );
    std::cout << "Starting cutoff freq of SVF: " << svfWrap.svf->lp.cutoffFreq << "\n";
    svfWrap.svf->sweepAll();
    std::cout << "Cutoff freq of SVF after sweep: " << svfWrap.svf->lp.cutoffFreq << "\n\n";

    std::cout << "Destructor Calls --------: \n\n";
}
