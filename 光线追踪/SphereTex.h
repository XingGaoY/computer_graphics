//CLASS_TextureSphere

#ifndef _TEXSPHERE
#define _TEXSPHERE 1
#define M_PI 3.14159265358979323846

#include "Surface.h"
#include "Ray.h"

class TexSphere:public Surface
{
public:
	Vector3 centre;
	float radii;

	TexSphere():Surface(){};
	TexSphere(Vector3 centre1,float radii1,Vector3 DR,Vector3 SR,Vector3 AR,int RSP,Vector3 DT,Vector3 ST,int TSR,Vector3 IR,Vector3 IT,bool Trancparent,Texture* tex);
	TexSphere(const TexSphere& sphere){*this = sphere;}

	void Setoutnorm(hitrecord& rec);
	bool Gethitpoint(const Ray& ray,float tmin,float tmax,hitrecord& record)const;
	bool Shadowhit(const Ray& ray,float tmin,float tmax)const; 
};

inline TexSphere::TexSphere( Vector3 centre1, float radii1, Vector3 DR, Vector3 SRC, Vector3 AR,int RSP,
					  Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT, bool transparent,Texture* tex):Surface(transparent, DR, SRC, AR, RSP, DT, ST, TSP, IR, IT,tex)
{
	centre = centre1;
	radii = radii1;
}



#endif