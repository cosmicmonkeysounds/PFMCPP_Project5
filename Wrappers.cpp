#include "Wrappers.h"


#include "Oscillator.h"

OscillatorWrapper::OscillatorWrapper( Oscillator* _osc ) : osc(_osc) {}

OscillatorWrapper::~OscillatorWrapper(){ delete osc; }



#include "VCA.h"

VCAWrapper::VCAWrapper( VCA* _vca ) : vca(_vca) {}

VCAWrapper::~VCAWrapper(){ delete vca; }



#include "Filter.h"

FilterWrapper::FilterWrapper( Filter* _f ) : filter(_f) {}

FilterWrapper::~FilterWrapper(){ delete filter; }



#include "SingleVoiceSynth.h"

SingleVoiceSynthWrapper::SingleVoiceSynthWrapper( SingleVoiceSynth* _sy ) : synth(_sy) {}

SingleVoiceSynthWrapper::~SingleVoiceSynthWrapper(){ delete synth; }



#include "StateVariableFilter.h"

StateVariableFilterWrapper::StateVariableFilterWrapper( StateVariableFilter* _svf ) : svf(_svf) {}

StateVariableFilterWrapper::~StateVariableFilterWrapper(){ delete svf; }
