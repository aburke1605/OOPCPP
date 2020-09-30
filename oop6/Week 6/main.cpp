#include "Week 6/Week 6.cpp"

int main() {
	matrix a(3, 3);
	matrix b(3, 3);
	for (int i{ 1 }; i <= a.size(); i++) {
		a.set_element(i, (double)i);
		b.set_element(i, (double)i + 1);
	}
	b = a;
	std::cout << a[4] << std::endl;

	//std::cout << "det(a) = " << a.get_determinant() << std::endl;

	matrix minor_a = a.get_minor_matrix(3, 3);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << minor_a << std::endl;
	std::cout << "a*b:\n" << a * b << std::endl;

	matrix A(2, 3);
	for (int i{ 1 }; i <= A.size(); i++) {
		A.set_element(i, (double)i);
	}
	matrix B(3, 1);
	for (int i{ 1 }; i <= B.size(); i++) {
		B.set_element(i, (double)i + 6);
	}
	std::cout << "A * B:\n" << A * B << std::endl;


	matrix m(3, 3);
	m.set_element(1, 1.0);
	m.set_element(2, 2.0);
	m.set_element(3, 5.0);
	m.set_element(4, 14.0);
	m.set_element(5, 5.0);
	m.set_element(6, 23.0);
	m.set_element(7, 57.0);
	m.set_element(8, 4.0);
	m.set_element(9, 7.0);
	std::cout << m << std::endl;
	std::cout << "det(m) = " << m.get_determinant() << std::endl;

	matrix M;
	std::cout << "Enter a matrix with elements separated by \',\' and new rows by \'.\'," << std::endl
		<< "e.g. the 2x2 identity matrix would be \'1,0.0,1\'... " << std::endl;
	std::cin >> M;
	std::cout << "Your matrix is:" << std::endl << M << std::endl;

	matrix f;
	std::cout << "f = " << f << std::endl;
}
