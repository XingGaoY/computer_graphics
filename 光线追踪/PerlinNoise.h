//Class_Perlin_Noise

#ifndef _PERLINNOISE
#define _PERLINNOISE 1

#include "Texture.h"

class PerlinNoise
{
public:

	float persistence;
	int octave;

	PerlinNoise(){};
	PerlinNoise(float _pers,int _oct){persistence = _pers;octave = _oct;}

	double randomNum(int x,int y)const;
	double lerp(double a,double b,double x)const;
	double diffr(int x,int y)const;
	double interpolate(float x,float y) const;
	double Perlin2D(float x,float y) const;
};

#endif