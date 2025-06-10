#ifndef _WBOSON_INCL_GUARD
#define _WBOSON_INCL_GUARD

#include "Particle.h"

class w_boson : public particle
{
public:
	w_boson(bool is_antiw_boson = false);
	w_boson(const double& mom, const double& theta, const double& phi, bool is_antiw_boson = false);
	~w_boson();
	void set_decay_modes();
};

#endif