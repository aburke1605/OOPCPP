#include "../include/Particles.h"

z_boson::z_boson()
{
	type = "Z BOSON";
	mass = 91.1876;
	charge = 0;
	//std::cout << "Default Z-boson constructor called" << std::endl;
}

z_boson::z_boson(const double& mom, const double& theta, const double& phi)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid Z-boson absolute momentum" << std::endl;
		exit(1);
	}
	type = "Z BOSON";
	mass = 91.1876;
	charge = 0;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	//std::cout << "Parametrised Z-boson constructor called" << std::endl;
}

z_boson::~z_boson()
{
	//std::cout << "Z-boson destructor called" << std::endl;
}

void z_boson::set_decay_modes()
{
	// anything
	std::vector<std::unique_ptr<particle>> channel_1, channel_2, channel_3, channel_4,
		channel_5, channel_6, channel_7, channel_8, channel_9, channel_10, channel_11;
	channel_1.push_back(std::make_unique<electron>()); channel_1.push_back(std::make_unique<electron>(true));
	channel_2.push_back(std::make_unique<muon>()); channel_2.push_back(std::make_unique<muon>(true));
	channel_3.push_back(std::make_unique<tau>()); channel_3.push_back(std::make_unique<tau>(true));
	channel_4.push_back(std::make_unique<electron_neutrino>()); channel_4.push_back(std::make_unique<electron_neutrino>(true));
	channel_5.push_back(std::make_unique<muon_neutrino>()); channel_5.push_back(std::make_unique<muon_neutrino>(true));
	channel_6.push_back(std::make_unique<tau_neutrino>()); channel_6.push_back(std::make_unique<tau_neutrino>(true));
	channel_7.push_back(std::make_unique<up>()); channel_7.push_back(std::make_unique<up>(true));
	channel_8.push_back(std::make_unique<down>()); channel_8.push_back(std::make_unique<down>(true));
	channel_9.push_back(std::make_unique<charm>()); channel_9.push_back(std::make_unique<charm>(true));
	channel_10.push_back(std::make_unique<strange>()); channel_10.push_back(std::make_unique<strange>(true));
	channel_11.push_back(std::make_unique<bottom>()); channel_11.push_back(std::make_unique<bottom>(true));
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));
	decay_particles.push_back(std::move(channel_3));
	decay_particles.push_back(std::move(channel_4));
	decay_particles.push_back(std::move(channel_5));
	decay_particles.push_back(std::move(channel_6));
	decay_particles.push_back(std::move(channel_7));
	decay_particles.push_back(std::move(channel_8));
	decay_particles.push_back(std::move(channel_9));
	decay_particles.push_back(std::move(channel_10));
	decay_particles.push_back(std::move(channel_11));

	this->decay(*this);
}