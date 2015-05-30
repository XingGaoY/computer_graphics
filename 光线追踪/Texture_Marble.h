//Class_Marble

#ifndef _MARBLE
#define _MARBLE 1

#include "PerlinNoise.h"

class TexMarble:public Texture
{
public:
	float freq;
	PerlinNoise perlin;
	float scale;
	Vector3 c0,c1,c2;

	Vector3 gettexture(const hitrecord& rec,Vector3& color) const;

	TexMarble(){};
	TexMarble(PerlinNoise _perlin,float _scale,Vector3 _c0,Vector3 _c1,Vector3 _c2,float _freq)
	{
		freq = _freq;
		c0 = _c0;c1=_c1;c2=_c2;
		perlin = _perlin;scale = _scale;
	}
};

#endif