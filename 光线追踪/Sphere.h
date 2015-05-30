//Class_Sphere.h

#ifndef _SPHERE_H
#define _SPHERE_H 1

#include "Surface.h"

class Sphere:public Surface
{
public:

	Vector3 centre;
	float radii;

	Sphere():Surface(){}
	Sphere( Vector3 centre1, float radii1, Vector3 DR, Vector3 SRC, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT, bool transparent,Texture* tex);
	Sphere(const Sphere& sphere);

	void Setoutnorm(hitrecord& rec);
	bool Gethitpoint(const Ray& ray, float tmin, float tmax, hitrecord& record) const;
	bool Shadowhit(const Ray& ray, float tmin, float tmax) const;
};

inline Sphere::Sphere(const Sphere& sp)
{
	*this = sp;
}


inline Sphere::Sphere( Vector3 centre1, float radii1, Vector3 DR, Vector3 SRC, Vector3 AR,int RSP,
					  Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT, bool transparent,Texture* tex):Surface(transparent, DR, SRC, AR, RSP, DT, ST, TSP, IR, IT,tex)
{
	centre = centre1;
	radii = radii1;
}


#endif