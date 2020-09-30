double doubleChecker(double x) {
        while(cin.fail() || x < 0) {
                cout << "Enter a number greater than 0... ";
                cin.clear(); cin.ignore(10000,'\n');
                cin >> x;
        }
	return x;
}

class galaxy {
	private:
		string type;
		double z, mass, f;
		vector<galaxy> satellites;
	public:
		galaxy():
			type{"None"}, z{0}, mass{0}, f{0} {}
		galaxy(string pType, double pZ, double pMass, double pF):
			type{pType}, z{pZ}, mass{pMass}, f{pF} {}
		
		void printInfo();
		double stellarMass() {
			return f*mass;
		}
		void changeType(string str);
		void addSatellite();
		
		~galaxy() {
			cout << "Destroying " << type << " data" << endl;
		}
};

int main() {
	vector<galaxy> myGalaxies;
	myGalaxies.push_back(galaxy("Sa",4.6,5e33,0.012));
	myGalaxies.push_back(galaxy("Sc",3.2,7e32,0.033));
	
	cout << "The current entries are:" << endl;
	int i{1};
	for(auto ptr = myGalaxies.begin(); ptr < myGalaxies.end(); ptr++) {
		cout << i << ". ";
		i++;
		ptr->printInfo();
	}
	
	cout << "Would you like to edit a Hubble type? (enter 'y' if yes)... ";
	string decision; cin >> decision;
	while(decision == "y") {
		cout << "Which entry would you like to change?... ";
		int entry; cin >> entry;
		while(cin.fail() || entry < 1 || entry > i-1) {
			cin.clear(); cin.ignore(10000,'\n');
			cout << "Enter an integer between 1 and " << i-1 << "... ";
			cin >> entry;
		}
		cout << "Enter the new Hubble type for entry " << entry << "... ";
		string newType; cin >> newType;
		myGalaxies[entry-1].changeType(newType);

		cout << "Would you like to edit another? (enter 'y' if yes)... ";
		cin.clear(); cin.ignore(10000,'\n'); cin >> decision;
	}
	
	cout << "Would you like to add a satellite galaxy? (enter 'y' if yes)... ";
	string decision2; cin >> decision2;
	while(decision2 == "y") {
		cout << "Which entry would you like to add a satellite to?... ";
		int entry2; cin >> entry2;
		while(cin.fail() || entry2 < 1 || entry2 > i-1) {
			cin.clear(); cin.ignore(10000,'\n');
			cout << "Enter an integer between 1 and " << i-1 << "... ";
			cin >> entry2;
		}
		myGalaxies[entry2-1].addSatellite();
		cout << "would you like to add another? (enter 'y' if yes)... ";
		cin.clear(); cin.ignore(10000,'\n'); cin >> decision2;
	}
	
	cout << "The final entries are:" << endl;
	int ii{1};
	for(auto ptr = myGalaxies.begin(); ptr < myGalaxies.end(); ptr++) {
		cout << ii << ". ";
		ii++;
		ptr->printInfo();
        }

	return 0;
}

void galaxy::printInfo() {
	cout << "Hubble type: " << type << ", red shift: " << z << ", mass: " << mass << ", stellar mass fraction: " << f << ", stellar mass: " << stellarMass() << ", number of satellites: " << satellites.size() << endl;
	if(satellites.size() > 0) {
		cout << "    Satellites:" << endl;
		for(auto ptr = satellites.begin(); ptr < satellites.end(); ptr++) {
			cout << "    ";
			ptr->printInfo();
		}
	}
}


void galaxy::changeType(string str) {
	type = str;
	cout << "Changed entry to:\nHubble type: " << type << ", red shift: " << z << ", mass: " << mass << ", stellar mass fraction: " << f << ", number of satellites: " << satellites.size() << endl;
}

void galaxy::addSatellite() {
	cout << "Enter the Hubble type... "; string Ht; cin >> Ht;
	cout << "Enter the red shift... "; double rs; cin >> rs; rs=doubleChecker(rs);
	cout << "Enter the mass... "; double m; cin >> m; m=doubleChecker(m);
	cout << "Enter the stellar mass fraction... "; double smf; cin >> smf; smf=doubleChecker(smf);
	
	satellites.push_back(galaxy(Ht,rs,m,smf));
}
