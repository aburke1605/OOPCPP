#include "Sphere.h"

sphere::sphere() : ellipsoid{} {
	//std::cout << "Defeault sphere constructor called" << std::endl;
}

sphere::sphere(const double& radius) : ellipsoid{ radius,radius,radius } {
	//std::cout << "Parametrised sphere constructor called" << std::endl;
}

sphere::~sphere() {
	//std::cout << "Sphere destructor called" << std::endl;
}

void sphere::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Sphere volume = " << std::setprecision(1) << volume() << ", surface area = " << area() << std::endl;
}