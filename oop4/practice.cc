class particle {
	private:
		string type;
		double mass;
		double momentum;
		double energy;
	public:
		//overloading contructor
		particle():
			type{"Ghost"}, mass{0}, momentum{0}, energy{0} {}
		particle(string pType, double pMass, double pEnergy):
			type{pType}, mass{pMass}, energy{pEnergy}, momentum{sqrt(pow(pEnergy,2)-pow(pMass,2))} {}
		
		void gammaFactor();
		void mom();
		
		//destructor
		~particle() {
			cout << "Destroying " << type << " information" << endl;
		}
};


int main() {
	vector<particle> myParticles;
	myParticles.push_back(particle("electron",511e3,1e6));
	cout << "test1" << endl;
	myParticles.push_back(particle("proton",938e6,2e9));
	cout << "test2" << endl;
	myParticles.push_back(particle("neutron",940e6,2e9));
	cout << "test3" << endl;

	for(auto ptr = myParticles.begin(); ptr < myParticles.end(); ptr++) {
		ptr->gammaFactor();
		ptr->mom();
	}
	
		
	return 0;
}

//these defined afterwards otherwise the 'destroying' output prints lots of times
void particle::gammaFactor() {
        cout << "The " << type << " has a gamma factor of " << energy/mass << endl;
}

void particle::mom() {
        cout << "The " << type << " has momentum " << momentum << endl;
}
