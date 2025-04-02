#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Tools.hpp"
#include <math.h>
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Vec2::Vec2(float _value)
{
	x = _value;
	y = _value;
}

Vec2::Vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vec2::Vec2(Vec3 _vec3)
{
	x = _vec3.x;
	y = _vec3.y;
}

Vec2::Vec2(Vec4 _vec4)
{
	x = _vec4.x;
	y = _vec4.y;
}

Vec2::Vec2(const Vec2& _copy)
{
	x = _copy.x;
	y = _copy.y;
}


//####################### FUNCTIONS #######################

void Vec2::SetZero()
{
	x = 0.f;
	y = 0.f;
}

void Vec2::SetOne()
{
	x = 1.f;
	y = 1.f;
}

void Vec2::Opposite()
{
	x *= -1.f;
	y *= -1.f;
}

void Vec2::MidPoint(Vec2 _vec)
{
	x = (x + _vec.x) / 2.f;
	y = (y + _vec.y) / 2.f;
}

float Vec2::Distance(Vec2 _vec) const
{
	return sqrtf(powf(x - _vec.x, 2.f) + powf(y - _vec.y, 2.f));
}

float Vec2::SquareNorm() const
{
	return powf(x, 2.f) + powf(y, 2.f);
}

float Vec2::Norm() const
{
	return sqrtf(powf(x, 2.f) + powf(y, 2.f));
}

void Vec2::Normalize()
{
	*this /= Norm();
}

float Vec2::DotProduct(Vec2 _vec) const
{
	return (x * _vec.x) + (y * _vec.y);
}

float Vec2::CrossProduct(Vec2 _vec) const
{
	return (x * _vec.y) - (y * _vec.x);
}

void Vec2::Rotate(float _theta, Vec2 _anchor)
{
	if (_anchor.x != 0.f || _anchor.y != 0.f)
		*this += Opposite(_anchor);

	Vec2 tempVector = *this;
	x = tempVector.x * cosf(_theta) - tempVector.y * sinf(_theta);
	y = tempVector.x * sinf(_theta) + tempVector.y * cosf(_theta);

	if (_anchor.x != 0.f || _anchor.y != 0.f)
		*this += _anchor;
}

void Vec2::Print() const
{
	std::cout << "X: " << x << ", Y: " << y << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec2 Vec2::Zero()
{
	return { 0.f, 0.f };
}

Vec2 Vec2::One()
{
	return { 1.f, 1.f };
}

Vec2 Vec2::Opposite(Vec2 _vec)
{
	return { -_vec.x, -_vec.y };
}

Vec2 Vec2::MidPoint(Vec2 _vec1, Vec2 _vec2) 
{
	return { (_vec1.x + _vec2.x) / 2.f, (_vec1.y + _vec2.y) / 2.f };
}

float Vec2::Distance(Vec2 _vec1, Vec2 _vec2)
{
	return sqrtf(powf(_vec1.x - _vec2.x, 2.f) + powf(_vec1.y - _vec2.y, 2.f));
}

float Vec2::SquareNorm(Vec2 _vec)
{
	return powf(_vec.x, 2.f) + powf(_vec.y, 2.f);
}

float Vec2::Norm(Vec2 _vec)
{
	return sqrtf(powf(_vec.x, 2.f) + powf(_vec.y, 2.f));
}

float Vec2::DotProduct(Vec2 _vec1, Vec2 _vec2)
{
	return (_vec1.x * _vec2.x) + (_vec1.y * _vec2.y);
}

float Vec2::CrossProduct(Vec2 _vec1, Vec2 _vec2)
{
	return (_vec1.x * _vec2.y) - (_vec1.y * _vec2.x);
}

Vec2 Vec2::Rotate(Vec2 _vec, float _theta, Vec2 _anchor)
{
	if (_anchor.x != 0.f || _anchor.y != 0.f)
		_vec += Opposite(_anchor);

	Vec2 vecRotate{ _vec.x * cosf(_theta) - _vec.y * sinf(_theta),_vec.x * sinf(_theta) + _vec.y * cosf(_theta) };

	if (_anchor.x != 0.f || _anchor.y != 0.f)
		vecRotate += _anchor;
	return vecRotate;
}

void Vec2::Print(Vec2 _vec)
{
	std::cout << "X: " << _vec.x << ", Y: " << _vec.y << std::endl;
}


//####################### OPERATORS #######################

Vec2 Vec2::operator+(float _scalar) const
{
	return { x + _scalar, y + _scalar };
}

Vec2 Vec2::operator+(Vec2 _vec) const
{
	return { x + _vec.x, y + _vec.y };
}

Vec2 Vec2::operator-(float _scalar) const
{
	return { x - _scalar, y - _scalar };
}

Vec2 Vec2::operator-(Vec2 _vec) const
{
	return { x - _vec.x, y - _vec.y };
}

Vec2 Vec2::operator*(float _scalar) const
{
	return { x * _scalar, y * _scalar };
}

Vec2 Vec2::operator*(Vec2 _vec) const
{
	return { x * _vec.x, y * _vec.y };
}

Vec2 Vec2::operator/(float _scalar) const
{
	if (_scalar != 0.f)
		return { x / _scalar, y / _scalar };
	return { NAN, NAN }; // TODO Replace
}

Vec2 Vec2::operator/(Vec2 _vec) const
{
	if (_vec.x != 0.f && _vec.y != 0.f)
		return { x / _vec.x, y / _vec.y };
	return { NAN, NAN }; // TODO Replace
}

void Vec2::operator+=(float _scalar)
{
	x += _scalar;
	y += _scalar;
}

void Vec2::operator+=(Vec2 _vec)
{
	x += _vec.x;
	y += _vec.y;
}

void Vec2::operator-=(float _scalar)
{
	x -= _scalar;
	y -= _scalar;
}

void Vec2::operator-=(Vec2 _vec)
{
	x -= _vec.x;
	y -= _vec.y;
}

void Vec2::operator*=(float _scalar)
{
	x *= _scalar;
	y *= _scalar;
}

void Vec2::operator*=(Vec2 _vec)
{
	x *= _vec.x;
	y *= _vec.y;
}

void Vec2::operator/=(float _scalar)
{
	if (_scalar == 0.f)
		return;

	x /= _scalar;
	y /= _scalar;
}

void Vec2::operator/=(Vec2 _vec)
{
	if (_vec.x == 0.f || _vec.y == 0.f)
		return;

	x /= _vec.x;
	y /= _vec.y;
}

float Vec2::operator[](int i) const
{
	if (i == 0)
		return x;
	else if (i == 1)
		return y;
	return NAN; // TODO Replace
}

void Vec2::operator=(float _scalar)
{
	x = _scalar;
	y = _scalar;
}

void Vec2::operator=(Vec2 _vec)
{
	x = _vec.x;
	y = _vec.y;
}

bool Vec2::operator==(Vec2 _vec) const
{
	return	fabsf(x - _vec.x) <= Tools::epsilon &&
			fabsf(y - _vec.y) <= Tools::epsilon;
}

bool Vec2::operator!=(Vec2 _vec) const
{
	return	fabsf(x - _vec.x) >= Tools::epsilon ||
			fabsf(y - _vec.y) >= Tools::epsilon;
}