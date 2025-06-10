#ifndef _PARTICLE_INCL_HEADER
#define _PARTICLE_INCL_HEADER

constexpr double pi = 3.14159265358979323846;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <memory>
#include "Random.h"

class particle
{
protected:
	std::string type;
	double mass; // GeV
	double charge; // e
	std::vector<double> momentum{ 0.0,0.0,0.0 }; // GeV
	std::vector<std::vector<std::unique_ptr<particle>>> decay_particles;

public:
	virtual ~particle() {}
	virtual void set_decay_modes() = 0;

	std::string get_type() const;
	double get_mass() const;
	double get_charge() const;
	const std::vector<double>& get_momentum_vector() const;
	double get_momentum() const;
	void set_momentum(std::vector<double>& mom);
	double get_theta() const;
	double get_phi() const;
	void set_phi(const double& phi);
	double get_energy() const;
	void reduce_energy(const double& energy);
	std::vector<std::unique_ptr<particle>>& get_decay_particles();
	void set_decay_particles(std::vector<std::vector<std::unique_ptr<particle>>>& particles);

	void display_info() const;
	void make_antiparticle();
	void decay(particle& parent_particle, const double& momentum = 0.0);
};

#endif