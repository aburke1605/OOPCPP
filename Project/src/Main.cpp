/*
Author: Aodh�n Burke
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

#include "../include/Session.h"
#include "../include/Particle.h"
#include "../include/Particles.h"
#include "../include/Collision.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif


#ifdef __EMSCRIPTEN__
    const std::string fontPath = "/arial.ttf";
#else
    const std::string fontPath = "assets/arial.ttf";
#endif


int main() {	
	unsigned int grid_dimension = 600;
	sf::RenderWindow window(sf::VideoMode(grid_dimension, grid_dimension + 75), "HEP detector");

	Session session{
		window,
		false
	};

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

	while (window.isOpen()) {
		window.clear(sf::Color::Black); // reset previous frame

		sf::Font* font = new sf::Font;
		if (!font->loadFromFile(fontPath)) {
			return EXIT_FAILURE;
		}

		sf::Text text;
		text.setFont(*font);
		text.setCharacterSize(15); // in pixels, not points!
		text.setStyle(sf::Text::Bold);

		text.setPosition(sf::Vector2f(4.0f, 0.0f));
		text.setString("Electrons (& neutrinos)");
		text.setFillColor(sf::Color::Magenta);
		window.draw(text);

		text.setPosition(sf::Vector2f(4.0f, 15.0f));
		text.setString("Muons (& neutrinos)");
		text.setFillColor(sf::Color::Blue);
		window.draw(text);

		text.setPosition(sf::Vector2f(4.0f, 30.0f));
		text.setString("Taus (& neutrinos)");
		text.setFillColor(sf::Color::Green);
		window.draw(text);

		text.setPosition(sf::Vector2f(4.0f, 45.0f));
		text.setString("Photons");
		text.setFillColor(sf::Color::Yellow);
		window.draw(text);

		text.setPosition(sf::Vector2f(4.0f, 60.0f));
		text.setString("Hadrons");
		text.setFillColor(sf::Color::Red);
		window.draw(text);


		text.setPosition(sf::Vector2f(grid_dimension /  2 + 4.0f, 0.0f));
		text.setString("Tracker");
		text.setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 150));
		window.draw(text);

		text.setPosition(sf::Vector2f(grid_dimension /  2 + 4.0f, 15.0f));
		text.setString("Electromagnetic calorimeter");
		text.setFillColor(sf::Color(sf::Color::Green.r, sf::Color::Green.g, sf::Color::Green.b, 150));
		window.draw(text);

		text.setPosition(sf::Vector2f(grid_dimension /  2 + 4.0f, 30.0f));
		text.setString("Hadronic calorimeter");
		text.setFillColor(sf::Color(sf::Color::Red.r, sf::Color::Red.g, sf::Color::Red.b, 150));
		window.draw(text);

		text.setPosition(sf::Vector2f(grid_dimension /  2 + 4.0f, 45.0f));
		text.setString("Muon chamber");
		text.setFillColor(sf::Color(sf::Color::Blue.r, sf::Color::Blue.g, sf::Color::Blue.b, 150));
		window.draw(text);

		window.display();

		text.setPosition(sf::Vector2f(grid_dimension * 0.75, grid_dimension * 0.9 + 75));
		text.setFillColor(sf::Color::White);
		text.setString("Event count:");
		window.draw(text);
		window.display();
		sf::RectangleShape hide(sf::Vector2f(130, 20));
		hide.setPosition(grid_dimension * 0.75, grid_dimension * 0.9 + 75);
		hide.setFillColor(sf::Color::Black);

		for (int i{}; i < 10; i++) {
			std::unique_ptr<collision> LHC_event = std::make_unique<collision>(session);

			window.draw(hide);
			sf::String event_count("Event count: " + std::to_string(i+1));
			text.setString(event_count);
			window.draw(text);
			window.display();

			sleep_ms(1000);
		}

		session.detector = false;
		sleep_ms(5000);
	}

	return 0;
}