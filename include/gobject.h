#ifndef _GOBJECT_
#define _GOBJECT_

#include "material.h"
#include "ray.h"

using namespace std;

//an abstract class
class GObject{
	Material Mat;	//the material reflectance properties of the object
public:
	GObject() : Mat() {};
	
	Material& material() {return Mat;}	
	
	virtual bool intersect(Ray ray, float& t) = 0;
	virtual Vector normal(Point) = 0;
	
	virtual void print(ostream&) = 0;
	
	//for each different kind of object need one of these
	virtual void read(istream&) = 0;
};

#endif