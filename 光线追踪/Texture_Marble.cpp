#include "Texture_Marble.h"

Vector3 TexMarble::gettexture(const hitrecord& rec,Vector3& color) const
{
	Vector3 result;
	float temp = scale*perlin.Perlin2D(freq*rec.hitpoint.x(),freq*rec.hitpoint.y());
	float t = 2* fabs(sin(freq*rec.hitpoint.x()+temp));

	if(t<1)result = c1*t + (1-t)*c2;
	else
	{
		t -= 1.0f;
		result = c0*t + (1-t)*c1;
	}
	result[1] *= 255;
	result[2] *= 255;
	result[0] *= 255;
	return result;
}

