#ifndef _ELECTRON_INCL_HEADER
#define _ELECTRON_INCL_HEADER

#include "Lepton.h"

class electron : public lepton
{
public:
	electron(bool is_positron = false);
	electron(const double& mom, const double& theta, const double& phi, bool is_positron = false);
	~electron();
	void set_decay_modes();
};

#endif