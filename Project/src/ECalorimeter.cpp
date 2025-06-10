#include "../include/ECalorimeter.h"

e_calorimeter::e_calorimeter() : detector{}
{
	//std::cout << "Default electronic calorimeter constructor called" << std::endl;
}

e_calorimeter::e_calorimeter(const double& radius_1, const double& radius_2) : detector{ radius_1,radius_2,sf::Color::Green }
{
	interactions["ELECTRON"] = (radius_2 - radius_1) / max_energy;
	interactions["TOP"] = 0.0;
	interactions["BOTTOM"] = 0.0;
	interactions["W BOSON"] = 0.0;
	interactions["TAU"] = 0.0;
	for (auto it = interactions.begin(); it != interactions.end(); it++) {
		interactions["ANTI" + it->first] = it->second;
	}
	interactions["PHOTON"] = (radius_2 - radius_1) / max_energy; // TODO
	interactions["Z BOSON"] = 0.0;
	//std::cout << "Parametrised electronic calorimeter constructor called, outer radius = " << radius_2 << std::endl;
}

e_calorimeter::~e_calorimeter()
{
	//std::cout << "Electronic calorimeter destructor called" << std::endl;
}