#include "Plane.h"

bool Plane::Gethitpoint(const Ray& ray,float tmin, float tmax, hitrecord& record)const
{
	double d = - dot(position,outnorm);
	double t1 = dot(outnorm, ray.origin);
	double t2 = dot(outnorm, ray.direct);
	double distance = t1 + d;
	if(abs(distance)<0.00001)return false; 
	double t = -(d+t1)/t2;
	if(t>=tmin && t<=tmax)
	{
		record.hitpoint = ray.origin + t * ray.direct;
		record.norm = outnorm;
		record.t = t;
		return true;
	}
	else return false;
}

bool Plane::Shadowhit(const Ray& ray, float tmin, float tmax) const
{
	double d = - dot(position,outnorm);
	double t1 = dot(outnorm, ray.origin);
	double t2 = dot(outnorm, ray.direct);
	double distance = t1 + d;
	if(abs(distance)<0.00001)return false; 
	double t = -(d+t1)/t2;
	if(t>=tmin && t<=tmax)return true;
	else return false;
}

