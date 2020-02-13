#pragma once

class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	__forceinline Vector& operator+=(const Vector& v);
	__forceinline Vector& operator-=(const Vector& v);
	__forceinline Vector& operator*=(const Vector& v);
	__forceinline Vector& operator*=(float s);
	__forceinline Vector& operator/=(const Vector& v);
	__forceinline Vector& operator/=(float s);
	__forceinline Vector& operator+=(float fl);
	__forceinline Vector& operator-=(float fl);
	inline float Length() const;

	__forceinline float LengthSqr(void) const
	{
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	float NormalizeInPlace();
	Vector Normalize() const;
	__forceinline float DistToSqr(const Vector& vOther) const;
	__forceinline float Dist(const Vector& vOther) const;
	float Dot(const Vector& vOther) const;
	float Dot(const float* fOther) const;
	float Length2D(void) const;
	float Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector operator-(const Vector& v) const;
	Vector operator+(const Vector& v) const;
	Vector operator*(const Vector& v) const;
	Vector operator/(const Vector& v) const;
	Vector operator*(float fl) const;
	Vector operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

//===============================================
inline Vector::Vector(void)
{ }

//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}

//===============================================
inline Vector& Vector::operator=(const Vector& vOther)
{
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	return *this;
}

//===============================================
inline float& Vector::operator[](int i)
{
	return ((float*)this)[i];
}

//===============================================
inline float Vector::operator[](int i) const
{
	return ((float*)this)[i];
}

//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}

//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//===============================================
__forceinline void VectorCopy(const Vector& src, Vector& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

//===============================================
__forceinline Vector& Vector::operator+=(const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator/=(const Vector& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

//===============================================
inline float Vector::Length(void) const
{
	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	__asm sqrtss xmm0, sqsr
	__asm movss root, xmm0

	return root;
}

//===============================================
inline float Vector::Length2D(void) const
{
	float root = 0.0f;

	float sqst = x * x + y * y;

	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}

	return root;
}

//===============================================
inline float Vector::Length2DSqr(void) const
{
	return (x * x + y * y);
}

//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

//===============================================
float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}

float Vector::Dist(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}

inline Vector Vector::Normalize() const
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else {
		vector.x = vector.y = 0.0f;
		vector.z = 1.0f;
	}

	return vector;
}

//===============================================
inline float Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return 0;
}

//===============================================
inline float VectorNormalize(Vector& v)
{
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
		v.z = 1.0f;
	}
	return l;
}

//===============================================
__forceinline float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
}

//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return (a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

inline float Vector::Dot(const float* fOther) const
{
	const Vector& a = *this;

	return (a.x * fOther[0] + a.y * fOther[1] + a.z * fOther[2]);
}

inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}