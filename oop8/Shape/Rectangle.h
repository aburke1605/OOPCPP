#ifndef _RECTANGLE_INCL_GUARD
#define _RECTANGLE_INCL_GUARD

#include "2DShape.h"

class rectangle : public two_d_shape {
public:
	rectangle();
	rectangle(const double& length, const double& width);
	~rectangle();
	double perimeter() const;
	double area() const;
	void info() const;
};

#endif