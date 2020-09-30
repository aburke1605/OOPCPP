#ifndef _PAR_INCL_GUARD
#define _PAR_INCL_GUARD

#include "4Vector.h"

class particle {
private:
	double mass;
	four_vector position;
	vector beta;
public:
	particle(const double& m, const four_vector& p, const vector& b);
	double get_mass();
	double gamma();
	double energy();
	double momentum();
	four_vector four_momentum();
};

#endif