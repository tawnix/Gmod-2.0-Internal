#pragma once
#include <math.h>
#include <stdlib.h>


class QAngleByValue;

class QAngle
{
public:
	float x, y, z;

	QAngle(void);
	QAngle(float X, float Y, float Z);

	operator QAngleByValue& ()
	{
		return *((QAngleByValue*)(this));
	}

	operator const QAngleByValue& () const
	{
		return *((const QAngleByValue*)(this));
	}

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	bool IsValid() const;
	void Invalidate();

	bool IsZero()
	{
		if (this->x == 0.f && this->y == 0.f && this->z == 0.f)
			return true;

		return false;
	}

	float operator[](int i) const;
	float& operator[](int i);

	float* Base();
	float const* Base() const;

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	float Length() const;
	float LengthSqr() const;

	QAngle& operator=(const QAngle& src);

	QAngle operator-(void) const;

	QAngle operator+(const QAngle& v) const;
	QAngle operator-(const QAngle& v) const;
	QAngle operator*(float fl) const;
	QAngle operator/(float fl) const;

	QAngle Clamp();
	QAngle Mod(float N);

	inline QAngle Normalize()
	{
		QAngle vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
			vector.x = vector.y = 0.0f;
		vector.z = 1.0f;

		return vector;
	}

	QAngle Normalized()
	{
		if (this->x != this->x)
			this->x = 0;
		if (this->y != this->y)
			this->y = 0;
		if (this->z != this->z)
			this->z = 0;

		if (this->x > 89.f)
			this->x = 89.f;
		if (this->x < -89.f)
			this->x = -89.f;

		while (this->y > 180)
			this->y -= 360;
		while (this->y <= -180)
			this->y += 360;

		if (this->y > 180.f)
			this->y = 180.f;
		if (this->y < -180.f)
			this->y = -180.f;

		this->z = 0;

		return *this;
	}
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = float_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle& vOther)
{
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	return (float)sqrt(LengthSqr()); //todo replace with fastsqrt
}

inline float QAngle::LengthSqr() const
{
	return x * x + y * y;
}

inline QAngle QAngle::operator-(void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle QAngle::Clamp()
{
	if (this->x < -89.0f)
		this->x = -89.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;

	return *this;
}

inline QAngle QAngle::Mod(float N)
{
	this->x = fmod(x, N);
	this->y = fmod(y, N);
	this->z = fmod(z, N);

	return *this;
}