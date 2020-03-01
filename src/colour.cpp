#include "colour.h"

Colour::Colour(float red, float green, float blue)
{
	Red   = red;
	Green = green;
	Blue  = blue;
}

Colour::Colour(const Colour& colour)
{
	Red   = colour.Red;
	Green = colour.Green;
	Blue  = colour.Blue;
}

Colour& Colour::operator=(const Colour& colour)
{
	Red   = colour.Red;
	Green = colour.Green;
	Blue  = colour.Blue;
	
	return *this;
}

void Colour::reset(float red, float green, float blue)
{
	Red   = red;
	Green = green;
	Blue  = blue;
}

void Colour::check()
{
    Red   = std::max(std::min(1.0f, Red),   0.0f);
    Green = std::max(std::min(1.0f, Green), 0.0f);
    Blue  = std::max(std::min(1.0f, Blue),  0.0f);
}
 
Colour Colour::operator*(const Colour & rhs) const
{
	return Colour(this->Red   * rhs.Red,
                  this->Green * rhs.Green,
                  this->Blue  * rhs.Blue);
}

Colour Colour::operator+(const Colour & rhs) const
{
	return Colour(this->Red   + rhs.Red,
                  this->Green + rhs.Green,
                  this->Blue  + rhs.Blue);
}


Colour operator*(const Colour & lhs, float rhs)
{
	return Colour(lhs.Red   * rhs,
                  lhs.Green * rhs,
                  lhs.Blue  * rhs);
}

Colour operator*(float lhs, const Colour & rhs)
{
    return rhs * lhs;
}

ostream& operator<<(ostream& s,Colour colour)
{
	s << "(" << colour.Red << "R"    	
	  << "," << colour.Green << "G"		
	  << "," << colour.Blue << "B"		
	  << ")";
	
	return s;
}

istream& operator>>(istream& s,Colour& colour)
{
	s >> colour.Red >> colour.Green >> colour.Blue;
	
	return s;
}
