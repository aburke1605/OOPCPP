#include "../include/Particles.h"

photon::photon()
{
	type = "PHOTON";
	mass = 0;
	charge = 0;
	//std::cout << "Default photon constructor called" << std::endl;
}

photon::photon(const double& mom, const double& theta, const double& phi)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid photon absolute momentum" << std::endl;
		exit(1);
	}
	type = "PHOTON";
	mass = 0;
	charge = 0;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	//std::cout << "Parametrised photon constructor called" << std::endl;
}

photon::~photon()
{
	//std::cout << "Photon destructor called" << std::endl;
}

void photon::set_decay_modes()
{
	std::vector<std::unique_ptr<particle>> channel_1;
	channel_1.push_back(std::make_unique<electron>()); channel_1.push_back(std::make_unique<electron>(true));
	decay_particles.push_back(std::move(channel_1));

	this->decay(*this);
}