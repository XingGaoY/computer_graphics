#include "Matrix.h"

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix c;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
		}
	}
	return c;
}

void Matrix::operator +=(const Matrix& m)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			matrix[i][j] += m.matrix[i][j];
		}
	}
}

bool Getmin(const Matrix& a,Vector3& vec,float& delta)
{
	double EIHF = a.matrix[1][1]*a.matrix[2][2] - a.matrix[1][2]*a.matrix[2][1];
	double GFDI = a.matrix[0][2]*a.matrix[2][1] - a.matrix[0][1]*a.matrix[2][2];
	double DHEG = a.matrix[0][1]*a.matrix[1][2] - a.matrix[1][1]*a.matrix[0][2];

	double M = a.matrix[0][0]*EIHF + a.matrix[1][0]*GFDI + a.matrix[2][0]*DHEG;
	if(abs(M)<0.0001)return false;
	
	double AKJB = -a.matrix[0][0]*a.matrix[1][3] + a.matrix[0][3]*a.matrix[1][0];
	double JCAL = -a.matrix[0][3]*a.matrix[2][0] + a.matrix[0][0]*a.matrix[2][3];
	double BLKC = -a.matrix[1][0]*a.matrix[2][3] + a.matrix[1][3]*a.matrix[2][0];

	double x = a.matrix[0][3]*EIHF + a.matrix[1][3]*GFDI + a.matrix[2][3]*DHEG;
	x = -x/M;
	double y = a.matrix[2][2]*AKJB + a.matrix[1][2]*JCAL + a.matrix[0][2]*BLKC;
	y = y/M;
	double z = a.matrix[2][1]*AKJB + a.matrix[1][1]*JCAL + a.matrix[0][1]*BLKC;
	z = -z/M;

	delta = a.matrix[0][0]*x*x + a.matrix[1][1]*y*y + a.matrix[2][2]*z*z + 2*a.matrix[0][1]*x*y + 2*a.matrix[0][2]*x*z 
		+ 2*a.matrix[1][2]*y*z + 2*a.matrix[0][3]*x + 2*a.matrix[1][3]*y + 2*a.matrix[2][3]*z + a.matrix[3][3];

	vec = Vector3(x,y,z);
	return true;
}

