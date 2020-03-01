#include "cube.h"

Cube::Cube(Material mat, Point centre, float radius) : GObject()
{
	material() = mat;
	
	Centre = centre;
	Length = radius;
}

ostream& operator<<(ostream& s, Cube sphere)
{
	s << "\nCube:" << "\n"
	  << "Centre: " << sphere.Centre << " "
	  << "Length: " << sphere.Length << "\n"
	  << "Material: " << sphere.material();
	  
	return s;
}


istream& operator>>(istream& s,Cube& cube)
{
	s >> cube.Centre >> cube.Length >> cube.material();
	return s;
}

void Cube::print(ostream &s)
{
	s << *this;
}

void Cube::read(istream& s)
{
	s >> *this;
}

bool Cube::intersect(Ray ray, float& t)
{
	float a,b,c,r;
	float dx,dy,dz;
	float A,B,C,d;
	float x1,y1,z1,x2,y2,z2;
	float t1,t2;
	
	a = Centre.x();
	b = Centre.y();
	c = Centre.z();
	r = Length;
	
	x1 = ray.origin().x();
	y1 = ray.origin().y();
	z1 = ray.origin().z();

	x2 = x1 + ray.direction().x();
	y2 = y1 + ray.direction().y();
	z2 = z1 + ray.direction().z();
	
	x1 = x1-a; y1 = y1-b; z1 = z1-c;
	x2 = x2-a; y2 = y2-b; z2 = z2-c;
	
	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;
	
	A = dx*dx + dy*dy + dz*dz;
	B = x1*dx + y1*dy + z1*dz;
	C = x1*x1 + y1*y1 + z1*z1- r*r;

	if((d=(B*B-A*C)) < 0.0) return false;

	d = (float)sqrt((double)d);
	t1 = (-B-d)/A;
	t2 = (-B+d)/A;

	t = t1;

	return true;
}

	

