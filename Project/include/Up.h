#ifndef _UP_INCL_GUARD
#define _UP_INCL_GUARD

#include "Quark.h"

class up : public up_type::quark
{
public:
	up(bool is_antiup = false);
	up(const double& mom, const double& theta, const double& phi, bool is_antiup = false);
	~up();
	void set_decay_modes() {} // doesn't decay
};

#endif