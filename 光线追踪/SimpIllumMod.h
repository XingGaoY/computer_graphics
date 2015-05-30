//SimpIlluMod.h

#ifndef _SIMPILLUMOD
#define _SIMPILLUMOD 1

#include <opencv2\highgui\highgui.hpp>
#include "Ray.h"
#include "Surface.h"
#include "Vector.h"
#include <math.h>

Vector3 DirectLightReflect(const Ray& ray, Surface* surface, const Ray& view, const hitrecord& rec)
{
	Vector3 _result(0,0,0);
	Vector3 _L = ray.direct;
	Vector3 _V = - view.direct;
	Vector3 H = _L + _V;
	Vector3 _norm = rec.norm;
	if(dot(_norm, _L) < 0)
		_norm = - _norm;
	H =H *(1 / H.length());
	float LN = dot( _L, _norm);
	float HN = dot( H, _norm);
	HN = pow(HN,surface->ReflectSmoothPara);
	_result = surface->texture->gettexture(rec,_result);
	for(int i=0;i<3;i++)
	{
		_result[i] += ray.colour[i] * (surface->DiffuseReflect[i]*LN + surface->SpecularReflect[i]*HN);
	}
	return _result;
}

Vector3 DirectLightTrans(const Ray& ray,const Surface* surface,const Ray& view,const hitrecord& rec)
{
	Vector3 _result;
	Vector3 _L = ray.direct;
	Vector3 _V = -view.direct;
	Vector3 _norm = -surface->outnorm;
	float NL = -dot(_norm,_L);
	Vector3 _H;
	_H = surface->outrefraction * _L + surface->inrefraction * _V;
	_H =_H * (1 / _H.length());
	if(surface->inrefraction < surface->outrefraction)
		_H = -_H;
	float HN = dot(_H , _norm);
	HN = pow(HN, surface->TransmitSmoothPara);
	for(int i = 0;i < 3; i++)
	{
		_result[i] = ray.colour[i] * (surface->DiffuseTransmit[i] * NL + surface->SpecularTransmit[i] * HN);
	}
	return _result;
}

Ray GetReflectDirection(const Ray& in,const hitrecord& rec)
{
	Vector3 _L = -in.direct;
	Vector3 _norm = rec.norm;
	if( dot( _L, _norm) < 0)
		_norm = -_norm;
	Vector3 R = 2 * dot(_norm,_L) * _norm;
	R = R - _L;
	return Ray(in.colour,Getnorm(R),rec.hitpoint);
}

Ray GetTransmitDirection(const Ray& in, const hitrecord& rec, const Surface* surface,bool iftra)
{
	Vector3 _L = -in.direct;
	Vector3 _norm;
	float outref;
	if(dot( in.direct, surface->outnorm) < 0)
	{
		_norm = rec.norm;
		outref = surface->inrefraction;
	}
	else
	{
		_norm = -rec.norm;
		outref = surface->outrefraction;
	}
	float ref = in.refraction / outref;
	float cosin = dot (_norm, _L);
	float cosout = cos(asin( ref * sqrtf(1 - (cosin * cosin))));
	if( cosin < 0 ) 
	{
		_norm = -_norm;
		cosin = -cosin;
	}
	if( in.refraction > outref)
	{
		if(cosin <= cos(asin(1 / ref)))
		{
			iftra = false;
			return Ray();
		}
	}
	Vector3 T;
	T = ( ref * cosin - cosout) * _norm - ref * _L;
	iftra = true;
	Ray res(in.colour, Getnorm(T), rec.hitpoint);
	res.Setref(outref);
	return res;
}



#endif