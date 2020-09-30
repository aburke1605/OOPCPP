/*
Author: Aodhán Burke
Last Modified: 11/05/2020


This code is my final project on the Object Oriented Programming in C++ course at
the University of Manchester.


The vision of my project is to use the concept of OOP to code a greatly over-
simplified LHC simulator. The code contained a class for each type of fundamental
particle, each detector segment in a general purpose detector, and a final class
to describe one particle event/collision.

There are abstract base classes 'particle' and 'detector' from which all other
classes are derived, except for the 'collision' class which contained particle and
detector data members.

To run the code runs and simulate one event, simply create a default instance of
the collision class. A detector will immediately be drawn in the console window,
however, the position may vary depending on the compiler.

IMPORTANT NOTE: TO ALTER THE COORDINATES OF THE DETECTOR FOR YOUR CONSOLE, PLEASE
				CHANGE THE centre_of_detector MEMBER VARIABLE IN DETECTOR.H
				(x, y) = (0, 0) corresponds to the top left corner of the window,
				with x increasing to the right and y increasing downwards.

Various advanced C++ features are used in the project:
	- multiple header and source files
	- static data
	- exception handling
	- template functions
	- namespaces
	- smart pointers (no raw pointers)
	- lambda functions
*/

#include "Particles.h"
#include "Collision.h"

int main() {
	// seed the 'random_number()' function
	srand((unsigned)std::chrono::system_clock::now().time_since_epoch().count());

	std::map<std::string, std::unique_ptr<particle>> fundamental_particles;
	fundamental_particles["e"] = std::make_unique<electron>(150.0, M_PI / 2, 0.0);
	fundamental_particles["m"] = std::make_unique<muon>(150.0, M_PI / 2, 0.0);
	fundamental_particles["tau"] = std::make_unique<tau>(150.0, M_PI / 2, 0.0);
	fundamental_particles["enu"] = std::make_unique<electron_neutrino>(150.0, M_PI / 2, 0.0);
	fundamental_particles["mn"] = std::make_unique<muon_neutrino>(150.0, M_PI / 2, 0.0);
	fundamental_particles["taunu"] = std::make_unique<tau_neutrino>(150.0, M_PI / 2, 0.0);
	fundamental_particles["u"] = std::make_unique<up>(150.0, M_PI / 2, 0.0);
	fundamental_particles["d"] = std::make_unique<down>(150.0, M_PI / 2, 0.0);
	fundamental_particles["c"] = std::make_unique<charm>(150.0, M_PI / 2, 0.0);
	fundamental_particles["s"] = std::make_unique<strange>(150.0, M_PI / 2, 0.0);
	fundamental_particles["t"] = std::make_unique<top>(150.0, M_PI / 2, 0.0);
	fundamental_particles["b"] = std::make_unique<bottom>(150.0, M_PI / 2, 0.0);
	fundamental_particles["p"] = std::make_unique<photon>(150.0, M_PI / 2, 0.0);
	fundamental_particles["w"] = std::make_unique<w_boson>(150.0, M_PI / 2, 0.0);
	fundamental_particles["z"] = std::make_unique<z_boson>(150.0, M_PI / 2, 0.0);

	HWND my_console = GetConsoleWindow();
	HDC my_dc = GetDC(my_console);

	// print a legend
	HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdout_handle, 13);	std::cout << "Electrons (& neutrinos)" << std::endl;
	SetConsoleTextAttribute(stdout_handle, 9); std::cout << "Muons (& neutrinos)" << std::endl;
	SetConsoleTextAttribute(stdout_handle, 10); std::cout << "Taus (& neutrinos)" << std::endl;
	SetConsoleTextAttribute(stdout_handle, 14);	std::cout << "Photons" << std::endl;
	SetConsoleTextAttribute(stdout_handle, 12);	std::cout << "Hadrons" << std::endl;
	SetConsoleTextAttribute(stdout_handle, 15);

	ReleaseDC(my_console, my_dc);

	std::cout << "Enter number of events... ";
	int number_of_events; std::cin >> number_of_events;
	for (int i{}; i < number_of_events; i++) {
		std::unique_ptr<collision> LHC_event = std::make_unique<collision>();
	}
	std::cout << "Would you like a specific decay? (Y/y)... ";
	std::string answer; std::cin >> answer;
	if (answer == "Y" || answer == "y") {
		std::cout << "Which particle from the list:\n    ";
		for (auto it{ fundamental_particles.begin() }; it != fundamental_particles.end(); it++) {
			std::cout << it->first << ",";
		}
		std::cout << std::endl << "(prepend \"a\" for the equivalent antiparticle)?... ";
		std::string which; std::cin >> which;
		bool anti{ false };
		if (which[0] == 'a') {
			which = which.substr(1, which.size() - 1);
			std::cout << which << std::endl;
			anti = true;
		}
		auto iterator{ fundamental_particles.find(which) };
		if (iterator != fundamental_particles.end()) {
			std::unique_ptr<particle> particle_type{ std::move(iterator->second) };
			if (anti && which != "p" && which != "z") {
				particle_type->make_antiparticle();
			}
			std::unique_ptr<collision> decay = std::make_unique<collision>(particle_type);
		}
		else {
			std::cout << "Particle type not found." << std::endl;
		}
	}
	std::cout << "Enter anything to end... ";
	std::string a; std::cin >> a;

	return 0;
}