#include "../include/Particles.h"

strange::strange(bool is_antistrange)
{
	type = "STRANGE";
	mass = 95e-3;
	if (is_antistrange) {
		this->make_antiparticle();
	}
	//std::cout << "Default strange-quark constructor called" << std::endl;
}

strange::strange(const double& mom, const double& theta, const double& phi, bool is_antistrange)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid strange-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "STRANGE";
	mass = 95e-3;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antistrange) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised strange-quark constructor called" << std::endl;
}

strange::~strange()
{
	//std::cout << "Strange-quark destructor called" << std::endl;
}

void strange::set_decay_modes()
{
	// up: 100 % ?
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<up>()); channel_1.push_back(std::make_unique<w_boson>());
	decay_particles.push_back(std::move(channel_1));
	if (charge != -1.0 / 3) {
		for (auto it{ decay_particles.begin()->begin() }; it != decay_particles.begin()->end(); it++) {
			(*it)->make_antiparticle();
		}
	}

	this->decay(*this);
}