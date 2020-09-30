#include <vector>
#include "Rectangle.h"
#include "Square.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Cuboid.h"
#include "Cube.h"
#include "Ellipsoid.h"
#include "Sphere.h"
#include "Prism.h"

int main() {
	// demonstrating run-time polymorphism
	std::vector<shape*> shapes;
	shapes.push_back(new rectangle(2, 3));
	shapes.push_back(new square(1.5));
	shapes.push_back(new ellipse(3, 4));
	shapes.push_back(new circle(3));
	shapes.push_back(new cuboid(1, 2, 3));
	shapes.push_back(new cube(2.5));
	shapes.push_back(new ellipsoid(1, 2, 3));
	shapes.push_back(new sphere(10));
	shapes.push_back(new prism(10, new circle(1))); // cylinder
	for (auto it = shapes.begin(); it != shapes.end(); it++) {
		(*it)->info();
		delete* it;
	}
	shapes.clear();

	return 0;
}