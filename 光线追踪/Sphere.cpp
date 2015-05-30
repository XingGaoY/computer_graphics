#include "Sphere.h"

bool Sphere::Gethitpoint(const Ray& ray,float tmin, float tmax, hitrecord& record) const		//return if intersect and set the hitpoint meanwhile
{
	int flag;
	double distance2, t2;
	Vector3 l = centre - ray.origin;
	double tp = dot( l, ray.direct);
	double sql = dot(l,l);
	double ra2 = radii * radii;
	if( abs(sql - ra2) < 0.0001) flag = 0;			//origin on the sphere
	else if( sql < ra2) flag = -1;		//origin inside the sphere
	else flag = 1;						//origin outside the sphere
	if( flag == 0)
	{

		tp *= 2;
		if( tp >= tmin && tp <= tmax )
		{
			record.hitpoint = ray.origin + ray.direct * tp;
			record.norm = Getnorm( record.hitpoint -centre );
			record.t = tp;
			return true;
		}
		else return false;
	}
	if(flag == 1 && tp < 0) return false;
	distance2 = sql - tp * tp;
	if(distance2 > ra2) return false;
	t2 = ra2 - distance2;
	t2 = sqrtf(t2);
	if(flag == 1)
	{
		tp -= t2;
		if( tp >= tmin && tp <= tmax)
		{
			record.hitpoint = ray.origin + ray.direct * tp;
			record.norm = Getnorm( record.hitpoint - centre );
			record.t = tp;
			return true;
		}
		else return false;
	}
	else if(flag ==-1)
	{
		tp += t2;
		if( tp >= tmin && tp <= tmax )
		{
			record.hitpoint = ray.origin + ray.direct * tp;
			record.norm = Getnorm( record.hitpoint - centre );
			record.t = tp;
			return true;
		}
		else return false;
	}

}

bool Sphere::Shadowhit(const Ray& ray, float tmin, float tmax) const
{
	int flag;
	double distance2, t2;
	Vector3 l = centre - ray.origin;
	double tp = dot( l, ray.direct);
	double sql = dot(l,l);
	double ra2 = radii * radii;
	if( abs(sql - ra2) < 0.0001) flag = 0;			//origin on the sphere
	else if( sql < ra2) flag = -1;		//origin inside the sphere
	else flag = 1;						//origin outside the sphere
	if( flag == 0)
	{
		tp *= 2;
		if( tp >= tmin && tp <= tmax )
		{
			return true;
		}
		else return false;
	}
	if(flag == 1 && tp < 0) return false;
	distance2 = sql - tp * tp;
	if(distance2 > ra2) return false;
	t2 = ra2 - distance2;
	t2 = sqrtf(t2);
	if(flag == 1)
	{
		tp -= t2;
		if( tp >= tmin && tp <= tmax)
		{
			return true;
		}
		else return false;
	}
	else if(flag ==-1)
	{
		tp += t2;
		if( tp >= tmin && tp <= tmax )
		{
			return true;
		}
		else return false;
	}
}

void Sphere::Setoutnorm(hitrecord& rec)
{
	Vector3 det = rec.hitpoint - centre;
	if(dot(det,rec.norm)<0) outnorm = -rec.norm;
	else outnorm = rec.norm;
}

