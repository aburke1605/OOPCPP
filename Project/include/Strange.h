#ifndef _STRANGE_INCL_GUARD
#define _STRANGE_INCL_GUARD

#include "Quark.h"

class strange : public down_type::quark
{
public:
	strange(bool is_antistrange = false);
	strange(const double& mom, const double& theta, const double& phi, bool is_antistrange = false);
	~strange();
	void set_decay_modes();
};

#endif