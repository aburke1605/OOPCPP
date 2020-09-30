#include "Particle.h"

particle::particle(const double& m, const four_vector& p, const vector& b) {
	if (m < 0 || b.get_length() != 3) {
		std::cerr << "Error: invalid argument(s)" << std::endl;
		exit(1);
	}

	// direct assignment
	mass = m;
	position = p;
	beta = b;
	//std::cout << "Parametrised constructor called" <<std::endl;
}

double particle::get_mass() {
	return mass;
}

double particle::gamma() {
	return 1 / sqrt(1 - beta.dot(beta));
}

double particle::energy() {
	return gamma() * mass; // E = gamma * m * c^2
}

double particle::momentum() {
	return energy() * sqrt(beta.dot(beta)); // p = gamma * m * |beta| * c
}

four_vector particle::four_momentum() {
	four_vector four_m(energy(), beta * gamma() * mass); // p^mu = (E/c, p_x, p_x, p_z)
	return four_m;
}