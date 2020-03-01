#include "vector.h"

Vector::Vector(float x, float y, float z)
: X(x), Y(y), Z(z)
{}

Vector::Vector(const Vector& p)
: X(p.X), Y(p.Y), Z(p.Z)
{}

bool Vector::operator==(Vector v)
{
	if(X==v.X&&Y==v.Y&&Z==v.Z)
		return true;
	else
		return false;
}

Vector& Vector::operator=(const Vector& p)
{
	
	if(this == &p) return *this;
	
	X = p.X;
	Y = p.Y;
	Z = p.Z;
	
	return *this;
}

float Vector::squarednorm()
{
	return X*X + Y*Y + Z*Z;
}


float Vector::norm()
{
	return (float)sqrt(squarednorm());
}

void Vector::normalise()
{
	float d = this->norm();
	
	X /= d;
	Y /= d;
	Z /= d;
}

Vector& Vector::normalised()
{
	float d = this->norm();
	
	X /= d;
	Y /= d;
	Z /= d;
	
	return *this;
}
	

ostream& operator<<(ostream& s,Vector p)
{	
	s << "[" << p.X << "," << p.Y << "," << p.Z << "]";
	return s;
}


istream& operator>>(istream& s,Vector& p)
{
	s >> p.X;
	s >> p.Y;
	s >> p.Z;
	return s;
}

Vector Vector::operator+(const Vector & rhs) const
{
	Vector v;
	
	v.X = this->X+rhs.X;
	v.Y = this->Y+rhs.Y;
	v.Z = this->Z+rhs.Z;
	
	return v;
}

Vector Vector::operator-(const Vector & rhs) const
{
	Vector v;
	
	v.X = this->X-rhs.X;
	v.Y = this->Y-rhs.Y;
	v.Z = this->Z-rhs.Z;
	
	return v;
}

float Vector::operator^(const Vector & rhs) const
{
    return this->X * rhs.X
         + this->Y * rhs.Y
         + this->Z * rhs.Z;
}

Vector Vector::operator*(const Vector & rhs) const
{
	Vector v;
	
    v.X = this->Y * rhs.Z - this->Z * rhs.Y;
    v.Y = this->Z * rhs.X - this->X * rhs.Z;
    v.Z = this->X * rhs.Y - this->Y * rhs.X;
	
	return v;
}
	
Vector Vector::operator-(void) const
{
    Vector v;

    v.X = -this->X;
    v.Y = -this->Y;
    v.Z = -this->Z;

    return v;
}
	
Vector operator*(const Vector & lhs, float rhs)
{
	Vector v;
	
	v.X = lhs.X*rhs;
	v.Y = lhs.Y*rhs;
	v.Z = lhs.Z*rhs;
	
	return v;
}

Vector operator*(float lhs, const Vector & rhs)
{
    return rhs * lhs;
}
