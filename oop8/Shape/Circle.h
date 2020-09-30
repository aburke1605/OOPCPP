#ifndef _CIRCLE_INCL_GUARD
#define _CIRCLE_INCL_GUARD

#include "Ellipse.h"

class circle : public ellipse {
public:
	circle();
	circle(const double& radius);
	~circle();
	void info() const;
};

#endif