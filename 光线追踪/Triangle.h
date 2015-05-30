//Class_Triangle

#ifndef _CLASS_TRIANGLE
#define _CLASS_TRIANGLE 1

#include "Ray.h"
#include "Texture.h"

class Triangle
{
public:
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;

	Triangle(){}
	Triangle(const Vector3 _p0,const Vector3 _p1,const Vector3 _p2);
	Triangle(Triangle& _Triangle){*this = _Triangle;}

	bool Gethitpoint(const Ray& ray, hitrecord& record) const;
};
inline Triangle::Triangle(const Vector3 _p0,const Vector3 _p1,const Vector3 _p2)
{
	p0 = _p0;
	p1 = _p1;
	p2 = _p2;
};

#endif