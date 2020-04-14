struct Oscillator;

struct OscillatorWrapper
{
    Oscillator* osc = nullptr;

    OscillatorWrapper( Oscillator* _osc );
    
    ~OscillatorWrapper();
};

struct VCA;

struct VCAWrapper
{
    VCA* vca = nullptr;
    VCAWrapper( VCA* _vca );
    ~VCAWrapper();
};

struct Filter;

struct FilterWrapper
{
    Filter* filter = nullptr;
    FilterWrapper( Filter* _f );
    ~FilterWrapper();
};

struct SingleVoiceSynth;

struct SingleVoiceSynthWrapper
{
    SingleVoiceSynth* synth = nullptr;
    SingleVoiceSynthWrapper( SingleVoiceSynth* _sy );
    ~SingleVoiceSynthWrapper();
};

struct StateVariableFilter;

struct StateVariableFilterWrapper
{
    StateVariableFilter* svf = nullptr;
    StateVariableFilterWrapper( StateVariableFilter* _svf );
    ~StateVariableFilterWrapper();
};
