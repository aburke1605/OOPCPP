#include "Ellipse.h"

ellipse::ellipse() {
	dimension_1, dimension_2 = 0;
	//std::cout << "Default ellipse constructor called" << std::endl;
}

ellipse::ellipse(const double& semi_axis_1, const double& semi_axis_2) {
	if (semi_axis_1 < 0 || semi_axis_2 < 0) {
		std::cerr << "Error: ellipse (or ellipse specialisation) radii must be positive" << std::endl;
		exit(1);
	}
	dimension_1 = semi_axis_1;
	dimension_2 = semi_axis_2;
	//std::cout << "Parametrised ellipse constructor called" << std::endl;
}

ellipse::~ellipse() {
	//std::cout << "Ellipse destructor called" << std::endl;
}

double ellipse::perimeter() const {
	// approximate for ellipse, exact for circle: https://en.wikipedia.org/wiki/Ellipse#Circumference
	double circumference{ sqrt((3 * dimension_1 + dimension_2) * (dimension_1 + 3 * dimension_2)) };
	circumference = 3 * (dimension_1 + dimension_2) - circumference;
	circumference *= M_PI;
	return circumference;
}

double ellipse::area() const {
	return M_PI * dimension_1 * dimension_2;
}

void ellipse::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Ellipse area = " << std::setprecision(1) << area() << ", circumference = " << perimeter() << std::endl;
}