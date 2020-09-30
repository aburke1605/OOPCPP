#ifndef _CUBE_INCL_GUARD
#define _CUBE_INCL_GUARD

#include "Cuboid.h"

class cube : public cuboid {
public:
	cube();
	cube(const double& length);
	~cube();
	void info() const;
};

#endif