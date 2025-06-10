#ifndef _HCALORIMETER_INCL_GUARD
#define _HCALORIMETER_INCL_GUARD

#include "Detector.h"

class h_calorimeter : public detector
{
public:
	h_calorimeter();
	h_calorimeter(const double& radius_1, const double& radius_2);
	~h_calorimeter();
};

#endif