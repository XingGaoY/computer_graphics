#include "Surface.h"

Surface::Surface(bool transparent, Vector3 DR, Vector3 SR, Vector3 AR,int RSP
						, Vector3 DT, Vector3 ST, int TSP,Vector3 IR, Vector3 IT,Texture* tex)
{
	Transparent = transparent;
	DiffuseReflect = DR;
	SpecularReflect = SR;
	AmbientReflect = AR;
	ReflectSmoothPara = RSP;
	DiffuseTransmit = DT;
	SpecularTransmit = ST;
	TransmitSmoothPara = TSP;
	IndirectReflect = IR;
	indirectTransmit = IT;
	texture = tex;
}

void Surface::SetRefraction(float inrefra,float outrefra)
{
	inrefraction = inrefra;
	outrefraction = outrefra;
}

