#include "Particles.h"

muon_neutrino::muon_neutrino(bool is_muon_antineutrino)
{
	type = "MUON-NEUTRINO";
	if (is_muon_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Default muon-neutrino constructor called" << std::endl;
}

muon_neutrino::muon_neutrino(const double& mom, const double& theta, const double& phi, bool is_muon_antineutrino)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid muon-neutrino absolute momentum" << std::endl;
		exit(1);
	}
	type = "MUON-NEUTRINO";
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_muon_antineutrino) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised muon-neutrino constructor called" << std::endl;
}

muon_neutrino::~muon_neutrino()
{
	//std::cout << "Muon-neutrino destructor called" << std::endl;
}