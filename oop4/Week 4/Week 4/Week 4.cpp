#include <iostream>
#include <vector>
#include <map>
#include <string>

class galaxy {
private:
	std::string hubble_type;
	double red_shift;
	double mass; // in units of M_sun
	double stellar_mass_fraction;
	std::vector<galaxy> satellites;
public:
	galaxy() :
		hubble_type{ "None" }, red_shift{}, mass{}, stellar_mass_fraction{} {}
	galaxy(std::string pHubble_type, double pRed_shift, double pMass, double pStellar_mass_fraction) :
		hubble_type{ pHubble_type }, red_shift{ pRed_shift }, mass{ pMass }, stellar_mass_fraction{ pStellar_mass_fraction } {}
	~galaxy() { std::cout << "destroying\n"; }

	void print_info();
	void change_type(std::string new_type);
	double stellar_mass() {
		return stellar_mass_fraction * mass;
	}
	void add_satellite();
	bool check_members();
};

int main() {

	// vector containing two initial galaxies for testing
	std::vector<galaxy> my_galaxies;
	my_galaxies.push_back(galaxy("Sa", 4.6, 10e10, 0.012));
	my_galaxies.push_back(galaxy("Sc", 3.2, 7e11, 0.033));


	// print initial galaxy info
	std::cout << "The current entries are:\n";
	int i{ 1 };
	for (auto it = my_galaxies.begin(); it < my_galaxies.end(); it++) {
		std::cout << i << ". ";
		i++;
		it->print_info();
		std::cout << "\n"; // for visual presentation
	}


	// ability to change type
	std::cout << "Would you like to edit a Hubble type? (enter 'y' if yes)... ";
	std::string decision; std::cin >> decision;
	while (decision == "y") {
		std::cout << "Which entry would you like to change (between 1 and " << my_galaxies.size() << ")?... ";
		int entry; std::cin >> entry;
		std::cout << "Enter the new Hubble type for entry " << entry << "... ";
		std::string newType; std::cin >> newType;
		my_galaxies[entry - 1].change_type(newType); // use the public member function to change the private hubble_type

		std::cout << "Would you like to edit another? (enter 'y' if yes)... ";
		std::cin.clear(); std::cin.ignore(10000, '\n'); std::cin >> decision;
	}


	// ability to add satellite galaxies
	std::cout << "Would you like to add satellite galaxies? (enter 'y' if yes)... ";
	std::cin >> decision;
	while (decision == "y") {
		std::cout << "Which galaxy (between 1 and " << my_galaxies.size() << ")?... ";
		int entry; std::cin >> entry;
		my_galaxies[entry - 1].add_satellite();

		std::cout << "Would you like to add satellites to another galaxy?\n";
		std::cin >> decision;
	}
	

	// print final galaxy info
	std::cout << "The final entries are:\n";
	i = 1 ;
	for (auto ptr = my_galaxies.begin(); ptr != my_galaxies.end(); ptr++) {
		std::cout << i << ". ";
		i++;
		ptr->print_info();
		std::cout << "\n\n";
	}

	return 0;
}

int depth{};
void galaxy::print_info() {
	/*
	A member function of the galaxy class which prints out all private member data of a galaxy, including it's satellites.
	The function is called recursively on the vector of satellite galaxies so that all of the satellite private member
	data is also printed.
	args: n/a
	returns: prints the hubble type, redshift, total mass, stellar mass fraction, stellar mass and number of satellites.
	*/

	std::cout << "Hubble type: " << hubble_type << ", red shift: " << red_shift << ", mass: " << mass
		      << " M_sun, stellar mass fraction: " << stellar_mass_fraction << ", stellar mass: " << stellar_mass()
		      << " M_sun, number of satellites: " << satellites.size();
	if (satellites.size() > 0) { // if there are satellites print their info too
		depth++;
		std::cout << "\n";
		for (int i{}; i <= depth; i++) {
			std::cout << "  ";
		}
		std::cout << "Satellites:\n";
		for (auto ptr = satellites.begin(); ptr < satellites.end(); ptr++) {
			//std::cout << "    "; //TODO: counter for depth to change the indent size?
			for (int i{}; i <= depth; i++) {
				std::cout << "  ";
			}
			ptr->print_info(); // recursive
			std::cout << "\n";
		}
		depth -= 1; //here?
	}
}

void galaxy::change_type(std::string new_hubble_type) {
	/*
	A member function of the galaxy class allowing the hubble type private parameter to be changed.
	args: the new hubble type in string form
	returns: changes the hubble type parameter to the input argument
	*/

	// dynamically create a temporary galaxy so that the check_member function
	// can be used to check the function argument for allowed values
	galaxy *temporary_galaxy = new galaxy(new_hubble_type, 0, 10e7, 0);
	if (temporary_galaxy->check_members()) {
		hubble_type = new_hubble_type;
		std::cout << "Changed entry to:\nHubble type: " << hubble_type << ", red shift: "
			<< red_shift << ", mass: " << mass << ", stellar mass fraction: " << stellar_mass_fraction
			<< ", number of satellites: " << satellites.size() << "\n";
	}
	else {
		std::cout << "Invalid hubble_type\n"; // error message
	}
	delete temporary_galaxy;
}

void galaxy::add_satellite() {
	/*
	A member function of the galaxy class allowing addition of a new satellite galaxy to
	vector of satellites which is a private member of the galaxy class.
	args: n/a
	returns: adds a new galaxy to satelltes
	*/

	bool again{ true }; // for multiple new satellites
	do {
		// user inputs
		std::cout << "Enter the satellite galaxy Hubble type... "; std::string satellite_hubble_type; std::cin >> satellite_hubble_type;
		std::cout << "Enter the red shift... "; double satellite_red_shift; std::cin >> satellite_red_shift;
		std::cout << "Enter the mass (in M_sun)... "; double satellite_mass; std::cin >> satellite_mass;
		std::cout << "Enter the stellar mass fraction... "; double satellite_stellar_mass_fraction; std::cin >> satellite_stellar_mass_fraction;
		
		galaxy satellite(satellite_hubble_type, satellite_red_shift, satellite_mass, satellite_stellar_mass_fraction);
		if (satellite.check_members()) {
			satellites.push_back(satellite);
		}

		std::string decision;
		std::cout << "Add any more satellites to this galaxy? {\n";
		print_info(); // display current satellites for clarification
		std::cout << "}?... ";
		std::cin >> decision;
		if (decision != "y") {
			again = false;
		}
	} while (again);

	// ability to add satellites to satellites
	std::cout << "Would you like to add satellite galaxies to any of these new satellite galaxies {\n";
	for (auto it = satellites.begin(); it != satellites.end(); it++) {
		it->print_info();
		std::cout << "\n";
	}
	std::cout << "}?... ";
	
	std::string decision; std::cin >> decision;
	while (decision == "y") {
		std::cout << "Which satellite galaxy (between 1 and " << satellites.size() << ")?... ";
		int entry; std::cin >> entry;
		satellites[entry - 1].add_satellite();
		
		std::cout << "Would you like to add satellites to another of these satellite galaxies {\n"; // any more new satellites?
		for (auto it = satellites.begin(); it != satellites.end(); it++) {
			it->print_info();
			std::cout << "\n";
		}
		std::cout << "}?... ";
		std::cin >> decision;
	}
}

bool galaxy::check_members() {
	/*
	A member function of the galaxy class which checks each private member parameter
	to be within specified values
	args: n/a
	returns: true or false dependent on parameters
	*/

	bool members_ok{ false };
	// vector of allowed hubble types to iterate over later
	std::vector<std::string> allowed_types{ "E0","E1","E2","E3","E4","E5","E6","E7","S0","Sa","Sb","Sc","SBa","SBb","SBc","Irr" };
	
	if (red_shift >= 0 && red_shift <= 10) {
		if (mass >= 10e7 && mass <= 10e12) {
			if (stellar_mass_fraction >= 0 && stellar_mass_fraction <= 0.05) {
				for (auto it = allowed_types.begin(); it != allowed_types.end(); it++) {
					if (hubble_type == *it) {
						members_ok = true;
						break;
					}
				}
			}
		}
	}
	if (members_ok == false) {
		// error message
		std::cout << "1 or more galaxy parameter is out of allowed range or hubble type...\n";
	}
	return members_ok;
}