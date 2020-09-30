#include <iostream>
#include <iomanip>
#include <string>

const double electron_volt{1.602e-19};
const double rydberg_constant{13.6}; // in electron volts

// function to calculate transition energy between two atomic electron states
double calculate_energy(int atomic_number, int quantum_number_1, int quantum_number_2) {
    return rydberg_constant * pow(atomic_number, 2) * (abs(1 / pow(quantum_number_1, 2) - 1 / pow(quantum_number_2, 2))); // in electron volts
}

// function to check if input is an integer which is greater than 0
bool check_positive_integer(std::string input) {
    for (std::string::const_iterator it{input.begin()}; it != input.end(); it++) {
        if (*it == '-') continue;
        if(!isdigit(*it)){ // check if any character of input is not a digit (eg decimal point or space)
            std::cout << "Enter an integer greater than 0... ";
            return false;
        }
    }
    if (atoi(input.c_str()) <= 0) { // make sure integer is greater than zero
        std::cout << "here" << std::endl;
        std::cout << "Enter an integer greater than 0... ";
        return false;
    }
    return true;
}

int main() {

    bool active{true}; // active used to decide whether to go again
    while(active){

        int atomic_number; int initial_quantum_number; int final_quantum_number;
        std::string input; // for keyboard inputs

        // assigning declared variables
        std::cout << "Enter the atomic number... ";
        std::getline(std::cin, input);
        while (!check_positive_integer(input)) { // check on input done here
            std::getline(std::cin, input);
        }
        atomic_number = atoi(input.c_str());

        std::cout << "Enter the initial quantum number... ";
        std::getline(std::cin, input);
        while (!check_positive_integer(input)) {
            std::getline(std::cin, input);
        }
        initial_quantum_number = atoi(input.c_str());

        std::cout << "Enter the final quantum number... ";
        std::getline(std::cin, input);
        while (!check_positive_integer(input)) {
            std::getline(std::cin, input);
        }
        final_quantum_number = atoi(input.c_str());


        // go to end of loop if quantum numbers are the same
        if (initial_quantum_number == final_quantum_number) {
            std::cout << "There is no transition!" << std::endl;
        }
        else {
            // check for absorbed or emitted photon
            std::string photon_type;
            if (initial_quantum_number < final_quantum_number) {
                photon_type = "absorbed";
            }
            else {
                photon_type = "emitted";
            }


            std::cout << "Would you like to use J or eV? (enter J/eV)... ";
            std::string energy_units; std::getline(std::cin, energy_units);
            while (energy_units != "J" && energy_units != "eV") {
                std::cout << "Please enter \"J\" or \"eV\"... ";
                std::getline(std::cin, energy_units);
            }


            double energy = calculate_energy(atomic_number, initial_quantum_number, final_quantum_number);
            if (energy_units == "J") energy *= electron_volt; // unit conversion if necassary
            std::cout << "The energy of the " << photon_type << " photon is " << std::setprecision(3) << energy << " " << energy_units << std::endl;
        }


        std::cout << "Would you like to go again? (y/n)... ";
        std::string decision; std::getline(std::cin, decision);
        while (decision != "y" && decision != "Y" && decision != "n" && decision != "N") {
            std::cout << "Please enter \"y\" or \"n\"... ";
            std::getline(std::cin, decision);
        }

        if (decision == "n" || decision == "N") {
            active = false; // don't go again, while loop breaks
        }

    }

    return 0;
}
