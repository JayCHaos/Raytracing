#include "ray.h"

ostream& operator<<(ostream& s,Ray ray)
{
	s << "{" << ray.Origin << "," << ray.Direction << "}";
	return s;
}

Point Ray::pointAt(float t)
{
	return Point(Origin.x() + t*Direction.x(),
	             Origin.y() + t*Direction.y(),
	             Origin.z() + t*Direction.z());
}

