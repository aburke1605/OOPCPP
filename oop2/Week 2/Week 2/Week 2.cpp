#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>

double calculate_mean(double* x, int N) {
	/*
	A function to return the mean of an array of numbers
	args: array x of doubles, integer N (should be the numbers of entries in x)
	returns: the mean of the first N entries in x
	*/
	double total{};
	for (int i{}; i < N; i++) {
		total += x[i];
	}
	return total / N;
}

double calculate_stdev(double* x, int N) {
	/*
	A fuction to return the standard deviation of an array of numbers
	args: array x of doubles, integer N (should be the numbers of entries in x)
	returns: the standard deviation of the first N entries in x
	*/
	double total{};
	for (int i{}; i < N; i++) {
		total += pow((x[i] - calculate_mean(x, N)), 2);
	}
	return sqrt(total / (N - 1));
}

int main() {

	// asks which file to open
	std::cout << "Enter file name... ";
	std::string file_name; std::cin >> file_name;
	std::ifstream my_file(file_name);
	int number_of_lines{};

	// check the file exists in the directory
	if (!my_file.good()) {
		std::cerr << "Error. File could not be opened or may not exist." << std::endl;
	}
	else {
		// loop over the lines in the file
		while (!my_file.eof()) {
			std::string line; my_file >> line;
			// count lines which are genuine numbers
			if (isdigit(line[0])) {
				number_of_lines++;
			}
		}

		// return to top of the file
		my_file.clear();
		my_file.seekg(0, my_file.beg);

		// dynamicaly allocate memory for an array to store the numbers in the file
		double* my_array = new double[number_of_lines];
		int index{}; // to track which array index to append to
		int errors{}; // to track the number of errored lines

		// loop over the lines in the file again
		while (!my_file.eof()) {
			double line; my_file >> line;
			if (my_file.fail()) { // if line is not a double
				errors++;
				my_file.clear(); my_file.ignore(10000, '\n'); // skips to next new line (assumes line shorter than 10000 characters)
			}
			else {
				my_array[index] = line;
				index++;
			}
		}
		my_file.close();
		std::cout << errors - 1 << " line(s) ignored." << std::endl;
		
		// print results
		std::cout.setf(std::ios::fixed, std::ios::floatfield); // same precision
		std::cout << "The mean electron charge is " << std::setprecision(3) << calculate_mean(my_array, number_of_lines) << "e-19 C" << std::endl
			<< "The standard deviation is " << calculate_stdev(my_array, number_of_lines) << "e-19 C" << std::endl
			<< "The standard error is " << calculate_stdev(my_array, number_of_lines) / sqrt(number_of_lines) << "e-19 C" << std::endl;
		
		delete[] my_array;
	}

	return 0;
}
