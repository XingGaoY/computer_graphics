#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include "SimpleObject.h"
#include "Octree.h"
#include "Texture_ConstColor.h"
#include "Raytrace.h"
#include <fstream>
using namespace cv;
Mat workspace(500,600,CV_8UC3,Scalar(0,0,0));
std::vector<Octree*> objlist;
std::vector<LightSource*> source;
Vector3 Ambient(30,30,30);
int LightNum;
int ObjNum;
void Render(float length,float width,Vector3 eye)
{
	float x0, z0;
	x0 = length/600;
	z0 = width/500;
	float x = 0, z = 0;
	int B,G,R;
	for(int i=499;i>=0;i--)
	{
		for(int j=0;j<600;j++)
		{
			Ray ray(Vector3(0,0,0),Getnorm(Vector3(x,0,z) - eye),eye);
			ray.Setref(1);
			bool inoct=false;
			Raytrace(ray,1,ray.colour,objlist,inoct,NULL,NULL);
			B = ray.colour.val[2];
			G = ray.colour.val[1];
			R = ray.colour.val[0];
			if(B>255) B = 255;
			if(G>255) G = 255;
			if(R>255) R = 255;
			Vec3b rest(B,G,R);
			workspace.at<Vec3b>(i,j) = rest;
			x += x0;
			/*if(R<50)
			{
 	    		imshow("RayTracing",workspace);
				waitKey(1);
			}*/
		}
		z += z0;
		x = 0;
		imshow("RayTracing",workspace);
  		waitKey(1);
	}
}
int main()
{
	Vector3 eye(3,-5,2.5);
	setscene();
	LightNum = source.size();
	ObjNum = objlist.size();
	Render(6,5,eye);
	waitKey();
	deletescene();
}
