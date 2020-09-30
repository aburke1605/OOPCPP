#include "Week6.h"
#include <vector>

matrix::matrix() {
	number_of_rows = 1;
	number_of_columns = 1;
	elements = new double[1];
	(*this)(1, 1) = 0;
	//std::cout << "Default constructor called" << std::endl;
}

matrix::matrix(const int& rows, const int& columns) {
	if (rows <= 0 || columns <= 0) {
		std::cerr << "Error: Matrix not valid\n       "
			"Matrix size cannot be zero" << std::endl;
		exit(1);
	}

	number_of_rows = rows;
	number_of_columns = columns;
	elements = new double[size()]; // elements is already a nullptr to an array of doubles
	//std::cout << "Parametrised constructor called" << std::endl;
}

matrix::matrix(matrix& m) {
	// number of rows and columns always > 0 anyway from default and parametrised constructor
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = new double[size()];
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			(*this)(i, j) = m(i, j);
		}
	}
	//std::cout << "Deep copy constructor called" << std::endl;
}

matrix::matrix(matrix&& m) noexcept {
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = m.elements;
	m.number_of_rows = 1;
	m.number_of_columns = 1;
	m.elements = new double[1];
	m(1, 1) = 0;
	//std::cout << "Move constructor called" << std::endl;
}

matrix::~matrix() {
	delete[] elements;
	//std::cout << "Destructor called" << std::endl;
}

int matrix::size() const {
	return number_of_rows * number_of_columns;
}

matrix matrix::get_minor_matrix(const int& row, const int& column) {
	/*
	A function which removes a choice of both row and column and returns the so-called minor matrix.
	Such a function is required to calculate the determinant of a square n x n matrix.
	args:      integer values row and column which are the row-column combination to remove from the matrix
	returns:   a matrix which is 1 row and 1 column smaller than the original
	*/

	if (row > number_of_rows || row < 0 || column>number_of_columns || column < 0) {
		std::cerr << "Error: Could not get minor matrix\n       "
			"Row or column is out of range" << std::endl;
		exit(1);
	}

	matrix m(number_of_rows - 1, number_of_columns - 1);
	int thisrow{ 1 };
	int thiscolumn{ 1 };
	for (int i{ 1 }; i <= number_of_rows; i++) {
		if (i == row) continue;
		for (int j{ 1 }; j <= number_of_columns; j++) {
			if (j == column) continue;
			else {
				m(thisrow, thiscolumn) = (*this)(i, j);
			}
			thiscolumn++;
		}
		thiscolumn = 1; // go back to leftmost column
		thisrow++;
	}
	return m;
}

double matrix::get_determinant() {
	/*
	A function which uses the get_minor_matrix to (recursively) calculate
	the determinant of any square matrix.
	args:      n/a
	returns:   the determinant of any n x n square matrix
	*/

	if (number_of_rows != number_of_columns || size() < 4) {
		std::cerr << "Error: Could not calculate determinant\n       "
			"Matrix is not square or is a scalar" << std::endl;
		exit(1);
	}

	// i.e. square
	double determinant{};
	if (size() == 4) {
		determinant = (*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1);
	}
	else { // recursively call get_determinant() on minor matrices along top row
		for (int j{ 1 }; j <= number_of_columns; j++) {
			determinant += pow(-1, j - 1) * (*this)(1, j) * (get_minor_matrix(1, j).get_determinant());
		}
	}
	return determinant;
}

matrix& matrix::operator=(const matrix& m) {
	// if the rvalue is exactly the lvalue, just return
	if (&m == this) {
		return *this;
	}

	// assume this matrix is already constructed so delete and replace its data
	delete[] elements;
	number_of_rows = m.number_of_rows;
	number_of_columns = m.number_of_columns;
	elements = new double[size()];

	// number of rows and columns always > 0 anyway from default and parametrised constructor
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			(*this)(i, j) = m(i, j);
		}
	}
	//std::cout << "Assignment operator called" << std::endl;
	return *this;
}

matrix& matrix::operator=(matrix&& m) noexcept {
	std::swap(number_of_rows, m.number_of_rows);
	std::swap(number_of_columns, m.number_of_columns);
	std::swap(elements, m.elements);
	//std::cout << "Move assignment operator called" << std::endl;
	return *this;
}

matrix matrix::operator+(const matrix& m) const {
	if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns) {
		std::cerr << "Error: Could not add matrices\n       "
			"Matrices do not have the same dimensions" << std::endl;
		exit(1);
	}

	matrix M(number_of_rows, number_of_columns);
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			M(i, j) = (*this)(i, j) + m(i, j);
		}
	}
	return M;
}

matrix matrix::operator-(const matrix& m) const {
	if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns) {
		std::cerr << "Error: Could not subtract matrices\n       "
			"Matrices do not have the same dimensions" << std::endl;
		exit(1);
	}

	matrix M(number_of_rows, number_of_columns);
	for (int i{ 1 }; i <= number_of_rows; i++) {
		for (int j{ 1 }; j <= number_of_columns; j++) {
			M(i, j) = (*this)(i, j) - m(i, j);
		}
	}
	return M;
}

matrix matrix::operator*(const matrix& m) const {
	if (number_of_columns != m.number_of_rows) {
		std::cerr << "Error: Could not multiply matrices\n       "
			"Check number of columns of matrix A = number of rows of martix B" << std::endl;
		exit(1);
	}

	matrix M(number_of_rows, m.number_of_columns); // takes properties from both matrices
	M.elements = new double[M.size()];
	for (int i{ 1 }; i <= M.number_of_rows; i++) {
		for (int j{ 1 }; j <= M.number_of_columns; j++) {
			double element{};
			// k loop to sum for each individual element
			for (int k{ 1 }; k <= number_of_columns; k++) {
				element += (*this)(i, k) * m(k, j);
			}
			M(i, j) = element;
		}
	}
	return M;
}

double& matrix::operator()(const int& row, const int& column) const {
	if (row < 1 || row > number_of_rows || column < 1 || column > number_of_columns) {
		std::cerr << "Error: Couldn't access matrix\n       "
			"Row or column index out of range of defined matrix" << std::endl;
		exit(1);
	}

	return elements[number_of_columns * (row - 1) + (column - 1)];
}

std::ostream& operator<<(std::ostream& os, matrix& m) {
	/*
	A function allowing output of a matrix object to the console window, for
	any shaped matrix.
	args:      outstream and matrix to insert into outstream
	returns:   a nicely formatted matrix view with columns separated by commas
	*/

	for (int i{ 1 }; i <= m.number_of_rows; i++) {
		std::ostringstream row;
		for (int j{ 1 }; j <= m.number_of_columns; j++) {
			row << m(i, j);
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
	args:      in-stream and a matrix to assign to
	returns:   changes the matrix which the >> operator is called on to have the form
			   specified by user in their input
	*/

	// input form: 1,2,3\4,5,6\7,8,9 - columns separated by ',' and rows by '\'
	std::string input_matrix_string;
	std::getline(is, input_matrix_string);

	m.number_of_rows = 1; // at least...
	int start{}; // index to start substrings from
	int index{}; // index to finish substrings on
	std::vector<std::string> rows; // to store substrings separated by '\'
	int initial_number_of_commas{}; // to count number of commas (and hence columns) in substring (row) number 1

	// find '\'s and hence number of rows
	for (auto it = input_matrix_string.begin(); it != input_matrix_string.end(); it++) {
		std::string sub_string;
		if (*it == '\\') {
			m.number_of_rows++;
			sub_string = input_matrix_string.substr(start, index - start);
			rows.push_back(sub_string);

			// count number of columns in TOP ROW for non-row-vector-matrices
			if (start == 0) {
				for (auto at = sub_string.begin(); at != sub_string.end(); at++) {
					if (*at == ',') {
						initial_number_of_commas++;
					}
				}
			}

			start = index + 1; // reassign start position for next row
		}
		else if (index == input_matrix_string.length() - 1) { // i.e. end of input string doesn't have '\'
			sub_string = input_matrix_string.substr(start, input_matrix_string.length());// -1);
			rows.push_back(sub_string);

			// deal with row vectors
			if (m.number_of_rows == 1) {
				for (auto at = sub_string.begin(); at != sub_string.end(); at++) {
					if (*at == ',') {
						initial_number_of_commas++;
					}
				}
			}
		}
		index++;
	}

	int number_of_commas{};
	for (auto it = rows.begin(); it != rows.end(); it++) {
		if (it == rows.begin()) {
			continue; // already counted initial_number_of_commas
		}
		for (auto at = it->begin(); at != it->end(); at++) {
			if (*at == ',') {
				number_of_commas++;
			}
		}
		if (number_of_commas != initial_number_of_commas) {
			std::cerr << "Error: Couldn't recognise matrix\n       "
				"Number of columns in each row do not match" << std::endl;
			exit(1);
		}
		number_of_commas = 0; // reset for the next row
	}

	m.number_of_columns = initial_number_of_commas + 1;
	m.elements = new double[m.size()];
	start = index = 0;
	int i{ 1 }, j{ 1 }; // to access elements of m
	for (auto it = input_matrix_string.begin(); it != input_matrix_string.end(); it++) {
		if (*it == ',') {
			m(i, j) = atof(input_matrix_string.substr(start, index - start).c_str());
			start = index + 1;
			j++;
		}
		else if (*it == '\\') {
			m(i, j) = atof(input_matrix_string.substr(start, index - start).c_str());
			start = index + 1;
			i++;
			j = 1; // back to leftmost column of matrix for next row
		}
		else if (index == input_matrix_string.length() - 1) {
			m(i, j) = atof(input_matrix_string.substr(start, index + 1 - start).c_str());
		}
		index++;
	}
	return is;
}

int main() {

	// demonstrate parametrised contruction and overloading of both () and <<
	matrix A(3, 3);
	matrix B(3, 3);
	for (int i{ 1 }; i <= 3; i++) {
		for (int j{ 1 }; j <= 3; j++) {
			A(i, j) = 3 * ((double)i - 1) + (double)j;
			B(i, j) = 3 * ((double)i - 1) + (double)j + 1;
		}
	}
	std::cout << "Matrix A:\n" << A << std::endl;
	std::cout << "Matrix B:\n" << B << std::endl;

	// demonstrate overloading of =
	std::cout << "Now doing B = A..." << std::endl;
	B = A;
	std::cout << "...which gives matrix A:\n" << A
		<< "and matrix B:\n" << B << std::endl;
	
	matrix C(3, 3);
	C(1, 1) = 1.0;
	C(1, 2) = 2.0;
	C(1, 3) = 5.0;
	C(2, 1) = 14.0;
	C(2, 2) = 5.0;
	C(2, 3) = 23.0;
	C(3, 1) = 57.0;
	C(3, 2) = 4.0;
	C(3, 3) = 7.0;
	std::cout << "Matrix C:\n" << C << std::endl;
	
	// demonstrate overloading of + and -
	matrix C_plus_A = C + A;
	std::cout << "C + A:\n" << C_plus_A << std::endl;

	matrix C_minus_B = C - B;
	std::cout << "C - B:\n" << C_minus_B << std::endl;

	matrix D(2, 3);
	for (int i{ 1 }; i <= 2; i++) {
		for (int j{ 1 }; j <= 3; j++) {
			D(i, j) = 2 * ((double)i - 1) + (double)j;
		}
	}
	std::cout << "Matrix D:\n" << D << std::endl;

	matrix E(3, 1);
	for (int i{ 1 }; i <= 3; i++) {
		for (int j{ 1 }; j <= 1; j++) {
			E(i, j) = 1 * ((double)i - 1) + (double)j + 6;
		}
	}
	std::cout << "Matrix E:\n" << E << std::endl;

	// demonstrate overloading of *
	matrix DE = D * E;
	std::cout << "D * E:\n" << DE << std::endl;

	// demonstrate move constructor
	std::cout << "Now doing D = std::move(E)..." << std::endl;
	D = std::move(E);
	std::cout << "...which gives matrix D:\n" << D
		<< "and matrix E:\n" << E << std::endl;

	matrix ED = E * D;
	std::cout << "E * D:\n" << ED << std::endl;


	// demonstrate minor matrix and determinant functions
	matrix minor_C = C.get_minor_matrix(3, 3);
	std::cout << "Removing row 3 and column 3 of matrix C:\n" << minor_C << std::endl;

	std::cout << "Determinant of C = " << C.get_determinant() << std::endl;

	// demonstrate overloading of >>
	matrix M;
	std::cout << "\nEnter a matrix with elements separated by \',\' and new rows by \'\\\'," << std::endl
		<< "e.g. the 2x2 identity matrix would be \'1,0\\0,1\'... " << std::endl;
	std::cin >> M;
	std::cout << "Your matrix is:" << std::endl << M << std::endl;
	if (M.size() == 9) { // only divisible by 1,3,9
		matrix MA = M * A;
		std::cout << "Your matrix times matrix A is:\n" << MA << std::endl;
	}

	// demonstrate determinant of a larger matrix
	matrix F(4, 4);
	F(1, 1) = 1;
	F(1, 2) = 3;
	F(1, 3) = 5;
	F(1, 4) = 9;
	F(2, 1) = 1;
	F(2, 2) = 3;
	F(2, 3) = 1;
	F(2, 4) = 7;
	F(3, 1) = 4;
	F(3, 2) = 3;
	F(3, 3) = 9;
	F(3, 4) = 7;
	F(4, 1) = 5;
	F(4, 2) = 2;
	F(4, 3) = 0;
	F(4, 4) = 9;
	std::cout << "Matrix F:\n" << F << std::endl;
	std::cout << "Determinant of F = " << F.get_determinant() << std::endl;
}