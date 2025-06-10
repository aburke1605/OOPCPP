#ifndef _LEPTON_INCL_GUARD
#define _LEPTON_INCL_GUARD

#include "Particle.h"

class lepton : public particle
{
public:
    lepton()
    {
        charge = -1.0;
    }
    virtual ~lepton() {}
};

#endif