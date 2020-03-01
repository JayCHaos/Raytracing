#include "scene.h"
#include "sphere.h"
#include "cube.h"
#include "polygon.h"

void Scene::set(int n) 
{
	N = n; 
	ObjectArray = new GObject*[n];
}

ostream& operator<<(ostream& s, Scene scene)
{
	int i;
	
	for(i=0; i<scene.N; ++i) scene.ObjectArray[i]->print(s);
	
	return s;
}

istream& operator>>(istream& s, Scene& scene)
{
	int n;
	
	s>>n; 
	
	scene.set(n);
	
	
	for(int i=0; i<n; ++i){
		int objectcode;
		s >> objectcode;
	
		/*I don't see any other way around this*/
		switch(objectcode){
			case 0 : scene.ObjectArray[i] = new Sphere();
				 scene.ObjectArray[i]->read(s);
				 break;
				 
			case 1 : Polygon* poly = new Polygon();
				 poly->read(s);
				 poly->planeEquation();
				 scene.ObjectArray[i] = poly;
				 break;
			//case 2 : scene.ObjectArray[i]=new Cube(); //WHY ERROR
				// scene.ObjectArray[i]->read(s);
				// break;
				 
			//add additional cases
			
		}
	}
			
	return s;
}



bool Scene::intersect(Ray ray, Colour& colour)
{
	float tmin = 9999999999.9f;
	bool found = false;

	for (int i = 0; i < N; ++i){
		float t;
		if (ObjectArray[i]->intersect(ray, t)){
			if(t < tmin && t>0.0){
				tmin = t;
				found = true;
			}
		}
	}
	return found;
}
			
		

ostream& Scene::print(ostream& s)
{
	int i;
	
	for(i=0; i<N; ++i) ObjectArray[i]->print(s);
	
	return s;
}


istream& Scene::read(istream &s)
{
	int n;

	s>>n; 
	
	set(n);
	
	
	for(int i=0; i<n; ++i){
		int objectcode;
		s >> objectcode;
	
		switch(objectcode){
			case 0 : ObjectArray[i] = new Sphere();
				 ObjectArray[i]->read(s);
				 break;	 
				 
			case 1 : Polygon* poly = new Polygon();
				 poly->read(s);
				 poly->planeEquation();
				 ObjectArray[i] = poly;
				 break;

		//	case 2 : ObjectArray[i]=new Cube(); //WHY ERROR
			//	 ObjectArray[i]->read(s);
			//	 break;
			//add additional cases
			
		}
	}
			
	return s;
}




