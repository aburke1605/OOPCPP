#include "../include/Particles.h"

muon::muon(bool is_antimuon)
{
	type = "MUON";
	mass = 105.658e-3;
	if (is_antimuon) {
		this->make_antiparticle();
	}
	//std::cout << "Default muon constructor called" << std::endl;
}

muon::muon(const double& mom, const double& theta, const double& phi, bool is_antimuon)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid muon absolute momentum" << std::endl;
		exit(1);
	}
	type = "MUON";
	mass = 105.658e-3;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antimuon) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised muon constructor called" << std::endl;
}

muon::~muon()
{
	//std::cout << "Muon destructor called" << std::endl;
}

void muon::set_decay_modes()
{
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<electron>());
	channel_1.push_back(std::make_unique<muon_neutrino>());
	channel_1.push_back(std::make_unique<electron_neutrino>(true));
	decay_particles.push_back(std::move(channel_1));
	if (charge != -1.0) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at = it->begin(); at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}