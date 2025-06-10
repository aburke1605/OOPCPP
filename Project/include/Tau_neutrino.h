#ifndef _TAUNEUTRINO_INCL_GUARD
#define _TAUNEUTRINO_INCL_GUARD

#include "Neutrino.h"

class tau_neutrino : public neutrino
{
public:
	tau_neutrino(bool is_tau_antineutrino = false);
	tau_neutrino(const double& mom, const double& theta, const double& phi, bool is_tau_antineutrino = false);
	~tau_neutrino();
};

#endif