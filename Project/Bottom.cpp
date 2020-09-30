#include "Particles.h"

bottom::bottom(bool is_antibottom)
{
	type = "BOTTOM";
	mass = 4.18;
	if (is_antibottom) {
		this->make_antiparticle();
	}
	//std::cout << "Default bottom-quark constructor called" << std::endl;
}

bottom::bottom(const double& mom, const double& theta, const double& phi, bool is_antibottom)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid bottom-quark absolute momentum" << std::endl;
		exit(1);
	}
	type = "BOTTOM";
	mass = 4.18;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antibottom) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised bottom-quark constructor called" << std::endl;
}

bottom::~bottom()
{
	//std::cout << "Bottom-quark destructor called" << std::endl;
}

void bottom::set_decay_modes()
{
	// charm: 92.1 %
	// up: 7.9 %
	std::vector<std::unique_ptr<particle>> channel_1, channel_2;
	channel_1.push_back(std::make_unique<charm>()); channel_1.push_back(std::make_unique<w_boson>());
	channel_2.push_back(std::make_unique<up>()); channel_2.push_back(std::make_unique<w_boson>());
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));
	if (charge != -1.0 / 3) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at{ it->begin() }; at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}