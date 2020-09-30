#ifndef _QUARK_INCL_GUARD
#define _QUARK_INCL_GUARD

#include "Particle.h"

namespace up_type {
	class quark : public particle
	{
	public:
		quark()
		{
			charge = 2.0 / 3;
		}
		virtual ~quark() {}
	};
}

namespace down_type {
	class quark : public particle
	{
	public:
		quark()
		{
			charge = -1.0 / 3;
		}
		virtual ~quark() {}
	};
}

#endif