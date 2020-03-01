#ifndef _SPHERE_
#define _SPHERE_

#include "gobject.h"

class Sphere : public GObject{
	Point Centre;
	float Radius; 

public :
	Sphere() : GObject(), Centre(0.0,0.0,0.0), Radius(1.0) {};
	Sphere(Material,Point,float);
	
	Point& centre() {return Centre;}
	float& radius() {return Radius;}
	
	Vector normal(Point p) {return (p-Centre).normalised();}
	bool intersect(Ray ray, float& t);
	
	friend ostream& operator<<(ostream&,Sphere);  //writing
	friend istream& operator>>(istream&,Sphere&); //reading
	void print(ostream&);
	void read(istream&);
};
	
#endif