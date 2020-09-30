#include "Tracker.h"

tracker::tracker() : detector{}
{
	//std::cout << "Default tracker constructor called" << std::endl;
}

tracker::tracker(const double& radius_1, const double& radius_2) : detector{ radius_1,radius_2,RGB(0, 0, 0) }
{
	//std::cout << "Parametrised tracker constructor called, radius = " << radius << std::endl;
	interactions["TOP"] = 0.0;
	interactions["BOTTOM"] = 0.0;
	interactions["W BOSON"] = 0.0;
	interactions["TAU"] = 0.0;
	for (auto it = interactions.begin(); it != interactions.end(); it++) {
		interactions["ANTI" + it->first] = it->second;
	}
	interactions["Z BOSON"] = 0.0;
}

tracker::~tracker()
{
	//std::cout << "Tracker destructor called" << std::endl;
}