//Class_constcolor
//this class define the texture that without texture, constant color that is

#ifndef _CONSTCOLOR
#define _CONSTCOLOR 1

#include "Texture.h"

class TexConstColor:public Texture
{
	Vector3 gettexture(const hitrecord& rec,Vector3& color) const{return color;}
};

#endif
