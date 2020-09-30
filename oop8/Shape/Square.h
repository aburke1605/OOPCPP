#ifndef _SQUARE_INCL_GUARD
#define _SQUARE_INCL_GUARD

#include "Rectangle.h"

class square : public rectangle {
public:
	square();
	square(const double& length);
	~square();
	void info() const;
};

#endif