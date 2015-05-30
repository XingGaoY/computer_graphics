//Class_Surface.h

#ifndef _CLASS_SURFACE
#define _CLASS_SURFACE 1

#include <opencv2\highgui\highgui.hpp>
#include "Texture.h"
#include "Ray.h"


class Surface
{
public:
	Texture* texture;

	Vector3 outnorm;		//defined to show the outside of the surface

	Vector3 AmbientReflect;

	Vector3 DiffuseReflect;
	Vector3 SpecularReflect;
	int ReflectSmoothPara;

	bool Transparent;
	float inrefraction;
	float outrefraction;

	Vector3 DiffuseTransmit;
	Vector3 SpecularTransmit;
	int TransmitSmoothPara;

	Vector3 IndirectReflect;
	Vector3 indirectTransmit;

	Surface(){};
	Surface(bool transparent,Vector3 DR, Vector3 SR, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT,Texture* tex);
	Surface(const Surface& s){*this = s;}

	void SetRefraction(float inrefra, float outrefra);
	Vector3 Getreflcolor(const Vector3 &raycolor,const hitrecord& record,int LN,int HN);

	//virtual void Setoutnorm(hitrecord& rec)=0;
	//virtual bool Gethitpoint(const Ray& ray,float tmin, float tmax, hitrecord& record) const=0;
	//virtual bool Shadowhit (const Ray& ray, float tmin, float tmax) const=0;
};
#endif