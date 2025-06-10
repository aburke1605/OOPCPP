#ifndef _SESSION_INCL_GUARD
#define _SESSION_INCL_GUARD

#include <SFML/Graphics.hpp>

typedef struct {
	sf::RenderWindow& window;
	bool detector;
} Session;

#endif