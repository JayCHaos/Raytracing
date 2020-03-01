#include "light.h"

Light::Light(const Light& light)
{
	Directional = light.Directional;
	X = light.X;
	Y = light.Y;
	Z = light.Z;
	Intensity = light.Intensity;
}


Light& Light::operator=(const Light& light)
{
	if(this == &light) return *this;

	Directional = light.Directional;
	X = light.X;
	Y = light.Y;
	Z = light.Z;
	Intensity = light.Intensity;

	return *this;
}
	
	
ostream& operator<<(ostream& s, Light light)
{
	if(light.Directional) s << "Directional";
	else s << "Point";
	
	s << "Light: "  
	  << "Intensity: " << light.Intensity << " Geometry: "
	  << "[" << light.X << "," << light.Y << "," << light.Z << "]";
	  
	return s;
}


istream& operator>>(istream& s, Light& light)
{
	int type;
	
	s >> light.Intensity >> light.X >> light.Y >> light.Z >> type;
	
	light.Directional = (type == 1);
	
	return s;
}
