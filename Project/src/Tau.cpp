#include "../include/Particles.h"

tau::tau(bool is_antitau)
{
	type = "TAU";
	mass = 1.77682;
	if (is_antitau) {
		this->make_antiparticle();
	}
	//std::cout << "Default tau constructor called" << std::endl;
}

tau::tau(const double& mom, const double& theta, const double& phi, bool is_antitau)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid tau absolute momentum" << std::endl;
		exit(1);
	}
	type = "TAU";
	mass = 1.77682;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antitau) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised tau constructor called" << std::endl;
}

tau::~tau()
{
	//std::cout << "Tau destructor called" << std::endl;
}

void tau::set_decay_modes()
{
	// down antiup: 65 %
	// electron: 18 %
	// muon: 17 %
	std::vector<std::unique_ptr<particle>> channel_1, channel_2, channel_3;
	channel_1.push_back(std::make_unique<down>());
	channel_1.push_back(std::make_unique<up>(true));
	channel_1.push_back(std::make_unique<tau_neutrino>());
	channel_2.push_back(std::make_unique<electron>());
	channel_2.push_back(std::make_unique<electron_neutrino>(true));
	channel_2.push_back(std::make_unique<tau_neutrino>());
	channel_3.push_back(std::make_unique<muon>());
	channel_3.push_back(std::make_unique<muon_neutrino>(true));
	channel_3.push_back(std::make_unique<tau_neutrino>());
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));
	decay_particles.push_back(std::move(channel_3));
	if (charge != -1.0) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at = it->begin(); at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}