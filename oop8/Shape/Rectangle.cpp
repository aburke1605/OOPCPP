#include "Rectangle.h"

rectangle::rectangle() {
	dimension_1, dimension_2 = 0;
	//std::cout << "Default rectangle constructor called" << std::endl;
}

rectangle::rectangle(const double& length, const double& width) {
	if (length < 0 || width < 0) {
		std::cerr << "Error: rectangle (or rectangle specialisation) dimensions must be positive" << std::endl;
		exit(1);
	}
	dimension_1 = length;
	dimension_2 = width;
	//std::cout << "Parametrised rectangle constructor called" << std::endl;
}

rectangle::~rectangle() {
	//std::cout << "Rectangle destructor called" << std::endl;
}

double rectangle::perimeter() const {
	return 2 * (dimension_1 + dimension_2);
}

double rectangle::area() const {
	return dimension_1 * dimension_2;
}

void rectangle::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Rectangle area = " << std::setprecision(1) << area() << ", perimeter = " << perimeter() << std::endl;
}