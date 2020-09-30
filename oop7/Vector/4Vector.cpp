#include "4Vector.h"

four_vector::four_vector() : vector(4) { // all four_vector objects are vector objects of length 4
	for (int i{}; i < 4; i++) {
		(*this)[i] = 0;
	}
	//std::cout << "Default 4-vector constructor called" << std::endl;
}

four_vector::four_vector(const double& ct, const double& x, const double& y, const double& z) : vector(4) {
	(*this)[0] = ct; (*this)[1] = x; (*this)[2] = y; (*this)[3] = z;
	//std::cout << "Coordinate 4-vector constructor called" << std::endl;
}

four_vector::four_vector(const double& ct, const vector& v) : vector(4) {
	if (v.get_length() != 3) {
		std::cerr << "Error: position vector is not 3-dimensional" << std::endl;
		exit(1);
	}

	(*this)[0] = ct;
	for (int i{}; i < 3; i++) {
		(*this)[i + 1] = v[i]; // first element is already set hence i+1
	}
	//std::cout << "Position 4-vector constructor called" << std::endl;
}

four_vector::four_vector(const four_vector& v) : vector(4) {
	// no check required - two four_vector objects have the same length, 4
	for (int i{}; i < 4; i++) {
		(*this)[i] = v[i];
	}
	//std::cout << "Deep copy 4-vector constructor called" << std::endl;
}

four_vector::four_vector(four_vector&& v) noexcept : vector(4) {
	elements = v.elements;
	v.elements = new double[4];
	for (int i{}; i < 4; i++) {
		v[i] = 0;
	}
	//std::cout << "Move 4-vector constructor called" << std::endl;
}

double four_vector::dot(const vector& v) const {
	if (length != v.get_length()) {
		std::cerr << "Error: cannot perform inner product of vectors of unequal dimension" << std::endl;
		exit(1);
	}

	double dot_product{ (*this)[0] * v[0] };
	for (int i{1}; i <= 3; i++) {
		dot_product -= (*this)[i] * v[i]; // spatial components are subtracted
	}
	return dot_product;
}

four_vector& four_vector::operator=(const four_vector& v) {
	if (this == &v) {
		return *this;
	}
	for (int i{}; i < 4; i++) {
		(*this)[i] = v[i];
	}
	//std::cout << "Assignment 4-vector operator called" << std::endl;
	return *this;
}

four_vector& four_vector::operator=(four_vector&& v) noexcept {
	std::swap(elements, v.elements);
	//std::cout << "Move assignment 4-vector operator called" << std::endl;
	return *this;
}

four_vector four_vector::lorentz_boost(const vector& B) const {
	if (B.get_length() != 3) {
		std::cerr << "Error: beta vector is not 3-dimensional" << std::endl;
		exit(1);
	}

	double B_squared{ B.dot(B) };
	double gamma{ 1 / sqrt(1 - B_squared) };
	double ct{ (*this)[0] };
	vector r(3);
	for (int i{}; i < 3; i++) {
		r[i] = (*this)[i + 1];
	}

	// primed are transformed coordinates
	double ct_primed{ gamma * (ct - B.dot(r)) };
	vector r_primed{ r + B * ((gamma - 1) * r.dot(B) / B_squared - gamma * ct) };
	four_vector V(ct_primed, r_primed);
	return V;
}

std::ostream& operator<<(std::ostream& os, const four_vector& v) {
	os << "(ct, x, y, z) = ("; // style specific to four_vector objects
	for (int i{}; i < 4; i++) {
		os << v[i];
		if (i != 3) {
			os << ", ";
		}
	}
	os << ")";
	return os;
}