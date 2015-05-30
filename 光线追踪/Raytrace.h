//raytrace.h

#ifndef _RAYTRACE
#define _RAYTRACE 1
#define INFINITY 0xffffffff
#define Minweight 0.00001

#include "Ray.h"
#include "Sphere.h"
#include "Octree.h"
#include "Triangle.h"
#include "SimpIllumMod.h"
#include "LightSource.h"
#include <opencv2\highgui\highgui.hpp>
#include "SetScene.h"

using namespace cv;

hitrecord record;


void Raytrace( Ray& view, float weight, Vector3& color,std::vector<Octree*> objlist,bool inoct,Octree* obj,Octree* ptr)
{
	if(weight < Minweight)
		view.colour = Vector3(0,0,0);
	else
	{
	bool shadowrec = true;
	Vector3* NearestPoint = NULL;
	float Nearestdistance = INFINITY;
	Octree* NearestObj = obj;
	Octree* subOct=ptr,*shadowh;
	Vector3 local;
	Vector3 refl = Vector3(0,0,0);
	Vector3 tras = Vector3(0,0,0);
	float tmax,tmin=0;
	Vector3 shadir;
	bool outscene=false;
	record.hit = false;

	while(!outscene)
	{
		findhit(view,objlist,tmin,Nearestdistance,record,inoct,NearestObj,subOct,outscene);
		if(record.hit)break;
	}
	if(NearestObj)
	{
		local = Ambient * NearestObj->AmbientReflect;
		for( int j = 0; j < LightNum; j++)
		{
			shadowrec=true;
			shadowh=NearestObj;
			outscene = false;
			hitrecord srecord = record;
			shadir = source[j]->origin - srecord.hitpoint;
			tmax = shadir.length();
			shadir = Getnorm(shadir);
			Ray shadow( source[j]->colour, shadir,srecord.hitpoint+shadir*0.1);
			inoct=true;
			tmin = 0;
			Octree* shadowsuboct = subOct;
			while(!outscene)
			{
				if(findhit(shadow,objlist,tmin,tmax,srecord,inoct,shadowh,shadowsuboct,outscene))
				{
					shadowrec=false;
					break;
				}
			}
			if(shadowrec)   local =local + DirectLightReflect( shadow,NearestObj,view,srecord);
		}
		Ray refray = GetReflectDirection(view,record);
		inoct=true;
		Raytrace(refray,weight * NearestObj->IndirectReflect.gmax(),refl,objlist,inoct,NearestObj,subOct);
		if(NearestObj->Transparent)
		{
			bool iftra = true;
			Ray traray = GetTransmitDirection(view,record,NearestObj,iftra);
			if(iftra)			//È«·´Éä
			{
				if( dot(NearestObj->outnorm,view.direct) < 0 )
				{
					inoct=true;
					Raytrace(traray,weight * NearestObj->indirectTransmit.gmax(),tras,objlist,inoct,NearestObj,subOct);
				}
				else
				{
					for(int j = 0; j < LightNum; j++)
					{
						shadir = source[j]->origin - record.hitpoint;
						tmax = shadir.length();
						Ray shadow ( source[j]->colour, Getnorm(shadir) ,record.hitpoint);
						tmin =0;
						while(!outscene)
						{
							if(findhit(shadow,objlist,tmin,tmax,record,inoct,shadowh,subOct,outscene))
							{
								shadowrec=false;
								break;
							}
						}
						if(shadowrec)	local = local + DirectLightTrans( shadow, NearestObj,view,record);
					}
					inoct=true;
					Raytrace(traray,weight * NearestObj->indirectTransmit.gmax(),tras,objlist,inoct,NearestObj,subOct);
				}
			}
		}
		color = local + NearestObj->IndirectReflect * refl + NearestObj->indirectTransmit * tras;
	}
	else view.colour = Vector3(0,0,0);
	}
}


#endif