#ifndef _RANDOM_INCL_GUARD
#define _RANDOM_INCL_GUARD

#include <random>

// template function to return doubles or integers
template <class T> T random_number(T lower_bound, T upper_bound)
{
	T number{ (T)(rand() % 10000) }; // [0., 9999.]
	number *= (upper_bound - lower_bound); // [0., (upper-lower)*9999.]
	number /= 10000; // [0., upper-lower]
	number += lower_bound; // [lower, upper]
	return number;
}

#endif