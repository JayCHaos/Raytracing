#ifndef _MATERIAL_
#define _MATERIAL_

#include "colour.h"

class Material{
	Colour Ambient;
	Colour Diffuse;
	Colour Specular;
	float Shininess;
	float Refra_index;
public :
	Material() : Ambient(0.0,0.0,0.0), Diffuse(0.0,0.0,0.0), 
		     Specular(0.0,0.0,0.0), Shininess(0.0), Refra_index(0.0) {};
	Material(const Material&);	  		//initialisation 
	Material& operator=(const Material&); 		//assignment
	
	
	Colour& ambient() {return Ambient;}
	Colour& diffuse() {return Diffuse;}
	Colour& specular() {return Specular;}
	float& shininess() {return Shininess;}
	float& refraction() {return Refra_index;}
	
	friend ostream& operator<<(ostream&,Material);  //writing
	friend istream& operator>>(istream&,Material&); //reading
};
	
#endif