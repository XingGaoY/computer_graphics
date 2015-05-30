//Class_Plane

#ifndef _PLANE
#define _PLANE 1

#include "Surface.h"
#include "Ray.h"

class Plane:public Surface
{
public:
	Vector3 position;

	Plane(){};
	Plane(Vector3 _pos, Vector3 _norm, Vector3 DR, Vector3 SRC, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT, bool transparent,Texture* tex);
	Plane(Plane& _pl){*this = _pl;}
 
	void Setoutnorm(hitrecord& rec){}
	bool Shadowhit(const Ray& ray, float tmin, float tmax) const;
	bool Gethitpoint(const Ray& ray, float tmin, float tmax, hitrecord& record) const;
};

inline Plane::Plane(Vector3 _pos, Vector3 _norm, Vector3 DR, Vector3 SRC, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, 
					int TSP, Vector3 IR, Vector3 IT, bool transparent,Texture* tex):Surface(transparent, DR, SRC, AR, RSP, DT, ST, TSP, IR, IT,tex)
{
	position = _pos;
	outnorm = _norm;
}

#endif