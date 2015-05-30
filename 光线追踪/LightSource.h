//Class_LightSource.h

#ifndef _LIGHTSOURCE
#define _LIGHTSOURCE 1

#include "Vector.h"
#include <opencv2\highgui\highgui.hpp>

class LightSource
{
public:
	Vector3 origin;
	Vector3 colour;

	LightSource(){};
	LightSource(Vector3 _origin, Vector3 _colour);

};

inline LightSource::LightSource(Vector3 _origin, Vector3 _colour)
{
	origin = _origin;
	colour = _colour;
}

#endif