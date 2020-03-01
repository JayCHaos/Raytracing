#ifndef _LITSCENE_
#define _LITSCENE_

//Same as a scene but with lights

#include "scene.h"
#include "light.h"

class LitScene : public Scene {
public:
	LitScene() : Scene(), Ambient(0.2f,0.2f,0.2f), index_ref(1.0f) {NLights = 0;}
	
	void setLighting    (int n)         { NLights=n; Lighting = new Light[n]; }

	void setFile        (char * file)   { fileName = file; }

	void setAmbient     (Colour colour) { Ambient = colour; }

	Light& lightAt      (int i)         { return Lighting[i]; }

	int& numberOfLights ()              { return NLights; }
	
	Colour evaluatePhongShading(GObject * object, Light * light, Vector pointToEye, Vector pointToLight, Vector normal);
	Colour colourOnObject(GObject*, Point, Point);
	bool intersect(GObject*, Ray, int, Colour&);
		
	friend ostream& operator<<(ostream&,LitScene);  //writing
	friend istream& operator>>(istream&,LitScene&); //reading

private:
	int     NLights;  // number of lights;
	Light * Lighting;
	Colour  Ambient;
	char *  fileName;
	float index_ref;
};
	
#endif
