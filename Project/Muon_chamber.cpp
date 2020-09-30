#include "Muon_chamber.h"

muon_chamber::muon_chamber() : detector{}
{
	//std::cout << "Default muon chamber constructor called" << std::endl;
}

muon_chamber::muon_chamber(const double& radius_1, const double& radius_2) : detector{ radius_1,radius_2,RGB(0, 0, 100) }
{
	//std::cout << "Parametrised muon chamber constructor called, radius = " << radius << std::endl;
	// muons only:
	interactions["TOP"] = 0.0;
	interactions["BOTTOM"] = 0.0;
	interactions["W BOSON"] = 0.0;
	interactions["TAU"] = 0.0;
	for (auto it = interactions.begin(); it != interactions.end(); it++) {
		interactions["ANTI" + it->first] = it->second;
	}
	interactions["Z BOSON"] = 0.0;
}

muon_chamber::~muon_chamber()
{
	//std::cout << "Muon chamber destructor called" << std::endl;
}