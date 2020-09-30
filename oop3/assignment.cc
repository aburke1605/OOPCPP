int main() {
	vector<string> courses;
	bool another = true;
	while(another) {
		cout << "Enter a course code... ";
		int courseCode; cin >> courseCode;
		while(cin.fail()) {
			cin.clear(); cin.ignore(10000,'\n');
			cout << "Please enter an integer... ";
			cin >> courseCode;
		}
		cin.clear(); cin.ignore(10000,'\n'); //to mix cin and getline
		
		cout << "Enter a course title... ";
		string courseTitle; getline(cin,courseTitle);
		
		ostringstream stream;
		stream << "PHYS" << courseCode << " " << courseTitle;
		courses.push_back(stream.str());
		stream.str("");
		
		cout << "Enter \"y\" to add another course or any other key to finish... ";
		string decision; cin >> decision;
		if(decision != "y" && decision != "Y") {
			another = false;
		}
	}
	
	cout << "Your courses are:" << endl;
	for(int i{0}; i < courses.size(); i++) {
		cout << courses[i] << endl;
	}
		
	return 0;
}
