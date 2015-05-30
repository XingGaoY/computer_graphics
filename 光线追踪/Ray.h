//Class_Ray.h

#ifndef _RAY_H
#define _RAY_H 1

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Vector.h"

class Ray
{
public:
	Vector3 origin;
	Vector3 colour;
	Vector3 direct;
	float refraction;

	Ray(){};
	Ray(const Vector3 colour1, const Vector3 direct1, Vector3 o);
	Ray(const Ray& ray){*this = ray; };

	void Setref(float ref){refraction = ref;}
};

inline Ray::Ray(const Vector3 colour1, const Vector3 direct1, Vector3 o)
{
	origin = o;
	colour = colour1;
	direct = direct1 * (1 / dot(direct1, direct1));
}



#endif