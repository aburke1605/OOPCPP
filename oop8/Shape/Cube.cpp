#include "Cube.h"

cube::cube() : cuboid{} {
	//std::cout << "Default cube constructor called" << std::endl;
}

cube::cube(const double& length) : cuboid{ length,length,length } {
	//std::cout << "Parametrised cube constructor called" << std::endl;
}

cube::~cube() {
	//std::cout << "Cube destructor called" << std::endl;
}

void cube::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Cube volume = " << std::setprecision(1) << volume() << ", surface area = " << area() << std::endl;
}