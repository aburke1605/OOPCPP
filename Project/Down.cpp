#include "Particles.h"

down::down(bool is_antidown)
{
	type = "DOWN";
	mass = 4.7e-3;
	if (is_antidown) {
		this->make_antiparticle();
	}
	//std::cout << "Default down-quark constructor called" << std::endl;
}

down::down(const double& mom, const double& theta, const double& phi, bool is_antidown)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid down-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "DOWN";
	mass = 4.7e-3;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antidown) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised down-quark constructor called" << std::endl;
}

down::~down()
{
	//std::cout << "Down-quark destructor called" << std::endl;
}

void down::set_decay_modes()
{
	// up: 100 %
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<up>()); channel_1.push_back(std::make_unique<w_boson>());
	decay_particles.push_back(std::move(channel_1));
	if (charge != -1.0 / 3) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at = it->begin(); at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}