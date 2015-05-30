//Class_Texture_Checkboard

#ifndef _CHECKBOARD
#define _CHECKBOARD 1

#include "Texture.h"

class TexCheckboard:public Texture
{
public:
	Vector3 gettexture(const hitrecord& rec,Vector3& color) const;

};


#endif