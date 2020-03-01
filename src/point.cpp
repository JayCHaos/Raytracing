#include "vector.h"

Point::Point(float x, float y, float z)
: X(x), Y(y), Z(z)
{}

Point::Point(const Point& p)
: X(p.X), Y(p.Y), Z(p.Z)
{}

bool Point::operator!= (Point p)
{
	if(X!=p.X&&Y!=p.Y&&Z!=p.Z)
		return true;
	else
		false;
}

Point& Point::operator=(const Point& p)
{
	if(this == &p) return *this;
	
	X = p.X;
	Y = p.Y;
	Z = p.Z;
	
	return *this;
}

Vector operator-(const Point& p1, const Point& p2)
{
	Vector v(
		p1.X - p2.X,
		p1.Y - p2.Y,
		p1.Z - p2.Z
    );
	
	return v;
}

ostream& operator<<(ostream& s,Point p)
{	
	s << "(" << p.X << "," << p.Y << "," << p.Z << ")";
	return s;
}



istream& operator>>(istream& s,Point& p)
{
	s >> p.X;
	s >> p.Y;
	s >> p.Z;
	return s;
}
