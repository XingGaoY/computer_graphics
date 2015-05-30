//BoundBox
#pragma once

class BoundBox
{
public:
	float xmin;
	float ymin;
	float zmin;
	float xmax;
	float ymax;
	float zmax;

	BoundBox(){}
	BoundBox(float _xmin,float _ymin,float _zmin,float _xmax,float _ymax,float _zmax)
	{
		xmin = _xmin;ymin = _ymin;zmin = _zmin;xmax = _xmax;ymax = _ymax;zmax = _zmax;
	}
};
