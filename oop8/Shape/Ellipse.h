#ifndef _ELLIPSE_INCL_GUARD
#define _ELLIPSE_INCL_GUARD

#include "2DShape.h"

class ellipse : public two_d_shape {
public:
	ellipse();
	ellipse(const double& semi_axis_1, const double& semi_axis_2);
	~ellipse();
	double perimeter() const;
	double area() const;
	void info() const;
};

#endif