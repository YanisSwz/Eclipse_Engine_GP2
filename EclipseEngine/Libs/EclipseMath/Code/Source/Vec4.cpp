#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Tools.hpp"
#include <math.h>
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Vec4::Vec4(float _scalar)
{
	x = _scalar;
	y = _scalar;
	z = _scalar;
	w = _scalar;
}

Vec4::Vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vec4::Vec4(Vec2 _vec, float _z, float _w)
{
	x = _vec.x;
	y = _vec.y;
	z = _z;
	w = _w;
}

Vec4::Vec4(Vec2 _vec1, Vec2 _vec2)
{
	x = _vec1.x;
	y = _vec1.y;
	z = _vec2.x;
	w = _vec2.y;
}

Vec4::Vec4(Vec3 _vec, float _w)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
	w = _w;
}

Vec4::Vec4(const Vec4& _copy)
{
	x = _copy.x;
	y = _copy.y;
	z = _copy.z;
	w = _copy.w;
}


//####################### FUNCTIONS #######################

void Vec4::SetZero()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

void Vec4::SetOne()
{
	x = 1.f;
	y = 1.f;
	z = 1.f;
	w = 1.f;
}

void Vec4::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
	w *= -1.f;
}

void Vec4::MidPoint(Vec4 _vec)
{
	x = (x + _vec.x) / 2.f;
	y = (y + _vec.y) / 2.f;
	z = (z + _vec.z) / 2.f;
	w = (w + _vec.w) / 2.f;
}

float Vec4::Distance(Vec4 _vec) const
{
	return sqrtf(powf(x - _vec.x, 2.f) + powf(y - _vec.y, 2.f) + powf(z - _vec.z, 2.f) + powf(w - _vec.w, 2.f));
}

float Vec4::SquareNorm() const
{
	return powf(x, 2.f) + powf(y, 2.0) + powf(z, 2.0) + powf(w, 2.0);
}

float Vec4::Norm() const
{
	return sqrtf(powf(x, 2.f) + powf(y, 2.0) + powf(z, 2.0) + powf(w, 2.0));
}

float Vec4::DotProduct(Vec4 _vec) const
{
	return (x * _vec.x) + (y * _vec.y) + (z * _vec.z) + (w * _vec.w);
}

void Vec4::RotateX(float _theta, Vec4 _anchor)
{
	*this = Mat4::RotationX(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec4::RotateY(float _theta, Vec4 _anchor)
{
	*this = Mat4::RotationY(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec4::RotateZ(float _theta, Vec4 _anchor)
{
	*this = Mat4::RotationZ(_theta) * (*this - _anchor);
	*this += _anchor;
}

void Vec4::Rotate(float _theta, Vec4 _anchor)
{
	*this = Mat4::RotationX(_theta) * (*this - _anchor);
	*this = Mat4::RotationY(_theta) * (*this);
	*this = Mat4::RotationZ(_theta) * (*this);
	*this += _anchor;
}

void Vec4::Rotate(Vec4 _theta, Vec4 _anchor)
{
	*this = Mat4::RotationX(_theta.x) * (*this - _anchor);
	*this = Mat4::RotationY(_theta.y) * (*this);
	*this = Mat4::RotationZ(_theta.z) * (*this);
	*this += _anchor;
}

void Vec4::Print() const
{
	std::cout << "X: " << x << ", Y: " << y << ", Z: " << z << ", W: " << w << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec4 Vec4::Zero()
{
	return { 0.f, 0.f, 0.f, 0.f };
}

Vec4 Vec4::One()
{
	return { 1.f, 1.f, 1.f, 1.f };
}

Vec4 Vec4::Opposite(Vec4 _vec)
{
	return { -_vec.x, -_vec.y, -_vec.z, -_vec.w };
}

Vec4 Vec4::MidPoint(Vec4 _vec1, Vec4 _vec2)
{
	return { (_vec1.x + _vec2.x) / 2.f, (_vec1.y + _vec2.y) / 2.f , (_vec1.z + _vec2.z) / 2.f, (_vec1.w + _vec2.w) / 2.f };
}

float Vec4::Distance(Vec4 _vec1, Vec4 _vec2)
{
	return sqrtf(powf(_vec1.x - _vec2.x, 2.f) + powf(_vec1.y - _vec2.y, 2.f) + powf(_vec1.z - _vec2.z, 2.f) + powf(_vec1.w - _vec2.w, 2.f));
}

float Vec4::SquareNorm(Vec4 _vec)
{
	return powf(_vec.x, 2.f) + powf(_vec.y, 2.0) + powf(_vec.z, 2.0) + powf(_vec.w, 2.0);
}

float Vec4::Norm(Vec4 _vec)
{
	return sqrtf(powf(_vec.x, 2.f) + powf(_vec.y, 2.0) + powf(_vec.z, 2.0) + powf(_vec.w, 2.0));
}

float Vec4::DotProduct(Vec4 _vec1, Vec4 _vec2)
{
	return (_vec1.x * _vec2.x) + (_vec1.y * _vec2.y) + (_vec1.z * _vec2.z) + (_vec1.w * _vec2.w);
}

Vec4 Vec4::RotateX(Vec4 _vecToRotate, float _theta, Vec4 _anchor)
{
	_vecToRotate = Mat4::RotationX(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor };
}

Vec4 Vec4::RotateY(Vec4 _vecToRotate, float _theta, Vec4 _anchor)
{
	_vecToRotate = Mat4::RotationY(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor };
}

Vec4 Vec4::RotateZ(Vec4 _vecToRotate, float _theta, Vec4 _anchor)
{
	_vecToRotate = Mat4::RotationZ(_theta) * (_vecToRotate - _anchor);
	return { _vecToRotate + _anchor };
}

Vec4 Vec4::Rotate(Vec4 _vecToRotate, float _theta, Vec4 _anchor)
{
	_vecToRotate = Mat4::RotationX(_theta) * (_vecToRotate - _anchor);
	_vecToRotate = Mat4::RotationY(_theta) * (_vecToRotate);
	_vecToRotate = Mat4::RotationZ(_theta) * (_vecToRotate);
	return { _vecToRotate + _anchor };
}

Vec4 Vec4::Rotate(Vec4 _vecToRotate, Vec4 _theta, Vec4 _anchor)
{
	_vecToRotate = Mat4::RotationX(_theta.x) * (_vecToRotate - _anchor);
	_vecToRotate = Mat4::RotationY(_theta.y) * (_vecToRotate);
	_vecToRotate = Mat4::RotationZ(_theta.z) * (_vecToRotate);
	return { _vecToRotate + _anchor };
}

void Vec4::Print(Vec4 _vec)
{
	std::cout << "X: " << _vec.x << ", Y: " << _vec.y << ", Z: " << _vec.z << ", W: " << _vec.w << std::endl;
}


//####################### OPERATORS #######################

Vec4 Vec4::operator+(float _scalar) const
{
	return { x + _scalar, y + _scalar, z + _scalar, w + _scalar };
}

Vec4 Vec4::operator+(Vec4 _vec) const
{
	return { x + _vec.x, y + _vec.y, z + _vec.z, w + _vec.w };
}

Vec4 Vec4::operator-(float _scalar) const
{
	return { x - _scalar, y - _scalar, z - _scalar, w - _scalar };
}

Vec4 Vec4::operator-(Vec4 _vec) const
{
	return { x - _vec.x, y - _vec.y, z - _vec.z, w - _vec.w };
}

Vec4 Vec4::operator*(float _scalar) const
{
	return { x * _scalar, y * _scalar, z * _scalar, w * _scalar };
}

Vec4 Vec4::operator*(Vec4 _vec) const
{
	return { x * _vec.x, y * _vec.y, z * _vec.z, w * _vec.w };
}

Vec4 Vec4::operator/(float _scalar) const
{
	if (_scalar != 0.f)
		return { x / _scalar, y / _scalar, z / _scalar, w / _scalar };
	return { NAN, NAN, NAN, NAN }; // TODO Replace
}

Vec4 Vec4::operator/(Vec4 _vec) const
{
	if (_vec.x != 0.f && _vec.y != 0.f && _vec.z != 0.f && _vec.w != 0.f)
		return { x / _vec.x, y / _vec.y, z / _vec.z, w / _vec.w };
	return { NAN, NAN, NAN, NAN }; // TODO Replace
}

void Vec4::operator+=(float _scalar)
{
	x += _scalar;
	y += _scalar;
	z += _scalar;
	w += _scalar;
}

void Vec4::operator+=(Vec4 _vec)
{
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;
	w += _vec.w;
}

void Vec4::operator-=(float _scalar)
{
	x -= _scalar;
	y -= _scalar;
	z -= _scalar;
	w -= _scalar;
}

void Vec4::operator-=(Vec4 _vec)
{
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;
	w -= _vec.w;
}

void Vec4::operator*=(float _scalar)
{
	x *= _scalar;
	y *= _scalar;
	z *= _scalar;
	w *= _scalar;
}

void Vec4::operator*=(Vec4 _vec)
{
	x *= _vec.x;
	y *= _vec.y;
	z *= _vec.z;
	w *= _vec.w;
}

void Vec4::operator/=(float _scalar)
{
	if (_scalar == 0.f)
		return;

	x /= _scalar;
	y /= _scalar;
	z /= _scalar;
	w /= _scalar;
}

void Vec4::operator/=(Vec4 _vec)
{
	if (_vec.x == 0.f || _vec.y == 0.f || _vec.z == 0.f || _vec.w == 0.f)
		return;

	x /= _vec.x;
	y /= _vec.y;
	z /= _vec.z;
	w /= _vec.w;
}

float Vec4::operator[](int i) const
{
	if (i == 0)
		return x;
	else if (i == 1)
		return y;
	else if (i == 2)
		return z;
	else if (i == 3)
		return w;
	return NAN; // TODO Replace
}

void Vec4::operator=(float _scalar)
{
	x = _scalar;
	y = _scalar;
	z = _scalar;
	w = _scalar;
}

void Vec4::operator=(Vec4 _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
	w = _vec.w;
}

bool Vec4::operator==(Vec4 _vec) const
{
	return	fabsf(x - _vec.x) <= Tools::epsilon &&
			fabsf(y - _vec.y) <= Tools::epsilon &&
			fabsf(z - _vec.z) <= Tools::epsilon &&
			fabsf(w - _vec.w) <= Tools::epsilon;
}

bool Vec4::operator!=(Vec4 _vec) const
{
	return	fabsf(x - _vec.x) >= Tools::epsilon ||
			fabsf(y - _vec.y) >= Tools::epsilon ||
			fabsf(z - _vec.z) >= Tools::epsilon ||
			fabsf(w - _vec.w) >= Tools::epsilon;
}