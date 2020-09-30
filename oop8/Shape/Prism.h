#ifndef _PRISM_INCL_GUARD
#define _PRISM_INCL_GUARD

#include "2DShape.h"
#include "3DShape.h"

class prism : public three_d_shape {
public:
	prism();
	prism(const double& depth, two_d_shape* s);
	~prism();
	double area() const;
	double volume() const;
	void info() const;
};

#endif