#include "Particles.h"

gluon::gluon()
{
	type = "GLUON";
	mass = 0;
	charge = 0;
	//std::cout << "Default gluon constructor called" << std::endl;
}

gluon::gluon(const double& mom, const double& theta, const double& phi)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid gluon absolute momentum" << std::endl;
		exit(1);
	}
	type = "GLUON";
	mass = 0;
	charge = 0;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	//std::cout << "Parametrised gluon constructor called" << std::endl;
}

gluon::~gluon()
{
	//std::cout << "Gluon destructor called" << std::endl;
}

void gluon::set_decay_modes()
{
	// ignoring hadronisation so gluons are only present
	// at collision time. in this case the only interesting
	// decays are to ups or downs
	std::vector<std::unique_ptr<particle>> channel_1, channel_2; 
	channel_1.push_back(std::make_unique<up>()); channel_1.push_back(std::make_unique<up>(true));
	channel_2.push_back(std::make_unique<down>()); channel_2.push_back(std::make_unique<down>(true));
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));

	this->decay(*this);
}