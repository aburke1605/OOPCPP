class vec {
	private:
		double x, y, z;
	public:
		vec() {
			x=y=z=0;
		}
		vec(double xin, double yin, double zin) {
			x=xin; y=yin; z=zin;
		}
		~vec(){
			cout << "Destroying vector with x=" << x << endl;
		}
	
	void show() {
		cout << "(" << x << "," << y << "," << z << ")" << endl;
	}
	double getx() const {return x;}
	//void setx(const double xin) {x=xin;}
	double gety() const {return y;}
	//void sety(const double yin) {y=yin;}
	double getz() const {return z;}
	//void setz(const double zin) {z=zin;}
	void addConst(const double n) /*const//test if error flagged*/ {
		//n += 1; //test if error is flagged (because of const)
		x += n;
		y += n;
		z += n;
	}
	double dotProduct(const vec &v) const {
		return x*v.getx() + y*v.gety() + z*v.getz();
	}
	vec add(const vec &v) const {
		/*vec temp;
		temp.setx(x+v.getx());
		temp.sety(y+v.gety());
		temp.setz(z+v.getz());
		return temp*/
		return vec(x+v.getx(),y+v.gety(),z+v.getz()); //parametrised constructor to avoid using setx etc
	}
	vec operator+(const vec &v) const { //adds functionality to the simple '+' operator so we don't have to use a.add(b) - it "overloads" the + operator
		return vec(x+v.getx(),y+v.gety(),z+v.getz());
	}
	vec operator+(const double m) const {
		return vec(x+m,y+m,z+m);
	} //can overload +,-,*,/,+=,[],......
	friend vec operator+(const double p, const vec &v);
	friend ostream &operator<<(ostream &os, const vec &v);
};
/*
double magnitude(const vec &v1, const vec &v2) {
	return sqrt(v1.getx()*v2.getx()+v1.gety()*v2.gety()+v1.getz()*v2.getz());
}
*/
vec operator+(const double p, const vec &v) { //to add a scalar from left ie 1+a, need to declare outside class and then make it a friend of the class inside the class
	return vec(p+v.x,p+v.y,p+v.z);
}

ostream &operator<<(ostream &os, const vec &v) {
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}

int main() {
	vec a;
	vec b(1,2,3);
	
	a.addConst(1.3);
	b.addConst(3);
	
	a.show();
	b.show();
	
	cout << a.dotProduct(b) << endl;
	
	vec c = a.add(b);
	c.show();
	
	vec d = 0.4 + a + b + 0.6; //uses all overloads of +
	cout << d << endl; //using overloading of <<
	
	return 0;
}
