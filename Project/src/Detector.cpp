#include "../include/Detector.h"

double detector::get_inner_radius() const
{
	return inner_radius;
}

double detector::get_outer_radius() const
{
	return outer_radius;
}

const std::pair<double, double>& detector::centre()
{
	return centre_of_detector;
}

const std::map<std::string, double>& detector::get_interactions() const
{
	return interactions;
}

void detector::draw_detector(sf::RenderWindow& window) const
{
	sf::CircleShape ring(inner_radius + 5);
	ring.setPosition(centre_of_detector.first - inner_radius, centre_of_detector.second - inner_radius);
	ring.setFillColor(sf::Color(0, 0, 0, 0)); // transparent inner
	ring.setOutlineThickness((outer_radius - 5) - (inner_radius + 5));
	ring.setOutlineColor(sf::Color(colour.r, colour.g, colour.b, 100));
	window.draw(ring);
}