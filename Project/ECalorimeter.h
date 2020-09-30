#ifndef _ECALORIMETER_INCL_GUARD
#define _ECALORIMETER_INCL_GUARD

#include "Detector.h"

class e_calorimeter : public detector
{
public:
	e_calorimeter();
	e_calorimeter(const double& radius_1, const double& radius_2);
	~e_calorimeter();
};

#endif