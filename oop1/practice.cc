void year() {
string decision{"y"};
while(decision == "y"){
cout << "Enter the year..." << endl;
int year; cin >> year;
while(cin.fail()) {
cout << "Input not an integer. Try again..." << endl;
cin.clear(); cin.ignore(); cin >> year;
}
cout << "The year is " << year << "." << endl;
cout << "Would you like to go again? (enter \"y\" for yes or any other key for no)..." << endl;
cin >> decision;
}
}

void enrgconv() {
const double e{1.602e-19};
cout << "Enter \"J\" to convert from eV to J or \"eV\" to convert from J to eV" << endl;
string decision; cin >> decision;
while(decision != "J" && decision != "eV"){
cout << "Input not recognised. Try again..." << endl;
cin.clear(); cin.ignore(); cin >> decision;
}
cout << "Enter a value to convert..." << endl;
double value; cin >> value;
while(cin.fail()){
cout << "Input not valid. Try again..." << endl;
cin.clear(); cin.ignore(); cin >> value;
}
if(decision =="J"){
cout << value << " eV is equal to "  << setprecision(3)  << value*e << " J." << endl;
}
else{
cout << setprecision(3)  << value/e << endl;
}
}
