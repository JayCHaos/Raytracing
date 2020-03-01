#include "material.h"

Material::Material(const Material& mat)
{
	Ambient = mat.Ambient;
	Diffuse = mat.Diffuse;
	Specular = mat.Specular;
	Shininess = mat.Shininess;
	Refra_index = mat.Refra_index;
}

 
Material& Material::operator=(const Material& mat)
{
	Ambient = mat.Ambient;
	Diffuse = mat.Diffuse;
	Specular = mat.Specular;
	Shininess = mat.Shininess;
	Refra_index = mat.Refra_index;
	
	return *this;
}


ostream& operator<<(ostream& s,Material mat)
{
	
	s << "Ambient: " << mat.Ambient << " " <<
	     "Diffuse: " << mat.Diffuse << " " <<
	     "Specular: " << mat.Specular << " " <<
	     "Shininess: " << mat.Shininess << " "<<
		 "Refraction:" << mat.Refra_index;
	    
	return s;
}


istream& operator>>(istream& s,Material& mat)
{
	s >> mat.Ambient >> mat.Diffuse >> mat.Specular >> mat.Shininess >> mat.Refra_index;
	
	return s;
}
