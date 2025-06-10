#ifndef _GLUON_INCL_GUARD
#define _GLUON_INCL_GUARD

#include "Particle.h"

class gluon : public particle
{
public:
	gluon();
	gluon(const double& mom, const double& theta, const double& phi);
	~gluon();
	void set_decay_modes();
};

#endif