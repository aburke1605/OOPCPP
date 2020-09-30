#include "Particles.h"

charm::charm(bool is_anticharm)
{
	type = "CHARM";
	mass = 1.275;
	if (is_anticharm) {
		this->make_antiparticle();
	}
	//std::cout << "Default charm-quark constructor called" << std::endl;
}

charm::charm(const double& mom, const double& theta, const double& phi, bool is_anticharm)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid charm-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "CHARM";
	mass = 1.275;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_anticharm) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised charm-quark constructor called" << std::endl;
}

charm::~charm()
{
	//std::cout << "Charm-quark destructor called" << std::endl;
}

void charm::set_decay_modes()
{
	// strange: 95 %
	// down: 5 %
	std::vector<std::unique_ptr<particle>> channel_1, channel_2;
	channel_1.push_back(std::make_unique<strange>()); channel_1.push_back(std::make_unique<w_boson>(true));
	channel_2.push_back(std::make_unique<down>()); channel_2.push_back(std::make_unique<w_boson>(true));
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));
	if (charge != 2.0 / 3) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at{ it->begin() }; at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}