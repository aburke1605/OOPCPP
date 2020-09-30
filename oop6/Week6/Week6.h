#ifndef _INCL_GUARD
#define _INCL_GUARD

#include <iostream>
#include <sstream>

class matrix {
private:
	int number_of_rows{};
	int number_of_columns{};
	double* elements{ nullptr }; // array of pointers to matrix data
public:
	matrix();
	matrix(const int& rows, const int& columns);
	matrix(matrix& m); // deep copy constructor
	matrix(matrix&& m) noexcept; // move constructor
	~matrix();

	int size() const;
	matrix get_minor_matrix(const int& row, const int& column);
	double get_determinant();

	matrix& operator=(const matrix& m); // deep copy assignment operator
	matrix& operator=(matrix&& m) noexcept; // move assignment operator
	matrix operator+(const matrix& m) const;
	matrix operator-(const matrix& m) const;
	matrix operator*(const matrix& m) const;
	double& operator()(const int& row, const int& column) const;

	friend std::ostream& operator<<(std::ostream& os, matrix& m);
	friend std::istream& operator>>(std::istream& is, matrix& m);
};

#endif