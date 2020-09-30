#include<iostream>
#include<math.h>
#include<string>

class complex_number {
private:
	double Re, Im;
public:
	complex_number() {
		Re = Im = 0;
	}
	complex_number(double x, double y) {
		Re = x; Im = y;
	}
	~complex_number() {
		std::cout << "Destructor called" << std::endl;
	}

	double real() const;
	double imaginary() const;
	double modulus() const;
	double argument() const;
	complex_number conjugate() const;
	void change_real(const double real);
	void change_imaginary(const double imaginary);

	complex_number operator+(const complex_number& c) const;
	complex_number operator-(const complex_number& c) const;
	complex_number operator*(const complex_number& c) const;
	complex_number operator/(const complex_number& c) const;
	friend std::ostream& operator<<(std::ostream& os, const complex_number& c);
	friend std::istream& operator>>(std::istream& is, complex_number& c);
};

std::ostream& operator<<(std::ostream& os, const complex_number& c) {
	/*
	Overloads << to allow direct printing of a complex number
	args: an output stream and a complex number object
	returns: a nicely formatted visualisation of the complex number object
	*/

	if (c.Im >= 0) {
		os << c.Re << " + " << c.Im << "i";
	}
	else {
		os << c.Re << " - " << -c.Im << "i";
	}
	return os;
}
std::istream& operator>>(std::istream& is, complex_number& c) {
	/*
	Overloads >> to allow direct reading in of a complex number
	args: an input stream and a complex number object (a default object suffices)
	returns: the complex number object with correctly assigned real and imaginary parts
	*/

	std::string complex_number_string;
	std::getline(is, complex_number_string);

	// start i from 1 incase the real part is negative
	// (ie the first charactre will be '-')
	for (int i{1}; i < (int)complex_number_string.size(); i++) {
		if (complex_number_string[i] == '+' || complex_number_string[i] == '-') {
			c.change_real(atof(complex_number_string.substr(0, i).c_str()));
			if (complex_number_string[i] == '-') {
				c.change_imaginary(-atof(complex_number_string.substr(i + 1, complex_number_string.length() - 1 - (i + 1)).c_str()));
			}
			else {
				c.change_imaginary(atof(complex_number_string.substr(i + 1, complex_number_string.length() - 1 - (i + 1)).c_str()));
			}
		}
	}
	return is;
}

int main() {

	// two example complex numbers
	complex_number a(3, 4);
	complex_number b(1, -2);

	// demonstrate overloading of the << operator
	std::cout << "a = " << a << ",\n"
	          << "b = " << b << ".\n\n";

	// demonstrate member fuctions
	std::cout << "Re(a) = " << a.real() << ",\n"
		      << "Im(a) = " << a.imaginary() << ",\n"
		      << "mod(a) = " << a.modulus() << ",\n"
			  << "arg(a) = " << a.argument()*180/(atan(1)*4) << " deg,\n"
			  << "conj(a) = " << a.conjugate() << ".\n\n";

	// demonstrate overloading of the +,-,*,/ operators
	std::cout << "a + b = " << a + b << ",\n"
		      << "a - b = " << a - b << ",\n"
		      << "a * b = " << a * b << ",\n"
		      << "a / b = " << a / b << ".\n\n";
	
	// demonstrate overloading of the >> operator
	std::cout << "Enter a complex number of the form \"a +/- bi\" ... ";
	complex_number c; std::cin >> c;
	std::cout << "Your complex number is " << c << "\n";

	return 0;
}

double complex_number::real() const {
	return Re;
}
double complex_number::imaginary() const {
	return Im;
}
double complex_number::modulus() const {
	return sqrt(Re * Re + Im * Im);
}
double complex_number::argument() const {
	return atan(Im / Re); // radians
}
complex_number complex_number::conjugate() const {
	return complex_number(Re, -Im);
}
void complex_number::change_real(const double real) {
	Re = real;
}
void complex_number::change_imaginary(const double imaginary) {
	Im = imaginary;
}
complex_number complex_number::operator+(const complex_number& c) const {
	return complex_number(Re + c.Re, Im + c.Im);
}
complex_number complex_number::operator-(const complex_number& c) const {
	return complex_number(Re - c.Re, Im - c.Im);
}
complex_number complex_number::operator*(const complex_number& c) const {
	return complex_number(Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re);
}
complex_number complex_number::operator/(const complex_number& c) const {
	double modsq{ c.Re * c.Re + c.Im * c.Im };
	return complex_number((Re * c.Re + Im * c.Im) / modsq, (Im * c.Re - Re * c.Im) / modsq);
}