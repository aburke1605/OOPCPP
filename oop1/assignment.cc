const double Er{13.6};
const double e{1.602e-19};

double enrg(int z, int m, int n) {
return Er*pow(z,2)*(abs(1/pow(m,2) - 1/pow(n,2))); //eV
}

int main() {

bool active{1};
while(active) {

int an; int iqn; int fqn;

cout << "Enter the atomic number..." << endl;
cin >> an;
while(cin.fail() || an <= 0) {
cout << "Enter an integer greater than 0..." << endl;
cin.clear(); cin.ignore(); cin >> an;
}

cout << "Enter the initial quantum number..." << endl;
cin >> iqn;
while(cin.fail() || iqn <= 0) {
cout << "Enter an integer greater than 0..." << endl;
cin.clear(); cin.ignore(); cin >> iqn;
}

cout << "Enter the final quantum number..." << endl;
cin >> fqn;
while(cin.fail() || fqn <= 0) {
cout << "Enter an integer greater than 0..." << endl;
cin.clear(); cin.ignore(); cin >> fqn;
}

string type;
if(iqn < fqn) {
type = "absorbed";
} else if(iqn > fqn) {
type = "emitted";
}

cout << "Would you like to use J or eV? (enter j/e)..." << endl;
string energy; cin >> energy;
while(energy != "j" && energy != "e") {
cout << "Please enter \"j\" or \"e\"..." << endl;
cin >> energy;
}

if(iqn == fqn) {
cout << "There is no transition!" << endl;
} else {
if(energy == "j"){
cout<< "The energy of the " << type << " photon is " << setprecision(3) << e*enrg(an,iqn,fqn) << " eV." << endl;
} else {
cout<< "The energy of the " << type << " photon is " << setprecision(3) << enrg(an,iqn,fqn) << " eV." << endl;
}
}

cout << "Would you like to go again? (y/n)..." << endl;
string decision; cin >> decision;
while(decision != "y" && decision != "n"){
cout << "Please enter \"y\" or \"n\"..." << endl;
cin >> decision;
}
if(decision == "n"){
active = 0;
}

}

return 0;
}
