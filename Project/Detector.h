#ifndef _DETECTOR_INCL_GUARD
#define _DETECTOR_INCL_GUARD

#define _USE_MATH_DEFINES // for M_PI

#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>

class detector
{
protected:
	const std::pair<double, double> centre_of_detector{ 750, 320 };
	const double max_energy{ 500.0 };
	const double inner_radius;
	const double outer_radius;
	std::map<std::string, double> interactions;

public:
	detector() : inner_radius{}, outer_radius{} {}
	detector(const double& radius_1, const double& radius_2, const COLORREF& colour) :
		inner_radius{ radius_1 }, outer_radius{ radius_2 }
	{
		draw_detector(colour);
	}
	virtual ~detector() {}

	double get_inner_radius() const;
	double get_outer_radius() const;
	const std::pair<double, double>& centre();
	const std::map<std::string, double>& get_interactions() const;

	void draw_detector(sf::RenderWindow& window) const;
};

#endif