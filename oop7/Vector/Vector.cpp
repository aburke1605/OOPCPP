#include "Vector.h"

vector::vector() {
	length = 1;
	elements = new double[1];
	(*this)[0] = 0;
	//std::cout << "Default vector constructor called" << std::endl;
}

vector::vector(const unsigned int& l) {
	if (l < 1) {
		std::cerr << "Error: vector length must be at least 1" << std::endl;
		exit(1);
	}

	length = l;
	elements = new double[length];
	for (int i{}; i < (int)length; i++) {
		(*this)[i] = 0;
	}
	//std::cout << "Parametrised vector constructor called" << std::endl;
}

vector::~vector() {
	delete[] elements;
	//std::cout << "Vector destructor called" << std::endl;
}

vector::vector(const vector& v) {
	length = v.length;
	elements = new double[length];
	for (int i{}; i < (int)length; i++) {
		(*this)[i] = v[i];
	}
	//std::cout << "Deep copy vector constructor called" << std::endl;
}

vector::vector(vector&& v) noexcept {
	length = v.length;
	elements = v.elements;
	v.length = 1;
	v.elements = new double[1];
	v[0] = 0;
	//std::cout << "Move vector constructor called" << std::endl;
}

int vector::get_length() const {
	return length;
}

double vector::dot(const vector& v) const {
	if (length != v.length) {
		std::cerr << "Error: cannot perform inner product of vectors of unequal dimension" << std::endl;
		exit(1);
	}

	double dot_product{};
	for (int i{}; i < (int)length; i++) {
		dot_product += (*this)[i] * v[i];
	}
	return dot_product;
}

vector& vector::operator=(const vector& v) {
	if (this == &v) {
		return *this;
	}
	delete[] elements;
	length = v.length;
	elements = new double[length];
	for (int i{}; i < (int)length; i++) {
		(*this)[i] = v[i];
	}
	//std::cout << "Assignment vector operator called" << std::endl;
	return *this;
}

vector& vector::operator=(vector&& v) noexcept {
	std::swap(length, v.length);
	std::swap(elements, v.elements);
	//std::cout << "Move assignment vector operator called" << std::endl;
	return *this;
}

vector vector::operator+(const vector& v) const {
	if (length != v.length) {
		std::cerr << "Error: cannot add vectors of unequal dimension" << std::endl;
		exit(1);
	}

	vector V(length);
	for (int i{}; i < (int)length; i++) {
		V[i] = (*this)[i] + v[i];
	}
	return V;
}

vector vector::operator*(const double& m) const {
	// must be vector * double in main, not double * vector
	vector V(length);
	for (int i{}; i < (int)length; i++) {
		V[i] = m * (*this)[i];
	}
	return V;
}

double& vector::operator[](const unsigned int& i) const {
	// accessor
	if (i < 0 || i >= length) {
		std::cerr << "Error: vector index out of range" << std::endl;
		exit(1);
	}

	return elements[i];
}

std::ostream& operator<<(std::ostream& os, const vector& v) {
	os << "(";
	for (int i{}; i < (int)v.length; i++) {
		os << v[i];
		if (i != v.length - 1) {
			os << ", ";
		}
	}
	os << ")";
	return os;
}