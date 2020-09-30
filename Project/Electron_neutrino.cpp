#include "Particles.h"

electron_neutrino::electron_neutrino(bool is_electron_antineutrino)
{
	type = "ELECTRON-NEUTRINO";
	if (is_electron_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Default electron-neutrino constructor called" << std::endl;
}

electron_neutrino::electron_neutrino(const double& mom, const double& theta, const double& phi, bool is_electron_antineutrino)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid electron-neutrino absolute momentum" << std::endl;
		exit(1);
	}
	type = "ELECTRON-NEUTRINO";
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_electron_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised electron-neutrino constructor called" << std::endl;
}


electron_neutrino::~electron_neutrino()
{
	//std::cout << "Electron-neutrino destructor called" << std::endl;
}