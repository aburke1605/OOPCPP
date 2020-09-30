#ifndef _MUON_INCL_GUARD
#define _MUON_INCL_GUARD

#include "Lepton.h"

class muon : public lepton
{
public:
	muon(bool is_antimuon = false);
	muon(const double& mom, const double& theta, const double& phi, bool is_antimuon = false);
	~muon();
	void set_decay_modes();
};

#endif