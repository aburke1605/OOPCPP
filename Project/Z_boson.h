#ifndef _ZBOSON_INCL_GUARD
#define _ZBOSON_INCL_GUARD

#include "Particle.h"

class z_boson : public particle
{
public:
	z_boson();
	z_boson(const double& mom, const double& theta, const double& phi);
	~z_boson();
	void set_decay_modes();
};

#endif