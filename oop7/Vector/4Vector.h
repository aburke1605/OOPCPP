#ifndef _4VEC_INCL_GUARD
#define _4VEC_INCL_GUARD

#include "Vector.h"

class four_vector: public vector {
public:
	four_vector();
	four_vector(const double& ct, const double& x, const double& y, const double& z);
	four_vector(const double& ct, const vector& v);
	four_vector(const four_vector& v);
	four_vector(four_vector&& v) noexcept;
	double dot(const vector& v) const;
	four_vector& operator=(const four_vector& v);
	four_vector& operator=(four_vector&& v) noexcept;
	four_vector lorentz_boost(const vector& B) const;
	friend std::ostream& operator<<(std::ostream& os, const four_vector& v);
};

#endif