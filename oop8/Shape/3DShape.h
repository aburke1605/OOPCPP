// abstract derived 3D shape class

#ifndef _3DSHAPE_INCL_GUARD
#define _3DSHAPE_INCL_GUARD

#include "Shape.h"

class three_d_shape : public shape {
protected:
	double dimension_3; // extra dimension storage
public:
	virtual ~three_d_shape() {}
	double perimeter() const {
		return 0; // perimeter not defined for 3D shapes
	}
};

#endif