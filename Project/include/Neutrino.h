#ifndef _NEUTRINO_INCL_GUARD
#define _NEUTRINO_INCL_GUARD

#include "Particle.h"

class neutrino : public particle
{
public:
	neutrino()
	{
		mass = 1e-9;
		charge = 0;
	}
	virtual ~neutrino() {}
	void set_decay_modes() {} // neutrinos don't decay
};

#endif