//Octree
#pragma once

#include "SimpleObject.h"
#include "Texture.h"
#include "Ray.h"
#include "Surface.h"

using namespace SimpleOBJ;

class Vector2
{
public:
	float val[2];

	Vector2(float a,float b){val[0]=a;val[1]=b;}

	Vector2 operator-(){return Vector2(-val[0],-val[1]);}
	
	float x(){return val[0];}
	float y(){return val[1];}

	friend float dot(Vector2 v1,Vector2 v2){return v1.x()*v2.x()+v1.y()*v2.y();}
};


class Octree:public Surface
{
public:
	CSimpleObject* obj;
	int depth;
	Vector3 min;
	Vector3 max;
	Vector3 delta;
	int Facenum;				//the number of Vertex in the node, if = 1, it is a leaf node
	Octree* child;
	int* ele;

	Octree(){};
	Octree(int num,bool transparent,Vector3 DR, Vector3 SR, Vector3 AR,int RSP, Vector3 DT, Vector3 ST, int TSP, Vector3 IR, Vector3 IT,Texture* tex);

	int CreatOct(int* &_ele,Vector3 _min,Vector3 _max,int _num,const int minnum,const int currentdepth);
	bool findsub(Vector3 _p,Vector3 _d,Octree* &ptr);
	void setOct();
	Vector3 crossBox(Ray _ray,Octree* ptr,Vector3 point);
	bool hitOct(Ray _ray,Octree* ptr,hitrecord& rec,float tmax,float tmin);
	bool BoundHit(Ray _ray,hitrecord& rec,float tmin,float tmax);
};
bool Gethitpoint(const Ray& ray, hitrecord& record,Vector3 p0,Vector3 p1,Vector3 p2,Vector3 p0n,Vector3 p1n,Vector3 p2n,float tmax,float tmin);
bool findhit(Ray ray,std::vector<Octree*> objlist,float &tmin,float &tmax,hitrecord& rec,bool& inoct,Octree* &obj,Octree* &ptr,bool& outscene);
