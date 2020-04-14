#include "StateVariableFilter.h"

StateVariableFilter::~StateVariableFilter()
{
    std::cout << "Say goodbye to your filters!" << std::endl;
}

void StateVariableFilter::sweepAll()
{
    lp.filterSweep(40.f, 20000.f);
    bp.filterSweep(40.f, 20000.f);
    hp.filterSweep(40.f, 20000.f);
}
