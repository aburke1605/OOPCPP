// abstract base shape class

#ifndef _SHAPE_INCL_GUARD
#define _SHAPE_INCL_GUARD

#define _USE_MATH_DEFINES // for M_PI

#include <iostream>
#include <iomanip>
#include <cmath>

class shape {
protected:
	// assume shapes have at least two dimensions
	double dimension_1;
	double dimension_2;
public:
	virtual ~shape() {}
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual void info() const = 0;
};

#endif