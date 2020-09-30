#ifndef _CUBOID_INCL_GUARD
#define _CUBOID_INCL_GUARD

#include "3DShape.h"

class cuboid : public three_d_shape {
public:
	cuboid();
	cuboid(const double& length, const double& width, const double& breadth);
	~cuboid();
	double area() const;
	double volume() const;
	void info() const;
};

#endif