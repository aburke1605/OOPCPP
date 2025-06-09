#ifndef _COLLISION_INCL_GUARD
#define _COLLISION_INCL_GUARD

#include "Session.h"
#include "Particle.h"
#include "Particles.h"
#include "Detectors.h"

class collision
{
private:
	static const std::map<std::string, COLORREF> colours;
	static const std::vector<std::shared_ptr<detector>> detector_segments; // must be a shared smart pointer if the detector segments are static members
	std::vector<std::pair<std::unique_ptr<particle>, std::pair<double, double>>> particles;

public:
	collision(Session& session);
	collision(Session& session, std::unique_ptr<particle>& p);
	~collision();

	const std::pair<double, double>& centre();
	void draw_event(Session& session);
};

#endif