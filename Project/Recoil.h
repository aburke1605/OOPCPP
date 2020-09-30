#ifndef _RECOIL_INCL_GUARD
#define _RECOIL_INCL_GUARD

#include "Particle.h"

class recoil : public particle
{
public:
	recoil(const double& m)
	{
		mass = m;
	}
	~recoil() 
	{
		//std::cout << "Recoil destructor called" << std::endl;
	}
	void set_decay_modes() {}
};

#endif