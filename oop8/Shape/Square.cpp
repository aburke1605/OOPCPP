#include "Square.h"

square::square() : rectangle{} {
	//std::cout << "Default square contructor called" << std::endl;
}

square::square(const double& length) : rectangle{ length,length } {
	//std::cout << "Parametrised square constructor called" << std::endl;
}

square::~square() {
	//std::cout << "Square destructor called" << std::endl;
}

void square::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Square area = " << std::setprecision(1) << area() << ", perimeter = " << perimeter() << std::endl;
}