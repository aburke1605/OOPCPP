#include "Week 6.h""

matrix::matrix() {
	number_of_rows = 1;
	number_of_columns = 1;
	elements = new double[1];
	set_element(1, 0);
	std::cout << "Default constructor called" << std::endl;
}
matrix::matrix(const int& rows, const int& columns) {
	if (rows <= 0 || columns <= 0) {
		std::cout << "Error: matrix not valid" << std::endl;
		throw("Matrix size cannot be zero");
	}
	number_of_rows = rows;
	number_of_columns = columns;
	elements = new double[size()]; // elements is already a nullptr to an array of doubles
}
matrix::matrix(matrix& m) {
	// number of rows and columns always > 0 anyway from default and parametrised constructor
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = new double[size()];
	for (int i{ 1 }; i <= size(); i++) {
		set_element(i, m.elements[i]);
	}
}
matrix::matrix(matrix&& m) noexcept {
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = m.elements;
	m.number_of_rows = 1;
	m.number_of_columns = 1;
	m.elements = new double[1];
}
matrix::~matrix() {
	delete[] elements;
	std::cout << "Destructor called" << std::endl;
}
int matrix::size() const {
	return number_of_rows * number_of_columns;
}
void matrix::set_element(const int& location, const double& element) {
	if (location - 1 >= size() || location - 1 < 0) {
		std::cout << "Error: could not find element" << std::endl;
		throw("Index out of range");
	}
	elements[location - 1] = element;
}
matrix matrix::get_minor_matrix(const int& row, const int& column) const {
	if (row > number_of_rows || row < 0 || column>number_of_columns || column < 0) {
		std::cout << "Error: could not get minor matrix" << std::endl;
		throw("Row or column is out of range");
	}
	matrix m(number_of_rows - 1, number_of_columns - 1);
	int index{ 1 };
	for (int i{ 1 }; i <= number_of_rows; i++) {
		if (i == row) continue;
		for (int j{ 1 }; j <= number_of_columns; j++) {
			if (j == column) continue;
			else {
				m.set_element(index, elements[location(i, j) + 1]);
				index++;
			}
		}
	}
	return m; // calls the && constructor???
}
double matrix::get_determinant() const {
	double determinant{};
	if (number_of_rows == number_of_columns && size() >= 4) {
		//i.e. square
		if (size() == 4) {
			determinant = elements[0] * elements[3] - elements[1] * elements[2];
		}
		else {
			for (int j{ 1 }; j <= number_of_columns; j++) {
				std::cout << pow(-1, j - 1) * elements[location(1, j)] << std::endl;
				std::cout << get_minor_matrix(1, j) << std::endl;
				determinant += pow(-1, j - 1) * elements[location(1, j)] * (get_minor_matrix(1, j).get_determinant());
			}
		}
		std::cout << "determinant = " << determinant << std::endl;
		return determinant;
	}
	else {
		std::cout << "Error: could not calculate determinant" << std::endl;
		throw("Matrix is not square or 1 dimensional");
	}
}
matrix & matrix::operator=(const matrix& m) {
	//TODO: check same dimensions?
	if (&m == this) {
		return *this;
	}

	// assume this matrix is already constructed so delete and replace its data
	delete[] elements;
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = new double[size()];

	// number of rows and columns always > 0 anyway from default and parametrised constructor
	for (int i{ 1 }; i <= size(); i++) {
		set_element(i, m.get_element(i));
	}
	return *this;
}
matrix & matrix::operator=(matrix&& m) noexcept {
	std::swap(number_of_rows, m.number_of_rows);
	std::swap(number_of_columns, m.number_of_columns);
	std::swap(elements, m.elements);
	return *this;
}
matrix matrix::operator+(const matrix& m) {
	if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns) {
		std::cout << "Error: could not add matrices" << std::endl;
		throw("Matrices do not have the same dimensions");
	}
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			set_element(location(i, j), get_element(location(i, j)) + m.get_element(location(i, j)));
		}
	}
	return *this;
}
matrix matrix::operator-(const matrix& m) {
	if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns) {
		std::cout << "Error: could not subtract matrices" << std::endl;
		throw("Matrices do not have the same dimensions");
	}
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			set_element(location(i, j), get_element(location(i, j)) - m.get_element(location(i, j)));
		}
	}
	return *this;
}
matrix matrix::operator*(const matrix& m) {
	if (number_of_columns != m.number_of_rows) {
		std::cout << "Error: could not multiply matrices" << std::endl;
		throw("Check number of columns of matrix A = number of rows of martix B");
	}
	// store this
	double* stored_elements = new double[size()];
	for (int i{ 1 }; i <= size(); i++) {
		stored_elements[i - 1] = elements[i - 1];
	}

	// number of rows stays the same, columns changes
	number_of_columns = m.number_of_columns;
	elements = new double[size()];
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			double element{};
			for (int k{ 1 }; k <= m.number_of_rows; k++) {
				element += stored_elements[m.number_of_rows * (i - 1) + (k - 1)] * m.get_element(location(k, j) + 1);
			}
			set_element(location(i, j) + 1, element);
		}
	}
	return *this;
}
double matrix::operator()(const int& row, const int& column) {
	return elements[number_of_columns * (row - 1) + (column - 1)];
}
std::ostream& operator<<(std::ostream& os, const matrix& m) {
	for (int i{ 1 }; i <= m.number_of_rows; i++) {
		std::ostringstream row;
		for (int j{ 1 }; j <= m.number_of_columns; j++) {
			row << m.elements[m.location(i, j) + 1];
			if (j < m.number_of_columns) {
				row << ", ";
			}
			else {
				row << "\n";
			}
		}
		os << row.str();
		row.str("");
	}
	return os;
}
std::istream& operator>>(std::istream& is, matrix& m) {
	/*
	A function allowing the user to enter a desired matrix to the terminal.
	The input gets assigned to an object of type matrix after a checking
	for consistent number of columns per row.
	args: in-stream and a matrix to assign to
	returns: changes the matrix which the >> operator is called on to have the form
	         specified by user in their input
	*/

	// input form: 1,2,3.4,5,6.7,8,9 - columns separated by , and rows by .
	std::string input_matrix_string;
	std::getline(is, input_matrix_string);

	m.number_of_rows = 1; // at least...
	int start{}; // index to start substrings from
	int index{}; // index to finish substrings on
	std::vector<std::string> rows; // to store substrings separated by '.'
	int initial_number_of_commas{}; // to count number of commas (and hence columns) in substring (row) number 1

	// find '.'s and hence number of rows
	for (auto it = input_matrix_string.begin(); it != input_matrix_string.end(); it++) {
		std::string sub_string;
		if (*it == '.') {
			m.number_of_rows++;
			sub_string = input_matrix_string.substr(start, index - start);
			rows.push_back(sub_string);
			start = index + 1; // reassign start position

			// count number of columns in top row
			if (initial_number_of_commas == 0) {
				for (auto at = sub_string.begin(); at != sub_string.end(); at++) {
					if (*at == ',') {
						initial_number_of_commas++;
					}
				}
			}
		}
		else if (index == input_matrix_string.length() - 1) {
			sub_string = input_matrix_string.substr(start, input_matrix_string.length() - 1);
			rows.push_back(sub_string);

			// deal with row vectors
			if (initial_number_of_commas == 0) {
				for (auto at = sub_string.begin(); at != sub_string.end(); at++) {
					if (*at == ',') {
						initial_number_of_commas++;
					}
				}
			}
		}
		index++;
	}

	// TODO 1.1,2.1,2 passes when it shouldn't
	int number_of_commas{};
	for (auto it = rows.begin(); it != rows.end(); it++) {
		if (it == rows.begin()) {
			continue;
		}
		for (auto at = it->begin(); at != it->end(); at++) {
			if (*at == ',') {
				number_of_commas++;
			}
		}
		if (number_of_commas != initial_number_of_commas) {
			std::cout << "Error: couldn't recognise matrix" << std::endl;
			throw("Number of columns in each row do not match");
		}
		number_of_commas = 0;
	}
	m.number_of_columns = initial_number_of_commas + 1;
	m.elements = new double[m.size()];
	start = index = 0;
	int location{ 1 };
	for (auto it = input_matrix_string.begin(); it != input_matrix_string.end(); it++) {
		double element;
		if (*it == ',' || *it == '.') {
			element = atof(input_matrix_string.substr(start, index - start).c_str());
			m.set_element(location, element);
			location++;
			start = index + 1;
		}
		else if (index == input_matrix_string.length() - 1) {
			element = atof(input_matrix_string.substr(start, index + 1 - start).c_str());
			m.set_element(location, element);
		}
		index++;
	}
	return is;
}