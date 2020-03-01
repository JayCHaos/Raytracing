#ifndef _LIGHT_
#define _LIGHT_

#include "colour.h"
#include "point.h"
#include "vector.h"

// class for defining point or directional lights
class Light
{
public:
	Light()         : Directional(false), X(1.0f),  Y(1.0f),  Z(1.0f),  Intensity(1.0f, 1.0f, 1.0f) {}
	Light(Vector v) : Directional(true),  X(v.x()), Y(v.y()), Z(v.z()), Intensity(1.0f, 1.0f, 1.0f) {}
	Light(Point p)  : Directional(false), X(p.x()), Y(p.y()), Z(p.z()), Intensity(1.0f, 1.0f, 1.0f) {}
	
	Light(const Light&);            // initialisation from another light
	Light& operator=(const Light&); // assignment
	
	float & x()           { return X; }
	float & y()           { return Y; }
	float & z()           { return Z; }

	Colour& intensity()   { return Intensity; }

	Point   point()       { return Point(X, Y, Z); }

	Vector  direction()   { return Vector(X, Y, Z).normalised(); }

	bool &  directional() { return Directional; }
	
	friend ostream& operator<<(ostream &, Light);   // writing
	friend istream& operator>>(istream &, Light &); // reading

private:
	bool   Directional; // true if directional light
	float  X, Y, Z;     // point or direction
	Colour Intensity;   // intensity of the light

};

#endif
