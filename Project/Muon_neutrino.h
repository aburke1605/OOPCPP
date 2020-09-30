#ifndef _MUONNEUTRINO_INCL_GUARD
#define _MUONNEUTRINO_INCL_GUARD

#include "Neutrino.h"

class muon_neutrino : public neutrino
{
public:
	muon_neutrino(bool is_antimuon_neutrino = false);
	muon_neutrino(const double& mom, const double& theta, const double& phi, bool is_antimuon_neutrino = false);
	~muon_neutrino();
};

#endif