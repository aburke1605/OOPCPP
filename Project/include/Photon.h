#ifndef _PHOTON_INCL_GUARD
#define _PHOTON_INCL_GUARD

#include "Particle.h"

class photon : public particle
{
public:
	photon();
	photon(const double& mom, const double& theta, const double& phi);
	~photon();
	void set_decay_modes();
};

#endif