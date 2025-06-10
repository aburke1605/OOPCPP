#ifndef _TAU_INCL_GUARD
#define _TAU_INCL_GUARD

#include "Lepton.h"

class tau : public lepton
{
public:
	tau(bool is_antitau = false);
	tau(const double& mom, const double& theta, const double& phi, bool is_antitau = false);
	~tau();
	void set_decay_modes();
};

#endif