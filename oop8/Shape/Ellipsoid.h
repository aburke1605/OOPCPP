#ifndef _ELLIPSOID_INCL_GUARD
#define _ELLIPSOID_INCL_GUARD

#include "3DShape.h"

class ellipsoid : public three_d_shape {
public:
	ellipsoid();
	ellipsoid(const double& semi_axis_1, const double& semi_axis_2, const double& semi_axis_3);
	~ellipsoid();
	double area() const;
	double volume() const;
	void info() const;
};

#endif