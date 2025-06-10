#include "../include/HCalorimeter.h"

h_calorimeter::h_calorimeter() : detector{}
{
	//std::cout << "Default hadronic calorimeter constructor called" << std::endl;
}

h_calorimeter::h_calorimeter(const double& radius_1, const double& radius_2) : detector{ radius_1,radius_2,sf::Color::Red }
{
	//std::cout << "Parametrised hadronic calorimeter constructor called, radius = " << radius << std::endl;
	// any quark:
	interactions["UP"] = (radius_2 - radius_1) / max_energy;
	interactions["ANTIUP"] = (radius_2 - radius_1) / max_energy;
	interactions["DOWN"] = (radius_2 - radius_1) / max_energy;
	interactions["CHARM"] = (radius_2 - radius_1) / max_energy;
	interactions["STRANGE"] = (radius_2 - radius_1) / max_energy;
	interactions["TOP"] = 0.0;
	interactions["BOTTOM"] = 0.0;
	interactions["W BOSON"] = 0.0;
	interactions["TAU"] = 0.0;
	for (auto it = interactions.begin(); it != interactions.end(); it++) {
		interactions["ANTI" + it->first] = it->second;
	}
	interactions["Z BOSON"] = 0.0;
}

h_calorimeter::~h_calorimeter()
{
	//std::cout << "Hadronic calorimeter destructor called" << std::endl;
}