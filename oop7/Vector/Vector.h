#ifndef _VEC_INCL_GUARD
#define _VEC_INCL_GUARD

#include <iostream>

class vector {
protected:
	unsigned int length;
	double* elements;
public:
	vector();
	vector(const unsigned int& l);
	~vector();
	vector(const vector& v);
	vector(vector&& v) noexcept;
	int get_length() const;
	double dot(const vector& v) const;
	vector& operator=(const vector& v);
	vector& operator=(vector&& v) noexcept;
	vector operator+(const vector& v) const;
	vector operator*(const double& m) const;
	double& operator[](const unsigned int& i) const;
	friend std::ostream& operator<<(std::ostream& os, const vector& v);
};

#endif