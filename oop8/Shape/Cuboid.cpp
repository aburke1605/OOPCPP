#include "Cuboid.h"

cuboid::cuboid() {
	dimension_1, dimension_2, dimension_3 = 0;
	//std::cout << "Default cuboid constructor called" << std::endl;
}

cuboid::cuboid(const double& length, const double& width, const double& breadth) {
	if (length < 0 || width < 0 || breadth < 0) {
		std::cerr << "Error: cuboid (or cuboid specialisation) dimensions must be positive" << std::endl;
		exit(1);
	}
	dimension_1 = length;
	dimension_2 = width;
	dimension_3 = breadth;
	//std::cout << "Parametrised cuboid constructor called " << std::endl;
}

cuboid::~cuboid() {
	//std::cout << "Cuboid destructor called" << std::endl;	
}

double cuboid::area() const {
	return 2 * (dimension_1 * dimension_2 + dimension_2 * dimension_3 + dimension_3 * dimension_1);
}

double cuboid::volume() const {
	return dimension_1 * dimension_2 * dimension_3;
}

void cuboid::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Cuboid volume = " << std::setprecision(1) << volume() << ", surface area = " << area() << std::endl;
}