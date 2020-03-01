#ifndef _POINT_
#define _POINT_

#include "headers.h"

using namespace std;
class Vector;

class Point{
public:
	Point() : X(0.0f), Y(0.0f), Z(0.0f) {}
	Point(float x, float y, float z);

	Point(const Point &);                 // initialisation from another point
	Point& operator=(const Point &);      // assignment
	
	float &         x() { return X; }
	float &         y() { return Y; }
	float &         z() { return Z; }

	bool operator!= (Point p);
	friend Vector   operator-   (const Point &, const Point &); // Vector = Point-Point

	friend ostream & operator<< (ostream &, Point);          // writing
	friend istream & operator>> (istream &, Point &);         // reading

private:
	float X;
	float Y;
	float Z;

};

Vector operator-(const Point &, const Point &);

#endif
