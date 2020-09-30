#ifndef _SPHERE_INCL_GUARD
#define _SPHERE_INCL_GUARD

#include "Ellipsoid.h"

class sphere : public ellipsoid {
public:
	sphere();
	sphere(const double& radius);
	~sphere();
	void info() const;
};

#endif