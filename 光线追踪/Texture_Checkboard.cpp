#include "Texture_Checkboard.h"

Vector3 TexCheckboard::gettexture(const hitrecord& rec, Vector3& color) const
{
	Vector3 result(0,0,0);
	bool x,y;
	if(sin(rec.hitpoint.x()*5)>0)x = true;
	else x = false;
	if(sin(rec.hitpoint.y()*5)>0)y = true;
	else y = false;
	if(x^y)return Vector3(0,0,0);
	else return Vector3(100,100,100);

}