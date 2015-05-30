//vector3.h

#ifndef _VECTOR3_H
#define _VECTOR3_H 1

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

class Vector3
{
public:
	float val[3];

	Vector3(){};											//constructor
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &v){ *this = v; };

	__forceinline float& operator [](int index)
	{
		assert(index>=0&&index<3);
		return val[index];
	}

	__forceinline const float& operator [](int index) const
	{
		assert(index>=0&&index<3);
		return val[index];
	}



	float x() const { return val[0]; }
	float y() const { return val[1]; }
	float z() const { return val[2]; }

	Vector3 operator-() const;
	Vector3& operator=(const Vector3&v);

	void operator +=(const Vector3& v);
	void operator +=(float f);
	void operator -=(const Vector3& v);
	void operator -=(float f);
	void operator *=(const Vector3& v);
    void operator *=(float f);
    void operator /=(const Vector3& v);
    void operator /=(float f);

	friend bool operator==(const Vector3& v1, const Vector3& v2);
	friend bool operator!=(const Vector3& v1, const Vector3& v2);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v, float scalar);
	friend Vector3 operator*(float scalar, const Vector3& v);
	friend Vector3 operator*(const Vector3& v1, const Vector3& v2);

	float length() const;
	float sqlength() const;
	float gmax() const;

	friend float dot(const Vector3& v1, const Vector3& v2);
	friend Vector3 cross(const Vector3& v1, const Vector3& v2);

	friend Vector3 Getnorm(Vector3& v);
};

inline Vector3::Vector3(float x, float y, float z)
{
	val[0] = x; val[1] = y; val[2] = z;
}



#endif