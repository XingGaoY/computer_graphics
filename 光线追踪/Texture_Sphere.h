//Class_Texture_Sphere
//defines various of texture to be mapped to a Shpere

#ifndef TEXTURESPHERE
#define TEXTURESPHERE 1

#include "Texture_Marble.h"

class TextureSphereMarble:public Texture
{
public:
	TexMarble* tex;

	Vector3 gettexture(const hitrecord& rec,Vector3& color) const;

	TextureSphereMarble(PerlinNoise _perlin,float _scale,Vector3 _c0,Vector3 _c1,Vector3 _c2,float _freq)
	{
		tex = new TexMarble;
		tex->freq = _freq;
		tex->c0 = _c0;tex->c1=_c1;tex->c2=_c2;
		tex->perlin = _perlin;tex->scale = _scale;
	}
	TextureSphereMarble(TexMarble* _tex){tex = _tex;}
};

#endif