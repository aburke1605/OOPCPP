#include "Particle.h"
#include "Recoil.h"

std::string particle::get_type() const
{
	return type;
}

double particle::get_mass() const
{
	return mass;
}

double particle::get_charge() const
{
	return charge;
}

const std::vector<double>& particle::get_momentum_vector() const
{
	return momentum;
}

double particle::get_momentum() const
{
	return sqrt(pow(momentum[0], 2) + pow(momentum[1], 2) + pow(momentum[2], 2));
}

void particle::set_momentum(std::vector<double>& mom)
{
	momentum = mom;
}

double particle::get_theta() const
{
	double theta;
	const int divide_flag(-1);
	try {
		if (get_momentum() == 0) {
			throw divide_flag;
		}
		theta = acos(momentum[2] / get_momentum());
	}
	catch (int error) {
		if (error == divide_flag) {
			theta = 0.0; // arbitrary if momentum is zero
		}
	}
	return theta;
}

double particle::get_phi() const
{
	double phi;
	const int divide_flag(-1);
	try {
		if (get_momentum() == 0 || get_theta() == 0) {
			throw divide_flag;
		}
		phi = atan2(momentum[1], momentum[0]);
	}
	catch (int error) {
		if (error == divide_flag) {
			phi = 0.0; // arbitrary if transverse component is zero
		}
	}
	return phi;
}

void particle::set_phi(const double& phi)
{
	double old_momentum{ this->get_momentum() };
	momentum[0] = old_momentum * sin(this->get_theta()) * cos(phi);
	momentum[1] = old_momentum * sin(this->get_theta()) * sin(phi);
}

double particle::get_energy() const
{
	return sqrt(pow(get_momentum(), 2) + pow(get_mass(), 2));
}

void particle::reduce_energy(const double& energy)
{
	double new_energy{ get_energy() - energy };
	if (new_energy < mass) {
		new_energy = mass;
	}
	double new_momentum{ sqrt(pow(new_energy, 2) - pow(get_mass(), 2)) };
	momentum[0] = new_momentum * sin(get_theta()) * cos(get_phi());
	momentum[1] = new_momentum * sin(get_theta()) * sin(get_phi());
	momentum[2] = new_momentum * cos(get_theta());
}

std::vector<std::unique_ptr<particle>>& particle::get_decay_particles()
{
	if (decay_particles.size() == 0) {
		std::vector<std::unique_ptr<particle>> dummy;
		decay_particles.push_back(std::move(dummy));
	}
	return *decay_particles.begin();
}

void particle::set_decay_particles(std::vector<std::vector<std::unique_ptr<particle>>>& particles)
{
	decay_particles.clear();
	decay_particles = std::move(particles);
}

void particle::display_info() const
{
	std::cout << type << " mass = " << mass << " GeV, electric charge = " << charge
		<< "e" << std::endl
		<< "momentum = " << get_momentum() << " GeV, theta = " << get_theta() << ", phi = " << get_phi() << std::endl;
	if (decay_particles.size() > 0) {
		std::cout << "Decay particles:" << std::endl;
		int i{};
		for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
			i++;
			std::cout << "  Decay mode " << i << ":" << std::endl;
			for (auto at = it->begin(); at != it->end(); at++) {
				std::cout << "    ";
				(*at)->display_info();
			}
		}
		std::cout << std::endl;
	}
}

void particle::make_antiparticle()
{
	charge *= -1;
	if (type.substr(0, 4) == "ANTI") {
		type.erase(0, 4);
	}
	else {
		type.insert(0, "ANTI");
	}
	for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
		for (auto at{ it->begin() }; at != it->end(); at++) {
			(*at)->make_antiparticle();
		}
	}
}

void particle::decay(particle& parent_particle, const double& momentum)
{
	/*
	A function to select a decay channel at random from the possibile
	channels available to a particle and calculate the kinematics
	associated with the decay particles
	args:    1. Reference to a particle which is the original "parent" particle
	         the function was called on. This is passed on in recursive calls
			 to the function such that Lorentz boosts are always calculated
			 with respect to the correct original frame of reference.
			 2. A momentum which is used in the case of a recursive call on a
			 "dummy" recoil particle to calculate its "mass".
	returns: void - clears the 'decay_particles' vector and replaces it with a
	         unit length vector containing a vector of decay particles with
			 correctly calculated momenta.
	*/

	// choose a random decay channel from the possibilities in 
	// 'decay_particles', respecting energy conservation
	std::vector<int> allowed_channels;
	int i{};
	for (auto it{ decay_particles.begin() }; it != decay_particles.end(); it++) {
		double total_mass{};
		for (auto at{ it->begin() }; at != it->end(); at++) {
			total_mass += (*at)->get_mass();
		}
		if (total_mass < this->get_energy()) {
			allowed_channels.push_back(i);
		}
		i++;
	}
	int channel;
	if (allowed_channels.size() > 0) {
		channel = allowed_channels[random_number<int>(0, (int)allowed_channels.size())];
	}
	else {
		decay_particles.clear();
		return;
	}

	// first daughter particle calculation
	double mom, theta, phi, mom_x, mom_y, mom_z, mom_1_x_lab, mom_1_y_lab, mom_1_z_lab;
	// all in lab frame, with z axis defined along the parent particle momentum vector
	if (this->mass != 0) {
		double final_mass_sq_sum{};
		for (auto it{ decay_particles[channel].begin() }; it != decay_particles[channel].end(); it++) {
			final_mass_sq_sum += pow((*it)->get_mass(), 2);
		}
		mom = 0.7 * sqrt((pow(parent_particle.get_energy(), 2) - final_mass_sq_sum) / 2);
	}
	else { // zero mass (photons)
		mom = sqrt(pow(this->get_momentum(), 2) / 4 - pow(decay_particles[channel][0]->mass, 2));
	}
	theta = 0.25; // corresponds to polar angle from z axis defined as the parent particle momentum vector
	phi = random_number<double>(-M_PI, M_PI); // corresponds to the randomly generated azimuthal angle around parent particle momentum vector
	mom_x = mom * sin(theta) * cos(phi);
	mom_y = mom * sin(theta) * sin(phi);
	mom_z = mom * cos(theta);
	// rotate back to original lab coordinates (parent particle momentum not necessarily along z)
	// rotate around x by -theta then around z by -phi to get back to regular lab frame
	mom_1_x_lab = mom_x * cos(parent_particle.get_theta()) * cos(parent_particle.get_phi())
		- mom_y * cos(parent_particle.get_theta()) * sin(parent_particle.get_phi())
		+ mom_z * sin(parent_particle.get_theta());
	mom_1_y_lab = mom_x * sin(parent_particle.get_phi())
		+ mom_y * cos(parent_particle.get_phi());
	mom_1_z_lab = -mom_x * sin(parent_particle.get_theta()) * cos(parent_particle.get_phi())
		+ mom_y * sin(parent_particle.get_theta()) * sin(parent_particle.get_phi())
		+ mom_z * cos(parent_particle.get_theta());

	std::vector<double> mom_1_lab{ mom_1_x_lab, mom_1_y_lab, mom_1_z_lab };
	this->decay_particles[channel][0]->set_momentum(mom_1_lab);

	if (decay_particles[channel].size() == 2) {
		// second daughter particle calculation
		double mom_2_x_lab{ this->momentum[0] - mom_1_x_lab };
		double mom_2_y_lab{ this->momentum[1] - mom_1_y_lab };
		double mom_2_z_lab{ this->momentum[2] - mom_1_z_lab };

		std::vector<double> mom_2_lab{ mom_2_x_lab, mom_2_y_lab, mom_2_z_lab };
		this->decay_particles[channel][1]->set_momentum(mom_2_lab);
	}
	else{
		// form a recoil system off of the first particle and recursively call the function
		double E_initial{ sqrt(pow(momentum, 2) + pow(this->mass, 2)) };
		double E_particle_1{ sqrt(pow(mom, 2) + pow(decay_particles[channel][0]->get_mass(), 2)) };
		double E_recoil{ E_initial - E_particle_1 };// PROBLEM: this is negative if mass is zero
													// but actually massless particles always decay to only 2 - so ok

		// move the remaining daughter particles onto the recoil system
		std::vector<std::unique_ptr<particle>> remaining_decay_particles;
		std::vector<std::vector<std::unique_ptr<particle>>> decay_channel;
		for (auto it{ decay_particles[channel].begin() + 1 }; it != decay_particles[channel].end(); it++) {
			remaining_decay_particles.push_back(std::move(*it));
		}
		decay_channel.push_back(std::move(remaining_decay_particles));
		while (decay_particles[channel].size() > 1) {
			decay_particles[channel].pop_back();
		}
		recoil r(E_recoil);
		r.set_decay_particles(decay_channel); // should be 1 entry long, which contains at least 2 particles
		r.decay(parent_particle, mom); // parent_particle must be passed to give the appropriate Lorentz boost
		
		// now push the newly calculated particles back to the parent particles 'decay_particles'
		for (auto it{ r.decay_particles[0].begin() }; it != r.decay_particles[0].end(); it++) {
			this->decay_particles[channel].push_back(std::move(*it));
		}
	}

	// delete the other channels!
	std::vector<std::unique_ptr<particle>> temporary_storage{ std::move(decay_particles[channel]) };
	decay_particles.clear();
	decay_particles.push_back(std::move(temporary_storage));
}