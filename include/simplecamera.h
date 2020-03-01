#ifndef _SIMPLECAMERA_
#define _SIMPLECAMERA_

#include "ray.h"

using namespace std;

class SimpleCamera{
	float Xmin, Xmax, Ymin, Ymax;	//view plane window
	float Width, Height, Wo2, Ho2;  //width and height of cell
	int Nx, Ny;			//number of subdivisions
	float Zcop;			//centre of projection along z-axis
	
public:
	SimpleCamera(int,int);
	
	void setVPWindow(float,float,float,float);
	void setResolution(int,int);
	
	int& xResolution() {return Nx;}
	int& yResolution() {return Ny;}
	float& xmin() {return Xmin;}
	float& xmax() {return Xmax;}
	float& ymin() {return Ymin;}
	float& ymax() {return Ymax;}
	float& zcop() {return Zcop;}
	
	Ray ray(int,int); //finds ray through pixel (i,j)
	
	friend ostream& operator<<(ostream&,SimpleCamera);  //writing
	friend istream& operator>>(istream&,SimpleCamera&); //reading
};

#endif
