#ifndef _CHARM_INCL_GUARD
#define _CHARM_INCL_GUARD

#include "Quark.h"

class charm : public up_type::quark
{
public:
	charm(bool is_anticharm = false);
	charm(const double& mom, const double& theta, const double& phi, bool is_anticharm = false);
	~charm();
	void set_decay_modes();
};

#endif