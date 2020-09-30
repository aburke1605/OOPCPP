class cplxn {
	private:
		double Re, Im;
	public:
		cplxn() {Re=Im=0;}
		cplxn(double x, double y) {Re=x; Im=y;}
		~cplxn(){cout << "Destroying cplxn with Re=" << Re << endl;}
		
		double real() const; //real
		double imag() const; //imaginary
		double mod() const; //modulus
		double arg() const; //argument
		cplxn conj() const; //conmplex conjugate
		cplxn operator+(const cplxn &c) const;
		cplxn operator-(const cplxn &c) const;
		cplxn operator*(const cplxn &c) const;
		cplxn operator/(const cplxn &c) const;
		friend ostream &operator<<(ostream &os, const cplxn &c);
		friend istream &operator>>(istream &is, const cplxn &c);
};

ostream &operator<<(ostream &os, const cplxn &c) {
	if(c.Im >= 0) {
		os << c.Re << " + " << c.Im << "i";
	} else {
		os << c.Re << " - " << -c.Im << "i";
	}
	return os;
}

istream &operator>>(istream &is, const cplxn &c) {
	string str;
	bool neg = false;
	getline(is,str);
	for(int i{0}; i < str.length(); i++) {
		if(str[i] == '+' || str[i] == '-') {
			c.Re = atof(str.substr(0,i));
			if(str[i] == '-') {neg = true;}
		} else if(str[i] == 'i') {
				c.Im = atof(str.substr(i+1,str.length()-i-1));
		}
	}
	return is;
}

int main() {
	cplxn a(3,4);
	cplxn b(1,-2);
	cout << b << endl;
	return 0;
}

double cplxn::real() const {
	return Re;
}
double cplxn::imag() const {
	return Im;
}
double cplxn::mod() const {
	return sqrt(Re*Re + Im*Im);
}
double cplxn::arg() const {
	return atan(Im/Re);
}
cplxn cplxn::conj() const{
	return cplxn(Re, -Im);
}
cplxn cplxn::operator+(const cplxn &c) const {
	return cplxn(Re+c.Re, Im+c.Im);
}
cplxn cplxn::operator-(const cplxn &c) const {
	return cplxn(Re-c.Re, Im-c.Im);
}
cplxn cplxn::operator*(const cplxn &c) const {
	return cplxn(Re*c.Re-Im*c.Im, Re*c.Im + Im*c.Re);
}
cplxn cplxn::operator/(const cplxn &c) const {
	double modsq{c.Re*c.Re+c.Im*c.Im};
	return cplxn((Re*c.Re+Im*c.Im)/modsq, (Im*c.Re-Re*c.Im)/modsq);
}
