#include "Particles.h"

w_boson::w_boson(bool is_antiw_boson)
{
	type = "W BOSON";
	mass = 80.379;
	charge = -1.0;
	if (is_antiw_boson) {
		this->make_antiparticle();
	}
	//std::cout << "Default W-boson constructor called" << std::endl;
}

w_boson::w_boson(const double& mom, const double& theta, const double& phi, bool is_antiw_boson)
{
	if (mom < 0) {
		std::cerr << "ERROR: Invalid W-boson absolute momentum" << std::endl;
		exit(1);
	}
	type = "W BOSON";
	mass = 80.379;
	charge = -1.0;
	momentum[0] = mom * sin(theta) * cos(phi);
	momentum[1] = mom * sin(theta) * sin(phi);
	momentum[2] = mom * cos(theta);
	if (is_antiw_boson) {
		this->make_antiparticle();
	}
	//std::cout << "Parametrised W-boson constructor called" << std::endl;
}

w_boson::~w_boson()
{
	//std::cout << "W-boson destructor called" << std::endl;
}

void w_boson::set_decay_modes()
{
	// anything
	std::vector<std::unique_ptr<particle>> channel_1, channel_2, channel_3,
		channel_4, channel_5, channel_6, channel_7, channel_8, channel_9;
	channel_1.push_back(std::make_unique<electron>()); channel_1.push_back(std::make_unique<electron_neutrino>(true));
	channel_2.push_back(std::make_unique<muon>()); channel_2.push_back(std::make_unique<muon_neutrino>(true));
	channel_3.push_back(std::make_unique<tau>()); channel_3.push_back(std::make_unique<tau_neutrino>(true));
	channel_4.push_back(std::make_unique<up>(true)); channel_4.push_back(std::make_unique<down>());
	channel_5.push_back(std::make_unique<up>(true)); channel_5.push_back(std::make_unique<strange>());
	channel_6.push_back(std::make_unique<up>(true)); channel_6.push_back(std::make_unique<bottom>());
	channel_7.push_back(std::make_unique<charm>(true)); channel_7.push_back(std::make_unique<down>());
	channel_8.push_back(std::make_unique<charm>(true)); channel_8.push_back(std::make_unique<strange>());
	channel_9.push_back(std::make_unique<charm>(true)); channel_9.push_back(std::make_unique<bottom>());
	decay_particles.push_back(std::move(channel_1));
	decay_particles.push_back(std::move(channel_2));
	decay_particles.push_back(std::move(channel_3));
	decay_particles.push_back(std::move(channel_4));
	decay_particles.push_back(std::move(channel_5));
	decay_particles.push_back(std::move(channel_6));
	decay_particles.push_back(std::move(channel_7));
	decay_particles.push_back(std::move(channel_8));
	decay_particles.push_back(std::move(channel_9));
	if (charge != -1.0) {
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			for (auto at = it->begin(); at != it->end(); at++) {
				(*at)->make_antiparticle();
			}
		}
	}

	this->decay(*this);
}