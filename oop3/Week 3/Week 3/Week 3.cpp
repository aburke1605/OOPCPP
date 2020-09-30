#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// global storage vector so that courses is accesible by all functions
// vector of pairs to allow sorting for int of std::string
std::vector<std::pair<int, std::string>> courses;

bool sort_by_code(std::pair<int, std::string>& course_1, std::pair<int, std::string>& course_2) {
	/*
	A function to numerically order two integers
	args: two std::pair's
	returns: the numerical order of the args
	*/
	return course_1.first < course_2.first;
}

bool sort_by_title(std::pair<int, std::string>& course_1, std::pair<int, std::string>& course_2) {
	/*
	A function to alphabetically order two strings
	args: two std::pair's
	returns: the alphabetical order of the args
	*/
	return course_1.second < course_2.second;
}

void print_courses() {
	/*
	A function to display the current existing courses
	args: n/a
	returns: list of course numbers and names in their current order
	*/
	std::cout << std::endl << "Your courses are:" << std::endl;
	for (std::vector<std::pair<int, std::string>>::const_iterator it{ courses.begin() }; it != courses.end(); it++) {
		std::ostringstream stream;
		stream << "PHYS " << it->first << " " << it->second; // create the string stream which will be printed
		std::cout << stream.str() << std::endl;
		stream.str("");
	}
}

void print_courses(int year) {
	/*
	Overloaded function to display the current existing courses in a given academic year
	args: the year of interest
	returns: list of course numbers and names for a year in their current order
	*/
	std::cout << std::endl << "The year " << year << " courses are:" << std::endl;
	for (std::vector<std::pair<int, std::string>>::const_iterator it{ courses.begin() }; it != courses.end(); it++) {
		if (year == it->first / 10000) { // dividing int by 10000 returns first digit of a 5 digit long int
			std::ostringstream stream;
			stream << "PHYS " << it->first << " " << it->second;
			std::cout << stream.str() << std::endl;
			stream.str("");
		}
	}

}

int main() {

	bool add_another_course{ true };
	while (add_another_course) {

		// get course code and title
		std::string course_code;
		std::string course_code_and_title;

		bool convertable;
		do {
			convertable = true;
			std::cout << "Enter the course code and title... ";
			getline(std::cin, course_code_and_title);
			if (course_code_and_title.length() > 6) { // ie it at least contains a 5 digit code, a space, and another character (course title)
				course_code = course_code_and_title.substr(0, 5); // extract the first 5 characters (course code)

				// check that the first 5 characters are digits
				for (std::string::const_iterator it{ course_code.begin() }; it != course_code.end(); it++) {
					if (!isdigit(*it) || course_code_and_title[5] != ' ') {
						std::cout << "ERROR: Ensure the 5-digit course code is entered first followed by a space." << std::endl;
						convertable = false;
						break;
					}
				}
			}
			else {
				std::cout << "ERROR: Ensure you enter a 5-digit course code, followed by a space, followed by the course title." << std::endl;
				convertable = false;
			}
		} while (!convertable);


		// put the course code and title together in a pair and push onto vector
		std::pair<int, std::string>* temporary_pair = new std::pair<int, std::string>;
		temporary_pair->first = atoi(course_code.c_str());
		temporary_pair->second = course_code_and_title.substr(6, course_code_and_title.length() - 6);
		courses.push_back(*temporary_pair);
		delete temporary_pair; // free up allocated memory


		// option to add another course or view current courses first
		std::cout << "Enter \"y\" to add another course, \"v\" to view the current list of courses or any other key to finish... ";
		std::string decision; std::cin >> decision;
		if (decision == "y" || decision == "Y" || decision == "v" || decision == "V") {
			if (decision == "v" || decision == "V") { // wishes to view the current courses
				print_courses();
				std::cout << "Would you now like to add another course?... ";
				std::cin >> decision;
				if (decision != "y" && decision != "Y") add_another_course = false;
			}
		}
		else add_another_course = false;
		std::cin.clear(); std::cin.ignore(10000, '\n');
	}


	// possibility to sort here
	std::cout << std::endl << "All courses added. If you would like to sort, enter \"c\" to sort by course code or \"t\" to sort by course title, otherwise enter any other key... ";
	std::string sort_option; std::cin >> sort_option;
	if (sort_option == "c" || sort_option == "C") std::sort(courses.begin(), courses.end(), sort_by_code);
	else if (sort_option == "t" || sort_option == "T") std::sort(courses.begin(), courses.end(), sort_by_title);


	// display final list with sorting option implemented
	std::cout << std::endl << "Would you like to display courses for a single year (\"y\")?... ";
	std::string decision; std::cin >> decision;
	if (decision == "y" || decision == "Y") {
		std::cout << "Enter the year (1 to 4)... ";
		std::string year_decision; std::cin >> year_decision;
		if (atoi(year_decision.c_str()) >= 1 && atoi(year_decision.c_str()) <= 4) {
			print_courses(atoi(year_decision.c_str())); // print only that year
		}
	}
	else {
		print_courses(); // print all
	}

	return 0;
}