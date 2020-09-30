#include "Detector.h"

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

void detector::draw_detector(const COLORREF& colour) const
{
	HWND my_console = GetConsoleWindow();
	HDC my_dc = GetDC(my_console);
	for (double i{}; i < 2 * M_PI; i += 0.02) {
		if (inner_radius != 0) {
			SetPixel(my_dc, (int)(inner_radius * cos(i) + centre_of_detector.first), (int)(inner_radius * sin(i) + centre_of_detector.second), RGB(255, 255, 255));
		}
		SetPixel(my_dc, (int)(outer_radius * cos(i) + centre_of_detector.first), (int)(outer_radius * sin(i) + centre_of_detector.second), RGB(255, 255, 255));
		for (double j{ inner_radius + 5 }; j < outer_radius - 5; j += 1) {
			SetPixel(my_dc, (int)(j * cos(i) + centre_of_detector.first), (int)(j * sin(i) + centre_of_detector.second), colour);
		}
	}
}