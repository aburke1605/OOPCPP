// abstract derived 2D shape class

#ifndef _2DSHAPE_INCL_GUARD
#define _2DSHAPE_INCL_GUARD

#include "Shape.h"

class two_d_shape : public shape {
public:
	virtual ~two_d_shape() {}
	double volume() const {
		return 0; // volume not defined for 2D shapes
	}
};

#endif