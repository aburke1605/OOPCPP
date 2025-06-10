#include "../include/Particles.h"

electron::electron(bool is_positron)
{
	type = "ELECTRON";
	mass = 0.511e-3;
	if (is_positron) {
		this->make_antiparticle();
	}
	//std::cout << "Default electron constructor called" << std::endl;
}

electron::electron(const double& mom, const double& theta, const double& phi, bool is_positron)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid electron absolute momentum" << std::endl;
		exit(1);
	}
	type = "ELECTRON";
	mass = 0.511e-3;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_positron) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised electron constructor called" << std::endl;
}

electron::~electron()
{
	//std::cout << "Electron destructor called" << std::endl;
}

void::electron::set_decay_modes()
{
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<electron>()); channel_1.push_back(std::make_unique<photon>());
	decay_particles.push_back(std::move(channel_1));
	if (charge != -1.0) {
		(*decay_particles.begin()->begin())->make_antiparticle();
	}

	this->decay(*this);
}