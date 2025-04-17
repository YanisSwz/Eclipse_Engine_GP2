#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat3.hpp"
#include "Tools.hpp"
#include <math.h>
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Vec3::Vec3(float _scalar)
{
	x = _scalar;
	y = _scalar;
	z = _scalar;
}

Vec3::Vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3::Vec3(Vec2 _vec2)
{
	x = _vec2.x;
	y = _vec2.y;
	z = 0.f;
}

Vec3::Vec3(Vec2 _vec2, float _z)
{
	x = _vec2.x;
	y = _vec2.y;
	z = _z;
}

Vec3::Vec3(Vec3 _vec1, Vec3 _vec2)
{
	x = _vec2.x - _vec1.x;
	y = _vec2.y - _vec1.y;
	z = _vec2.z - _vec1.z;
}

Vec3::Vec3(Vec4 _vec4)
{
	x = _vec4.x;
	y = _vec4.y;
	z = _vec4.z;
}

Vec3::Vec3(const Vec3& _copy)
{
	x = _copy.x;
	y = _copy.y;
	z = _copy.z;
}

//####################### STATIC VARIABLES #######################

const Vec3 Vec3::right{1.f, 0.f, 0.f};
const Vec3 Vec3::up{ 0.f, 1.f, 0.f };
const Vec3 Vec3::forward{ 0.f, 0.f, 1.f };

//####################### FUNCTIONS #######################

void Vec3::SetZero()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

void Vec3::SetOne()
{
	x = 1.f;
	y = 1.f;
	z = 1.f;
}

void Vec3::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
}

void Vec3::MidPoint(Vec3 _vec)
{
	x = (x + _vec.x) / 2.f;
	y = (y + _vec.y) / 2.f;
	z = (z + _vec.z) / 2.f;
}

float Vec3::Distance(Vec3 _vec) const
{
	return sqrtf(powf(x - _vec.x, 2.f) + powf(y - _vec.y, 2.f) + powf(z - _vec.z, 2.f));
}

float Vec3::SquareNorm() const
{
	return powf(x, 2.f) + powf(y, 2.f) + powf(z, 2.f);
}

float Vec3::Norm() const
{
	return sqrtf(powf(x, 2.f) + powf(y, 2.f) + powf(z, 2.f));
}

void Vec3::Normalize()
{
	float norm = Norm();
	if (norm >= Tools::epsilon)
	{
		x /= norm;
		y /= norm;
		z /= norm;
	}
}

float Vec3::DotProduct(Vec3 _vec) const
{
	return (x * _vec.x) + (y * _vec.y) + (z * _vec.z);
}

void Vec3::CrossProduct(Vec3 _vec)
{
	float tempX = x;
	float tempY = y;
	float tempZ = z;
	x = (tempY * _vec.z) - (tempZ * _vec.y);
	y = (tempZ * _vec.x) - (tempX * _vec.z);
	z = (tempX * _vec.y) - (tempY * _vec.x);
}

void Vec3::RotateX(float _theta, Vec3 _anchor)
{
	*this = Mat3::RotationX(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec3::RotateY(float _theta, Vec3 _anchor)
{
	*this = Mat3::RotationY(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec3::RotateZ(float _theta, Vec3 _anchor)
{
	*this = Mat3::RotationZ(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec3::Rotate(float _theta, Vec3 _anchor)
{
	*this = Mat3::RotationX(_theta) * (*this - _anchor);
	*this = Mat3::RotationY(_theta) * (*this);
	*this = Mat3::RotationZ(_theta) * (*this);
	*this += _anchor;
}

void Vec3::Rotate(Vec3 _theta, Vec3 _anchor)
{
	*this = Mat3::RotationX(_theta.x) * (*this - _anchor);
	*this = Mat3::RotationY(_theta.y) * (*this);
	*this = Mat3::RotationZ(_theta.z) * (*this);
	*this += _anchor;
}

void Vec3::Print() const
{
	std::cout << "X: " << x << ", Y: " << y << ", Z: " << z << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec3 Vec3::Zero()
{
	return { 0.f, 0.f, 0.f };
}

Vec3 Vec3::One()
{
	return { 1.f, 1.f, 1.f };
}

Vec3 Vec3::Opposite(Vec3 _vec)
{
	return { -_vec.x, -_vec.y, -_vec.z };
}

Vec3 Vec3::MidPoint(Vec3 _vec1, Vec3 _vec2)
{
	return { (_vec1.x + _vec2.x) / 2.f, (_vec1.y + _vec2.y) / 2.f , (_vec1.z + _vec2.z) / 2.f };
}

float Vec3::Distance(Vec3 _vec1, Vec3 _vec2)
{
	return sqrtf(powf(_vec1.x - _vec2.x, 2.f) + powf(_vec1.y - _vec2.y, 2.f) + powf(_vec1.z - _vec2.z, 2.f));
}

float Vec3::SquareNorm(Vec3 _vec)
{
	return powf(_vec.x, 2.f) + powf(_vec.y, 2.0) + powf(_vec.z, 2.0);
}

float Vec3::Norm(Vec3 _vec)
{
	return sqrtf(powf(_vec.x, 2.f) + powf(_vec.y, 2.0) + powf(_vec.z, 2.0));
}

Vec3 Vec3::Normalized(Vec3 _vec)
{
	float norm = _vec.Norm();
	if(norm >= Tools::epsilon)
		return _vec / norm;
	return _vec;
}

float Vec3::DotProduct(Vec3 _vec1, Vec3 _vec2)
{
	return (_vec1.x * _vec2.x) + (_vec1.y * _vec2.y) + (_vec1.z * _vec2.z);
}

Vec3 Vec3::CrossProduct(Vec3 _vec1, Vec3 _vec2)
{
	return { _vec1.y * _vec2.z - _vec1.z * _vec2.y, _vec1.z * _vec2.x - _vec1.x * _vec2.z, _vec1.x * _vec2.y - _vec1.y * _vec2.x };
}

Vec3 Vec3::RotateX(Vec3 _vecToRotate, float _theta, Vec3 _anchor)
{
	_vecToRotate = Mat3::RotationX(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor};
}

Vec3 Vec3::RotateY(Vec3 _vecToRotate, float _theta, Vec3 _anchor)
{
	_vecToRotate = Mat3::RotationY(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor };
}

Vec3 Vec3::RotateZ(Vec3 _vecToRotate, float _theta, Vec3 _anchor)
{
	_vecToRotate = Mat3::RotationZ(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor };
}

Vec3 Vec3::Rotate(Vec3 _vecToRotate, float _theta, Vec3 _anchor)
{
	_vecToRotate -= _anchor;
	_vecToRotate = Mat3::RotationX(_theta) * _vecToRotate;
	_vecToRotate = Mat3::RotationY(_theta) * _vecToRotate;
	_vecToRotate = Mat3::RotationZ(_theta) * _vecToRotate;
	return { _vecToRotate + _anchor };
}

Vec3 Vec3::Rotate(Vec3 _vecToRotate, Vec3 _theta, Vec3 _anchor)
{
	_vecToRotate -= _anchor;
	_vecToRotate = Mat3::RotationX(_theta.x) * _vecToRotate;
	_vecToRotate = Mat3::RotationY(_theta.y) * _vecToRotate;
	_vecToRotate = Mat3::RotationZ(_theta.z) * _vecToRotate;
	return { _vecToRotate + _anchor };
}

void Vec3::Print(Vec3 _vec)
{
	std::cout << "X: " << _vec.x << ", Y: " << _vec.y << ", Z: " << _vec.z << std::endl;
}


//####################### OPERATORS #######################

Vec3 Vec3::operator+(float _scalar) const
{
	return { x + _scalar, y + _scalar, z + _scalar };
}

Vec3 Vec3::operator+(Vec3 _vec) const
{
	return { x + _vec.x, y + _vec.y, z + _vec.z };
}

Vec3 Vec3::operator-(float _scalar) const
{
	return { x - _scalar, y - _scalar, z - _scalar };
}

Vec3 Vec3::operator-(Vec3 _vec) const
{
	return { x - _vec.x, y - _vec.y, z - _vec.z };
}

Vec3 Vec3::operator*(float _scalar) const
{
	return { x * _scalar, y * _scalar, z * _scalar };
}

Vec3 Vec3::operator*(Vec3 _vec) const
{
	return { x * _vec.x, y * _vec.y, z * _vec.z };
}

Vec3 Vec3::operator/(float _scalar) const
{
	if (_scalar != 0.f)
		return { x / _scalar, y / _scalar, z / _scalar };
	return {NAN, NAN, NAN}; // TODO Replace
}

Vec3 Vec3::operator/(Vec3 _vec) const
{
	if (_vec.x != 0.f && _vec.y != 0.f && _vec.z != 0.f)
		return { x / _vec.x, y / _vec.y, z / _vec.z };
	return { NAN, NAN, NAN }; // TODO Replace
}

void Vec3::operator+=(float _scalar)
{
	x += _scalar;
	y += _scalar;
	z += _scalar;
}

void Vec3::operator+=(Vec3 _vec)
{
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;
}

void Vec3::operator-=(float _scalar)
{
	x -= _scalar;
	y -= _scalar;
	z -= _scalar;
}

void Vec3::operator-=(Vec3 _vec)
{
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;
}

void Vec3::operator*=(float _scalar)
{
	x *= _scalar;
	y *= _scalar;
	z *= _scalar;
}

void Vec3::operator*=(Vec3 _vec)
{
	x *= _vec.x;
	y *= _vec.y;
	z *= _vec.z;
}

void Vec3::operator/=(float _scalar)
{
	if (_scalar == 0.f)
		return;

	x /= _scalar;
	y /= _scalar;
	z /= _scalar;
}

void Vec3::operator/=(Vec3 _vec)
{
	if (_vec.x == 0.f || _vec.y == 0.f || _vec.z == 0.f)
		return;

	x /= _vec.x;
	y /= _vec.y;
	z /= _vec.z;
}

float Vec3::operator[](int i) const
{
	if (i == 0)
		return x;
	else if (i == 1)
		return y;
	else if (i == 2)
		return z;
	return NAN; // TODO Replace
}

void Vec3::operator=(float _scalar)
{
	x = _scalar;
	y = _scalar;
	z = _scalar;
}

void Vec3::operator=(Vec3 _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
}

bool Vec3::operator==(Vec3 _vec) const
{
	return  fabsf(x - _vec.x) <= Tools::epsilon &&
			fabsf(y - _vec.y) <= Tools::epsilon &&
			fabsf(z - _vec.z) <= Tools::epsilon;
}

bool Vec3::operator!=(Vec3 _vec) const
{
	return	fabsf(x - _vec.x) >= Tools::epsilon ||
			fabsf(y - _vec.y) >= Tools::epsilon ||
			fabsf(z - _vec.z) >= Tools::epsilon;
}