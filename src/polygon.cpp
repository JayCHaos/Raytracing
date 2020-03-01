#include "polygon.h"

Polygon::Polygon(Material mat, int m) : GObject()
{
	material() = mat;
	
	N = 0; 
	Max = m; 
	P = new Point[m];
}

void Polygon::set(Point p)
{
	if(N<Max){
		P[N] = p;
		N++;
	}
}


void Polygon::planeEquation(void)
{
	Vector va = P[1]-P[0];
	Vector vb = P[2]-P[0];
	
	Nm = (va*vb).normalised(); 
	
	D = Nm^(Vector &)P[0];
}


void Polygon::planeEquation(Vector& normal, float &d)
{
	normal = Nm; 
	d = D;
}


float Polygon::evalPlaneEquation(Point p)
{
	/*ax+by+cz-d*/
	return (Nm^(Vector &)p) - D;
}

float Polygon::evalPlaneEquation(Vector v)
{
	/*ax+by+cz-d*/
	return (Nm^v) - D;
}

ostream& operator<<(ostream& s, Polygon poly)
{
	s << "\nPolygon:" << "\n";
	s << "Number of points: " << poly.N << "\n";
	for(int i = 0; i < poly.N; ++i){
		s << "(" << i << ")" << poly.P[i] << "\n";
	}
	s << "Normal: " << poly.Nm << "\n";
	 
	s << "Material: " << poly.material();
	  
	return s;
}


istream& operator>>(istream& s, Polygon& poly)
{
	int m;
	s >> m; //number of points in this polygon
	poly.setMaxPoints(m);
	
	for(int i = 0; i<m; ++i){
		Point p;
		s >> p;
		poly.set(p);
	}
	
	s >> poly.material();
	return s;
}

void Polygon::print(ostream &s)
{
	s << *this;
}

void Polygon::read(istream& s)
{
	s >> *this;
}

static float myabs(float x)
{
	if(x < 0.0) return -x;
	else return x;
}

static int maxCoeff(float a, float b, float c)
{
	float absA = myabs(a);
	float absB = myabs(b);
	float absC = myabs(c);
	int s = 0;
	float max = absA;
	
	if(absB > absA){
		s = 1;
		max = absB;
	}
	if(absC > max){
		s = 2;
	}
	
	return s;
}
	
static float xVal(Point p, int s)
{
	if(s==0) return p.y();
	else     return p.x();
}

static float yVal(Point p, int s)
{
	if(s==2) return p.y();
	else     return p.z();
}

static float dxVal(Point p0, Point p1, int s)
{
	return xVal(p1,s) - xVal(p0,s);
}

static float dyVal(Point p0, Point p1, int s)
{
	return yVal(p1,s) - yVal(p0,s);
}
	
bool Polygon::intersect(Ray ray, float& t)
{
	float denom = evalPlaneEquation(ray.direction()) + D;
	if(denom <0.000000001 && denom > -0.00000001) return false;
	
	t = -evalPlaneEquation(ray.origin())/denom;
	
	float x = ray.origin().x() + t*ray.direction().x();
	float y = ray.origin().y() + t*ray.direction().y();
	float z = ray.origin().z() + t*ray.direction().z();
	Point p(x,y,z);
	
	int test =0;

	float a = Nm.x(); float b = Nm.y(); float c = Nm.z();
	
	int s = maxCoeff(a,b,c);
	x = xVal(p,s);
	y = yVal(p,s);
	float dx,dy,x1,y1;
	
		for(int i = 1; i < N; ++i){
		dx = dxVal(P[i-1],P[i],s);
		dy = dyVal(P[i-1],P[i],s);
		x1 = xVal(P[i-1],s);
		y1 = yVal(P[i-1],s);
		
		if((x-x1)*dy - (y-y1)*dx > 0.0) {
			test--;
		}
		else{
			test++;
		}
	}

	dx = dxVal(P[N-1],P[0],s);
	dy = dyVal(P[N-1],P[0],s);
	x1 = xVal(P[N-1],s);
	y1 = yVal(P[N-1],s);
	if((x-x1)*dy - (y-y1)*dx > 0.0) {
		test--;
	}
	else{
		test++;
	}
	
	return ((test==-N)||(test==N));


	
}
	
