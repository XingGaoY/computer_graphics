#include "Texture_Sphere.h"

Vector3 TextureSphereMarble::gettexture(const hitrecord& rec,Vector3& color) const
{
	Vector3 result;
	float temp = tex->scale*tex->perlin.Perlin2D(tex->freq*rec.u,tex->freq*rec.v);
	float t = 2* fabs(sin(tex->freq*rec.u+temp));

	if(t<1)result = tex->c1*t + (1-t)*tex->c2;
	else
	{
		t -= 1.0f;
		result = tex->c0*t + (1-t)*tex->c1;
	}
	result[1] *= 255;
	result[2] *= 255;
	result[0] *= 255;
	return result;
}

