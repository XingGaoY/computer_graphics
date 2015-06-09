#pragma once

#include <cstring>
#include "Vector.h"

class Matrix
{
public:
	float matrix[4][4];

	Matrix(){
	memset(matrix,0.0f,sizeof(float)*16);
	};
	Matrix(float** a)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				matrix[i][j] = a[i][j];
			}
		}
	}
	Matrix(const Matrix &a){
		memcpy(matrix,a.matrix,16*sizeof(float));
	}
	
	friend Matrix operator+(const Matrix& a,const Matrix& b);
	friend bool Getmin(const Matrix& a,Vector3& vec,float& delta);

	void operator +=(const Matrix& m);
};
