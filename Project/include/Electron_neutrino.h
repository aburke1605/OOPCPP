#ifndef _ELECTRONNEUTRINO_INCL_GUARD
#define _ELECTRONNEUTRINO_INCL_GUARD

#include "Neutrino.h"

class electron_neutrino : public neutrino
{
public:
	electron_neutrino(bool is_electron_antineutrino = false);
	electron_neutrino(const double& mom, const double& theta, const double& phi, bool is_electron_antineutrino = false);
	~electron_neutrino();
};

#endif