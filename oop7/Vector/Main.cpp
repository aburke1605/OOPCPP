#include "Particle.h"

int main() {
	std::cout << "DEMONSTRATION OF VECTOR CLASS:" << std::endl << std::endl;

	vector v1;
	std::cout << "Defaultly constructed vector:\nv1 = " << v1 << std::endl << std::endl;

	vector v2(3);
	v2[0] = 2;
	v2[1] = 2;
	v2[2] = 2;
	std::cout << "Parametrised vector:\nv2 = " << v2 << std::endl << std::endl;

	vector v3{ v2 };
	std::cout << "Deep copy of v2:\nv3 = " << v3 << ", v2 = " << v2 << std::endl << std::endl;

	vector v4{ std::move(v2) };
	std::cout << "Deep move of v2:\nv4 = " << v4 << ", v2 = " << v2 << std::endl << std::endl;

	vector v5(3);
	for (int i{}; i < 3; i++) {
		v5[i] = 5;
	}
	std::cout << "New vector:\nv5 = " << v5 << std::endl
		<< "Dot product:\nv3.v5 = " << v3.dot(v5) << std::endl << std::endl;

	v1 = v4;
	std::cout << "Assigning v1 = v4:\nv1 = " << v1 << ", v4 = " << v4 << std::endl << std::endl;

	v1 = std::move(v5);
	std::cout << "Moving v1 and v5:\nv1 = " << v1 << ", v5 = " << v5 << std::endl << std::endl <<
		"------------------------------------------------------------------" << std::endl << std::endl;

	//-----------------------------------------------------------------------------------------------------//

	std::cout << "DEMONSTRATION OF FOUR_VECTOR CLASS:" << std::endl << std::endl;

	four_vector V1;
	std::cout << "Defaultly constructed 4-vector:\nV1: " << V1 << std::endl << std::endl;

	four_vector V2(2, 2, 2, 2);
	std::cout << "Parametrised 4-vector:\nV2: " << V2 << std::endl << std::endl;

	vector position(3);
	for (int i{}; i < 3; i++) {
		position[i] = 3;
	}
	std::cout << "Position = " << position << std::endl;
	four_vector V3(3, position);
	std::cout << "Same parametrised 4-vector:\nV3: " << V3 << std::endl << std::endl;

	four_vector V4{ V2 };
	std::cout << "Deep copy of V2:\nV4: " << V4 << ", V2: " << V2 << std::endl << std::endl;

	four_vector V5{ std::move(V2) };
	std::cout << "Deep move of V2:\nV5: " << V5 << ", V2: " << V2 << std::endl << std::endl;

	four_vector V6(6, 6, 6, 6);
	std::cout << "New vector:\nV6: " << V6 << std::endl
		<< "Dot product:\nV3.V6 = " << V3.dot(V6) << std::endl << std::endl;

	V1 = V6;
	std::cout << "Assigning V1 = V6:\nV1: " << V1 << ", V6: " << V6 << std::endl << std::endl;

	V1 = std::move(V5);
	std::cout << "Moving V1 and V5:\nV1: " << V1 << ", V5: " << V5 << std::endl << std::endl;

	vector boost(3);
	boost[0] = 0.99;
	std::cout << "Lorentz boosted V1: " << V1.lorentz_boost(boost) << std::endl << std::endl <<
		"------------------------------------------------------------------" << std::endl << std::endl;

	//-----------------------------------------------------------------------------------------------------//

	std::cout << "DEMONSTRATION OF PARTICLE CLASS:" << std::endl << std::endl;

	// MeV
	four_vector electron_position(1, 1, 1, 1);
	vector beta(3);
	beta[0] = 0.95; // 0.95c ; b1 = b2 = 0, propagating in +x direction
	particle electron(0.511, electron_position, beta);
	std::cout << "Electron:\n"
		"mass = " << electron.get_mass() << " MeV/c^2\n"
		"gamma = " << electron.gamma() << "\n"
		"total energy = " << electron.energy() << " MeV\n"
		"momentum = " << electron.momentum() << " MeV/c\n"
		"position: " << electron_position << std::endl;

	return 0;
}