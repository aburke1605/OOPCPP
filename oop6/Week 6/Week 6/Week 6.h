//TODO: overload [] instead of get_element and set_element
//TODO: location: change to include +1
//TODO: work out how throw works

#include <iostream>
#include <sstream>
#include <vector>

class matrix {
private:
	int number_of_rows{}; //m
	int number_of_columns{}; //n
	double* elements{ nullptr }; // pointer to matrix data
public:
	matrix();
	matrix(const int& rows, const int& columns);
	matrix(matrix& m); // deep copy constructor
	matrix(matrix&& m) noexcept; // move constructor
	~matrix();
	int size() const;
	void set_element(const int& location, const double& element);
	matrix get_minor_matrix(const int& row, const int& column) const;
	double get_determinant() const;

	matrix& operator=(const matrix& m);
	matrix& operator=(matrix&& m) noexcept; // move assignment operator
	matrix operator+(const matrix& m);
	matrix operator-(const matrix& m);
	matrix operator*(const matrix& m);
	double operator()(const int& row, const int& column);

	friend std::ostream& operator<<(std::ostream& os, const matrix& m);
	friend std::istream& operator>>(std::istream& is, matrix& m);
};