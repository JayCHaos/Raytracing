#include "litscene.h"

Colour LitScene::evaluatePhongShading(GObject * object, Light * light, Vector pointToEye, Vector pointToLight, Vector normal)
{
    Vector h           = (pointToEye + pointToLight).normalised(); // halfway vector between eye and light, (V + L) / |L + V|
	/* h' 
	float  index       = object->material().refraction()/index_ref;
	Vector h		   = ((pointToEye-(index*pointToLight))*(1/(index-1))).normalised();*/

	float  nh          = normal ^ h;
    Colour kd          = object->material().diffuse();
    Colour ks          = object->material().specular();
    Colour intensity   = light->intensity();
    Colour diffuse     = kd * (normal ^ pointToLight);
    Colour specular    = ks * std::pow(nh, object->material().shininess());
    Colour addedColour = diffuse + specular;
    Colour reflection  = intensity * addedColour;

    return reflection;
}

Colour LitScene::colourOnObject(GObject * object, Point p, Point eye)
{
	Vector n = object->normal(p);
    Ray    shadowray;
	Colour colour;

	Colour ka     = object->material().ambient();
	       colour = ka * Ambient;

	for (int i = 0; i < NLights; ++i) {
        bool shadow = false;
		Light light = lightAt(i);

		Vector pointToLight;
		if (light.directional()) {
            pointToLight = -light.direction().normalised();
		} else { 
            pointToLight = (light.point() - p).normalised();
		}

		shadowray.origin() = p;
		shadowray.direction() = pointToLight;
		float dist = 99999999.9;
		if (!light.directional()){
            dist = (light.point() - p).squarednorm();
		}
		for (int i = 0; i < numObjects(); ++i)
		{
			float t;
			if ((at(i) != object) && at(i)->intersect(shadowray, t)){
				if ((shadowray.pointAt(t)-p).squarednorm()<dist && (t > 0.0f)){		
					shadow=true;break;}
			} 
		}

		float nl = n ^ pointToLight;
		if (nl > 0.0 && !shadow) {
            colour = colour + evaluatePhongShading(object, &light, (eye - p).normalised(), pointToLight, n);
		}
	}

	colour.check();
	
	return colour;
}
	
bool LitScene::intersect(GObject* me, Ray ray, int depth, Colour& colour /* out variable */)
{
    if (depth == 0)
        return false;
	else
		depth--;

	double   tmin   = 9999999999.9; // lowest t-value found
	bool     found  = false;        // has an object been intersected?
	GObject* object = NULL;         // which object has been hit?
    Ray      reflected;
	Ray		 refracted;

	// for each object
	for (int i = 0; i < numObjects(); ++i)
    {
		float t;
		if ((at(i) != me) && at(i)->intersect(ray, t))
        {
			// intersection found
			if ((t < tmin) && (t > 0.0f))
            {
				object = at(i);
				tmin   = t;
				found  = true;
			}
		} 
	}

	if (found) {
		// find the intersection point
		Point p = ray.pointAt((float)tmin);
		
		colour = colourOnObject(object, p, ray.origin());

        Colour refl_col;
		Colour refr_col;
		Vector e;
		Vector t;
		e = -(ray.direction()).normalised(); 
		Vector n = object->normal(p);
		Vector r = -e+(2*(n^e))*n;
		float index, cos;
		cos = (e^n)/(e.norm()*n.norm());
		//index = object->material().refraction()/index_ref;
		index = index_ref/object->material().refraction();
		
		reflected.direction()=r;
		reflected.origin()=p;
		if(intersect(object,reflected,depth,refl_col)){
			Colour kr = object->material().specular();
			colour=colour+kr*refl_col;}

		if((1+(pow(index,2))*(pow(cos,2)-1))>=0){
			t = (-index)*(e) + n*(index*cos-sqrt(1+(pow(index,2))*(pow(cos,2)-1)));
			refracted.direction()=t;
			refracted.origin()=p;
			if(intersect(object,refracted,depth,refr_col)){
				Colour kt = object->material().specular();
				colour=colour+kt*refr_col;}}

        colour.check();  
		return true;
	}
	else 
	{
		return false;
	}
}

ostream& operator<<(ostream& s, LitScene scene)
{
	scene.print(s);
	
	s << "\n\nLighting:\n";
	
	int i;
	s << "Ambient: " << scene.Ambient <<"\n";
	for (i=0; i < scene.numberOfLights(); ++i)
    {
        s << "Light: " << i << " " << scene.lightAt(i) << "\n";
    }
	
	return s;
}
	
istream& operator>>(istream& s, LitScene& scene)
{
	scene.read(s);
	
	s >> scene.Ambient;
	
	int n; s >> n;
	
	if(n==0) return s;
	
	scene.setLighting(n);
	
	Light light;

	for(int i = 0; i < n; ++i) {
		s >> light;
		scene.lightAt(i) = light;
	}

	return s;
}

