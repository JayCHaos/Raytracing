#ifndef _VECTOR_
#define _VECTOR_

#include "point.h"

using namespace std;

class Vector {
	float X;
	float Y;
	float Z;
	
public:
	Vector() { X = Y = Z = 0.0; }
	Vector(float, float, float);

	Vector(const Vector&);                                  // copy constructor
	Vector& operator=(const Vector&);                       // copy assignment operator

	float   squarednorm();                                  // returns square of norm
	float   norm();                                         // returns norm
	void    normalise();                                    // normalises
	Vector& normalised();                                   // returns normalised vector

    bool operator==(Vector v);
	Vector operator+(const Vector & rhs) const;             // addition operator
    Vector operator-(const Vector & rhs) const;             // subtraction operator
    float  operator^(const Vector & rhs) const;             // dot product
    Vector operator*(const Vector & rhs) const;             // cross product
    Vector operator-(void) const;                           // unary minus

    friend Vector operator*(const Vector & lhs, float rhs); // vector * scalar
    friend Vector operator*(float lhs, const Vector & rhs); // vector * scalar

	float &x() { return X; }
	float &y() { return Y; }
	float &z() { return Z; }

	friend ostream& operator<<(ostream&, Vector);           // writing
	friend istream& operator>>(istream&, Vector&);          // reading
};

#endif
