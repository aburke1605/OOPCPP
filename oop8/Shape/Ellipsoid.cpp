#include "Ellipsoid.h"

ellipsoid::ellipsoid() {
	dimension_1, dimension_2, dimension_3 = 0;
	//std::cout << "Default ellipsoid constructor called" << std::endl;
}


ellipsoid::ellipsoid(const double& semi_axis_1, const double& semi_axis_2, const double& semi_axis_3) {
	if (semi_axis_1 < 0 || semi_axis_2 < 0 || semi_axis_3 < 0) {
		std::cerr << "Error: ellipsoid (or ellipsoid specialisation) radii must be positive" << std::endl;
		exit(1);
	}
	dimension_1 = semi_axis_1;
	dimension_2 = semi_axis_2;
	dimension_3 = semi_axis_3;
	//std::cout << "Parametrised ellipsoid constructor called" << std::endl;
}

ellipsoid::~ellipsoid() {
	//std::cout << "Ellipsoid destructor called" << std::endl;
}

double ellipsoid::area() const {
	double x{ 1.6 };
	double surface_area{ pow(dimension_1 * dimension_2,x) + pow(dimension_2 * dimension_3,x) + pow(dimension_3 * dimension_1,x) };
	surface_area /= 3;
	surface_area = 4 * M_PI * pow(surface_area, 1 / x);
	return surface_area; // approximate for ellipsoid, exact for sphere: https://en.wikipedia.org/wiki/Ellipsoid#Surface_area
}

double ellipsoid::volume() const {
	return 4 * M_PI * dimension_1 * dimension_2 * dimension_3 / 3;
}

void ellipsoid::info() const {
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "Ellipsoid volume = " << std::setprecision(1) << volume() << ", surface area = " << area() << std::endl;
}