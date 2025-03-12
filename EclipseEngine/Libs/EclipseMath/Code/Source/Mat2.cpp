#include "Mat2.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Tools.hpp"
#include <iostream>
using namespace Math;

//####################### CONSTRUCTORS #######################

Mat2::Mat2(float _scalar)
{
	value[0][0] = _scalar;	value[0][1] = _scalar;
	value[1][0] = _scalar;	value[1][1] = _scalar;
}

Mat2::Mat2(float _a, float _b, float _c, float _d)
{
	value[0][0] = _a;	value[0][1] = _b;
	value[1][0] = _c;	value[1][1] = _d;
}

Mat2::Mat2(Vec2 _vec, float _c, float _d)
{
	value[0][0] = _vec[0];	value[0][1] = _vec[1];
	value[1][0] = _c;		value[1][1] = _d;
}

Mat2::Mat2(Vec2 _vec1, Vec2 _vec2)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];
}

Mat2::Mat2(Vec3 _vec, float _d)
{
	value[0][0] = _vec[0];	value[0][1] = _vec[1];
	value[1][0] = _vec[2];	value[1][1] = _d;
}

Mat2::Mat2(Vec4 _vec)
{
	value[0][0] = _vec[0];	value[0][1] = _vec[1];
	value[1][0] = _vec[2];	value[1][1] = _vec[3];
}

Mat2::Mat2(const Mat2& _copy)
{
	value[0][0] = _copy[0][0];
	value[0][1] = _copy[0][1];
	value[1][0] = _copy[1][0];
	value[1][1] = _copy[1][1];
}


//####################### FUNCTIONS #######################

Vec2 Mat2::Diagonal() const
{
	return { value[0][0], value[1][1] };
}

void Mat2::Transpose()
{
	float temp = value[0][1];
	value[0][1] = value[1][0];
	value[1][0] = temp;
}

float Mat2::Trace() const
{
	return value[0][0] + value[1][1];
}

void Mat2::Opposite()
{
	value[0][0] *= -1.f;	value[0][1] *= -1.f;
	value[1][0] *= -1.f;	value[1][1] *= -1.f;
}

float Mat2::Det() const
{
	return (value[0][0] * value[1][1]) - (value[1][0] * value[0][1]);
}

void Mat2::Inverse()
{
	float oneDividedByDet = 1.f / ((value[0][0] * value[1][1]) - (value[1][0] * value[0][1]));
	float temp00 = value[0][0];		float temp01 = value[0][1];
	float temp10 = value[1][0];		float temp11 = value[1][1];
	
	value[0][0] = oneDividedByDet * temp11;		value[0][1] = oneDividedByDet * -temp01;
	value[1][0] = oneDividedByDet * -temp10;	value[1][1] = oneDividedByDet * temp00;
}

void Mat2::Rotate(float _theta)
{
	value[0][0] = cosf(_theta);		value[0][1] = -sinf(_theta);
	value[1][0] = sinf(_theta);		value[1][1] = cosf(_theta);
}

void Mat2::Print() const
{
	std::cout << "|" << value[0][0] << ", " << value[0][1] << "|" << std::endl
			  << "|" << value[1][0] << ", " << value[1][1] << "|" << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec2 Mat2::s_Diagonal(Mat2 _mat)
{
	return { _mat[0][0], _mat[1][1] };
}

Mat2 Mat2::s_Transpose(Mat2 _mat)
{
	return { _mat[0][0], _mat[1][0],
			 _mat[0][1], _mat[1][1] };
}

float Mat2::s_Trace(Mat2 _mat)
{
	return _mat[0][0] + _mat[1][1];
}

Mat2 Mat2::s_Opposite(Mat2 _mat)
{
	return{ -_mat[0][0],	-_mat[0][1],
			-_mat[1][0],	-_mat[1][1] };
}

float Mat2::s_Det(Mat2 _mat)
{
	return (_mat[0][0] * _mat[1][1]) - (_mat[1][0] * _mat[0][1]);
}

Mat2 Mat2::s_Inverse(Mat2 _mat)
{
	float oneDividedByDet = 1.f / ((_mat[0][0] * _mat[1][1]) - (_mat[1][0] * _mat[0][1]));
	return { oneDividedByDet * _mat[1][1], oneDividedByDet * -_mat[0][1],
			 oneDividedByDet * -_mat[1][0], oneDividedByDet * _mat[0][0] };
}

Mat2 Mat2::s_Rotate(float _theta)
{
	return { cosf(_theta), -sinf(_theta), sinf(_theta), cosf(_theta) }; 
}


void Mat2::s_Print(Mat2 _mat)
{
	std::cout << "|" << _mat[0][0] << ", " << _mat[0][1] << "|" << std::endl
	   		  << "|" << _mat[1][0] << ", " << _mat[1][1] << "|" << std::endl;
}


//####################### OPERATORS #######################

Mat2 Mat2::operator+(float _scalar) const
{
	return { value[0][0] + _scalar, value[0][1] + _scalar,
			 value[1][0] + _scalar, value[1][1] + _scalar };
}

Mat2 Mat2::operator+(Mat2 _mat) const
{
	return { value[0][0] + _mat[0][0], value[0][1] + _mat[0][1],
			 value[1][0] + _mat[1][0], value[1][1] + _mat[1][1] };
}

Mat2 Mat2::operator-(float _scalar) const
{
	return { value[0][0] - _scalar, value[0][1] - _scalar,
			 value[1][0] - _scalar, value[1][1] - _scalar };
}

Mat2 Mat2::operator-(Mat2 _mat) const
{
	return { value[0][0] - _mat[0][0], value[0][1] - _mat[0][1],
			 value[1][0] - _mat[1][0], value[1][1] - _mat[1][1] };
}

Mat2 Mat2::operator*(float _scalar) const
{
	return { value[0][0] * _scalar, value[0][1] * _scalar, 
			 value[1][0] * _scalar, value[1][1] * _scalar };
}

Vec2 Mat2::operator*(Vec2 _vec) const
{
	return { value[0][0] * _vec[0] + value[0][1] * _vec[1],
			 value[1][0] * _vec[0] + value[1][1] * _vec[1] };
}

Mat2 Mat2::operator*(Mat2 _mat) const
{
	return { (value[0][0] * _mat[0][0]) + (value[0][1] * _mat[1][0]),
			 (value[0][0] * _mat[0][1]) + (value[0][1] * _mat[1][1]),
			 (value[1][0] * _mat[0][0]) + (value[1][1] * _mat[1][0]),
			 (value[1][0] * _mat[0][1]) + (value[1][1] * _mat[1][1]) };
}

void Mat2::operator+=(float _scalar)
{
	value[0][0] += _scalar;		value[0][1] += _scalar;
	value[1][0] += _scalar;		value[1][1] += _scalar;
}

void Mat2::operator+=(Mat2 _mat)
{
	value[0][0] += _mat[0][0];		value[0][1] += _mat[0][1];
	value[1][0] += _mat[1][0];		value[1][1] += _mat[1][1];
}

void Mat2::operator-=(float _scalar)
{
	value[0][0] -= _scalar;		value[0][1] -= _scalar;
	value[1][0] -= _scalar;		value[1][1] -= _scalar;
}

void Mat2::operator-=(Mat2 _mat)
{
	value[0][0] -= _mat[0][0];		value[0][1] -= _mat[0][1];
	value[1][0] -= _mat[1][0];		value[1][1] -= _mat[1][1];
}

void Mat2::operator*=(float _scalar)
{
	value[0][0] *= _scalar;		value[0][1] *= _scalar;
	value[1][0] *= _scalar;		value[1][1] *= _scalar;
}

void Mat2::operator*=(Mat2 _mat)
{
	float temp1 = value[0][0];
	float temp2 = value[0][1];
	float temp3 = value[1][0];
	float temp4 = value[1][1];
	value[0][0] = (temp1 * _mat[0][0]) + (temp2 * _mat[1][0]);
	value[0][1] = (temp1 * _mat[0][1]) + (temp2 * _mat[1][1]);
	value[1][0] = (temp3 * _mat[0][0]) + (temp4 * _mat[1][0]);
	value[1][1] = (temp3 * _mat[0][1]) + (temp4 * _mat[1][1]);
}

Vec2 Mat2::Mat2::operator[](int _i) const
{
	if (_i == 0 || _i == 1)
		return { value[_i][0], value[_i][1] };
	return { NAN, NAN }; // TODO Replace
}

void Mat2::Mat2::operator=(float _scalar)
{
	value[0][0] = _scalar;		value[0][1] = _scalar;
	value[1][0] = _scalar;		value[1][1] = _scalar;
}

void Mat2::Mat2::operator=(Mat2 _mat)
{
	value[0][0] = _mat[0][0];		value[0][1] = _mat[0][1];
	value[1][0] = _mat[1][0];		value[1][1] = _mat[1][1];
}

bool Mat2::operator==(Mat2 _mat) const
{
	return	fabsf(value[0][0] - _mat[0][0]) <= Tools::epsilon && fabsf(value[0][1] - _mat[0][1]) <= Tools::epsilon &&
			fabsf(value[1][0] - _mat[1][0]) <= Tools::epsilon && fabsf(value[1][1] - _mat[1][1]) <= Tools::epsilon;
}

bool Mat2::operator!=(Mat2 _mat) const
{
	return	fabsf(value[0][0] - _mat[0][0]) >= Tools::epsilon || fabsf(value[0][1] - _mat[0][1]) >= Tools::epsilon ||
			fabsf(value[1][0] - _mat[1][0]) >= Tools::epsilon || fabsf(value[1][1] - _mat[1][1]) >= Tools::epsilon;
}