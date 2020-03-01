#ifndef _Cube_
#define _Cube_

#include "gobject.h"

class Cube : public GObject{
	Point Centre;
	float Length; 

public :
	Cube() : GObject(), Centre(0.0,0.0,0.0), Length(1.0) {};
	Cube(Material,Point,float);
	
	Point& centre() {return Centre;}
	float& radius() {return Length;}
	
	Vector normal(Point p) {return check(p-Centre).normalised();}
	Vector check(Vector v) {
		if((fabs(v.x())==Length&&fabs(v.y())==Length)||(fabs(v.x())==Length&&fabs(v.z())==Length)||(fabs(v.y())==Length&&fabs(v.z())==Length)){return v;}
		if (fabs(v.x())==Length) {v.y()=0;v.z()=0;return v;}
		if (fabs(v.y())==Length) {v.x()=0;v.z()=0;return v;}
		if (fabs(v.z())==Length) {v.x()=0;v.y()=0;return v;}}
	bool intersect(Ray ray, float& t);
	
	friend ostream& operator<<(ostream&,Cube);  //writing
	friend istream& operator>>(istream&,Cube&); //reading
	void print(ostream&);
	void read(istream&);
};
	
#endif