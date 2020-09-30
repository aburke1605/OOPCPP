#ifndef _MUONCHAMBER_INCL_GUARD
#define _MUONCHAMBER_INCL_GUARD

#include "Detector.h"

class muon_chamber : public detector
{
public:
	muon_chamber();
	muon_chamber(const double& radius_1, const double& radius_2);
	~muon_chamber();
};

#endif