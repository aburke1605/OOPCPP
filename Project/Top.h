#ifndef _TOP_INCL_GUARD
#define _TOP_INCL_GUARD

#include "Quark.h"

class top : public up_type::quark
{
public:
	top(bool is_antitop = false);
	top(const double& mom, const double& theta, const double& phi, bool is_antitop = false);
	~top();
	void set_decay_modes();
};

#endif