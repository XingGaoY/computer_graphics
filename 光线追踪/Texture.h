//Class_Texture

#ifndef _TEXTURE
#define _TEXTURE 1

#include "Vector.h"

struct hitrecord
{
	float u,v;
	Vector3 norm;
	Vector3 hitpoint;
	float t;
	bool hit;
};

class Texture
{
public:
	virtual Vector3 gettexture(const hitrecord& rec,Vector3& color) const = 0;
};

#endif