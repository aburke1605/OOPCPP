#ifndef _TRACKER_INCL_GUARD
#define _TRACKER_INCL_GUARD

#include "Detector.h"

class tracker : public detector
{
public:
	tracker();
	tracker(const double& radius_1, const double& radius_2);
	~tracker();
};

#endif