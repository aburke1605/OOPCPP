#include "../include/Particles.h"

up::up(bool is_antiup)
{
	type = "UP";
	mass = 2.3e-3;
	if (is_antiup) {
		this->make_antiparticle();
	}
	//std::cout << "Default up-quark constructor called" << std::endl;
}

up::up(const double& mom, const double& theta, const double& phi, bool is_antiup)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid up-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "UP";
	mass = 2.3e-3;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antiup) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised up-quark constructor called" << std::endl;
}

up::~up()
{
	//std::cout << "Up-quark destructor called" << std::endl;
}