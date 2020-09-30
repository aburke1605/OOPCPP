#include "Circle.h"

circle::circle() : ellipse{} {
	//std::cout << "Default circle constructor called" << std::endl;
}

circle::circle(const double& radius) : ellipse{ radius,radius } {
	//std::cout << "Parametrised circle constructor called" << std::endl;
}

circle::~circle() {
	//std::cout << "Circle destructor called" << std::endl;
}

void circle::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Circle area = " << std::setprecision(1) << area() << ", circumference = " << perimeter() << std::endl;
}