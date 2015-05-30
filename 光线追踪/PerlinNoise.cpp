#include "PerlinNoise.h"

double PerlinNoise:: randomNum(int x, int y) const
{
	int n = 13*x + 29*y;
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

double PerlinNoise:: lerp(double a,double b,double x) const
{
	return a*(1-x)+b*x;
}
double PerlinNoise:: diffr(int x,int y) const
{
	double corner = (randomNum(x-1,y-1)+randomNum(x+1,y-1)+randomNum(x-1,y+1)+randomNum(x+1,y+1))/16;
	double side = (randomNum(x-1,y)+randomNum(x+1,y)+randomNum(x,y-1)+randomNum(x,y+1))/8;
	double center = randomNum(x,y)/4;
	return corner+side+center;
}

double PerlinNoise:: interpolate(float x,float y) const
{
	int intx = floor(x);
	float fracx = x - intx;
	int inty = floor(y);
	float fracy = y - inty;

	double v1 = diffr(intx,inty);
	double v2 = diffr(intx + 1,inty);
	double v3 = diffr(intx,inty + 1);
	double v4 = diffr(intx+1,inty+1);

	double i1 = lerp(v1,v2,fracx);
	double i2 = lerp(v3,v4,fracx);

	return lerp(i1,i2,fracy);
}

double PerlinNoise:: Perlin2D(float x,float y) const
{
	double result = 0;
	int frequency = 1;
	float p = 1;
	for(int i = 0 ; i < octave;i++)
	{
		result += interpolate( x*frequency, y*frequency) * p;
		frequency *= 2;
		p *= persistence;
	}
	return result;
}

