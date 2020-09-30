#include "Particles.h"

tau_neutrino::tau_neutrino(bool is_tau_antineutrino)
{
	type = "TAU-NEUTRINO";
	if (is_tau_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Default tau-neutrino constructor called" << std::endl;
}

tau_neutrino::tau_neutrino(const double& mom, const double& theta, const double& phi, bool is_tau_antineutrino)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid tau-neutrino absolute momentum" << std::endl;
		exit(1);
	}
	type = "TAU-NEUTRINO";
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_tau_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised tau-neutrino constructor called" << std::endl;
}

tau_neutrino::~tau_neutrino()
{
	//std::cout << "Tau-neutrino destructor called" << std::endl;
}