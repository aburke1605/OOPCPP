#ifndef _DOWN_INCL_GUARD
#define _DOWN_INCL_GUARD

#include "Quark.h"

class down : public down_type::quark
{
public:
	down(bool is_antidown = false);
	down(const double& mom, const double& theta, const double& phi, bool is_antidown = false);
	~down();
	void set_decay_modes();
};

#endif