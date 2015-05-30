#pragma once
#include "Octree.h"
#include "LightSource.h"
#include "Texture_ConstColor.h"
#include "Texture_Checkboard.h"
#include "Texture_Marble.h"
#include "SphereTex.h"
#include "Texture_Sphere.h"

extern Vector3 Ambient;

extern	std::vector<Octree*> objlist;
extern	std::vector<LightSource*> source;
	
extern	int LightNum;
extern	int ObjNum;

void setscene()
{
//	Texture* checkboard = new TexCheckboard;
	Texture* constcolor = new TexConstColor;
//	Texture* spheremarble = new TextureSphereMarble(PerlinNoise(0.5,8),5,Vector3(0.2,0.46,0.46),Vector3(0,0,0),Vector3(0.1,0.1,0.1),20);
//	Texture* marble = new TexMarble(PerlinNoise(0.5,2),5,Vector3(0.125,0.169,0.255),Vector3(0,0,0),Vector3(0.863,0.863,0.9),5);
////0
	using namespace SimpleOBJ;
	CSimpleObject* cube = new CSimpleObject;
	cube->LoadFromObj("grouptable.obj");
	objlist.push_back(new Octree(cube->m_nTriangles,false,Vector3(0.7,0.7,0.25),Vector3(0,0,0),Vector3(0.1,0.1,0.1),10,Vector3(0,0,0),Vector3(0,0,0),0,Vector3(0.01,0.01,0.01),Vector3(0,0,0),constcolor));
	int* ele1 = new int[cube->m_nTriangles];
	for(int i=0;i<cube->m_nTriangles;i++)
	{
		ele1[i]=i;
	}
	cube->setface();
	cube->setVert();
	objlist[0]->obj=cube;
	objlist[0]->CreatOct(ele1,Vector3(cube->xmin,cube->ymin,cube->zmin),Vector3(cube->xmax,cube->ymax,cube->zmax),
		cube->m_nTriangles,4,0);
    
	/*CSimpleObject* plane1 = new CSimpleObject;
	plane1->LoadFromObj("grouptable.obj");
	objlist.push_back(new Octree(plane1->m_nTriangles,false,Vector3(0.2,0.7,0.25),Vector3(0,0,0),Vector3(0.1,0.1,0.1),100,Vector3(0,0,0),Vector3(0,0,0),0,Vector3(0.2,0.2,0.2),Vector3(0,0,0),constcolor));
	int* ele2 = new int[plane1->m_nTriangles];
	for(int i=0;i<plane1->m_nTriangles;i++)
	{
		ele2[i]=i;
	}
	plane1->setface();
	plane1->setVert();
	objlist[1]->obj=plane1;
	objlist[1]->CreatOct(ele2,Vector3(plane1->xmin,plane1->ymin,plane1->zmin),Vector3(plane1->xmax,plane1->ymax,plane1->zmax),
		plane1->m_nTriangles,6,0);	*/
	
	
	
	
	
	
	
	
	
	
	
	source.push_back(new LightSource(Vector3(10,1,6),Vector3(255,255,255)));
	source.push_back(new LightSource(Vector3(1,3,10),Vector3(255,255,255)));
}
void deletescene()
{
	delete objlist[0];
	delete source[0];
}

