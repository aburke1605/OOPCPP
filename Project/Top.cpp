#include "Particles.h"

top::top(bool is_antitop)
{
	type = "TOP";
	mass = 173;
	if (is_antitop) {
		this->make_antiparticle();
	}
	//std::cout << "Default top-quark constructor called" << std::endl;
}

top::top(const double& mom, const double& theta, const double& phi, bool is_antitop)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid top-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "TOP";
	mass = 173;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antitop) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised top-quark constructor called" << std::endl;
}

top::~top()
{
	//std::cout << "Top-quark destructor called" << std::endl;
}

void top::set_decay_modes()
{
	// bottom: 100 %
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<bottom>()); channel_1.push_back(std::make_unique<w_boson>(true));
	decay_particles.push_back(std::move(channel_1));
	if (charge != 2.0 / 3) {
		for (auto it{ decay_particles.begin()->begin() }; it != decay_particles.begin()->end(); it++) {
			(*it)->make_antiparticle();
		}
	}

	this->decay(*this);
}