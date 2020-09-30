#ifndef _BOTTOM_INCL_GUARD
#define _BOTTOM_INCL_GUARD

#include "Quark.h"

class bottom : public down_type::quark
{
public:
	bottom(bool is_antibottom = false);
	bottom(const double& mom, const double& theta, const double& phi, bool is_antibottom = false);
	~bottom();
	void set_decay_modes();
};

#endif