#include "Vector.h"

Vector3 Vector3::operator-() const
{ return Vector3(-val[0], -val[1], -val[2]); }

Vector3& Vector3::operator=(const Vector3& v)
{
	val[0] = v[0];
	val[1] = v[1];
	val[2] = v[2];
	return *this;
}

void Vector3::operator +=(const Vector3&v)
{
	for(int i=0;i<3;i++)
	{
		val[i] += v.val[i];
	}
}

void Vector3::operator+=(float f)
{
	for(int i=0;i<3;i++)
	{
		val[i] += f;
	}
}

void Vector3::operator-=(const Vector3&v)
{
	for(int i=0;i<3;i++)
	{
		val[i] -= v.val[i];
	}
}

void Vector3::operator-=(float f)
{
	for(int i=0;i<3;i++)
	{
		val[i] -= f;
	}
}
void Vector3::operator *=(const Vector3& v)
{
	for(int i=0;i<3;i++)
		val[i] *= v.val[i];
}
void Vector3::operator *=(float f)
{
    for(int i=0;i<3;i++)
        val[i] *= f;
}

void Vector3::operator /=(const Vector3& v)
{
    for(int i=0;i<3;i++)
        val[i] /= v.val[i];
}

void Vector3::operator /=(float f)
{
    for(int i=0;i<3;i++)
        val[i] /= f;
}

bool::operator==(const Vector3& v1, const Vector3& v2)
{
	if(v1.val[0]!=v2.val[0]) return false;
	if(v1.val[1]!=v2.val[1]) return false;
	if(v1.val[2]!=v2.val[2]) return false;
	return true;
}

bool::operator!=(const Vector3& v1, const Vector3& v2)
{
	return !(v1==v2);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.val[0]+v2.val[0],v1.val[1]+v2.val[1],v1.val[2]+v2.val[2]);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.val[0]-v2.val[0],v1.val[1]-v2.val[1],v1.val[2]-v2.val[2]);
}

Vector3 operator*(const Vector3& v, float scalar)
{
	return Vector3(v.val[0]*scalar,v.val[1]*scalar,v.val[2]*scalar);
}

Vector3 operator*(float scalar, const Vector3& v)
{
	return Vector3(v.val[0]*scalar,v.val[1]*scalar,v.val[2]*scalar);
}

Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result[0] = v1[0] * v2[0];
	result[1] = v1[1] * v2[1];
	result[2] = v1[2] * v2[2];
	return result;
}


float Vector3::length() const
{
	double sqr;
	sqr = val[0]*val[0]+val[1]*val[1]+val[2]*val[2];
	return (float)sqrt(sqr);
}

float Vector3::sqlength() const
{
	return val[0]*val[0]+val[1]*val[1]+val[2]*val[2];
}

float Vector3::gmax() const
{
	float _max = val[0];
	if( val[1] > _max)
		_max = val[1];
	if( val[2] >_max)
		_max = val[2];
	return _max;
}


float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.val[0]*v2.val[0]+v1.val[1]*v2.val[1]+v1.val[2]*v2.val[2];
}

Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.val[1]*v2.val[2]-v1.val[2]*v2.val[1],v1.val[2]*v2.val[0]-v1.val[0]*v2.val[2],v1.val[0]*v2.val[1]-v1.val[1]*v2.val[0]);
}

Vector3 Getnorm(Vector3& v)
{
	return v * ( 1 / v.length());
}

