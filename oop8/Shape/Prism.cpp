#include "Prism.h"

prism::prism() {
	dimension_1, dimension_2, dimension_3 = 0;
	//std::cout << "Default prism constructor called" << std::endl;
}

prism::prism(const double& depth, two_d_shape* s) {
	if (depth < 0) {
		std::cerr << "Error: prism depth must be positive" << std::endl;
		exit(1);
	}
	dimension_1 = depth;
	dimension_2 = s->perimeter(); // needed to calculate surface area
	dimension_3 = s->area(); // needed to calculate both surface area and volume
	//std::cout << "Parametrised prism constructor called" << std::endl;
}

prism::~prism() {
	//std::cout << "Prism destructor called" << std::endl;
}

double prism::area() const {
	return dimension_1 * dimension_2 + 2 * dimension_3;
}

double prism::volume() const {
	return dimension_1 * dimension_3; 
}

void prism::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Prism volume = " << std::setprecision(1) << volume() << ", surface area = " << area() << std::endl;
}