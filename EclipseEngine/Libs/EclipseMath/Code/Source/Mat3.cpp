#include "Mat3.hpp"
#include "Vec3.hpp"
#include "Tools.hpp"
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Mat3::Mat3(float _scalar)
{
	value[0][0] = _scalar;	value[0][1] = _scalar;	value[0][2] = _scalar;
	value[1][0] = _scalar;	value[1][1] = _scalar;	value[1][2] = _scalar;
	value[2][0] = _scalar;	value[2][1] = _scalar;	value[2][2] = _scalar;
}

Mat3::Mat3(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i)
{
	value[0][0] = _a;	value[0][1] = _b;	value[0][2] = _c;
	value[1][0] = _d;	value[1][1] = _e;	value[1][2] = _f;
	value[2][0] = _g;	value[2][1] = _h;	value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec, float _d, float _e, float _f, float _g, float _h, float _i)
{
	value[0][0] = _vec[0];	value[0][1] = _vec[1];	value[0][2] = _vec[2];
	value[1][0] = _d;		value[1][1] = _e;		value[1][2] = _f;
	value[2][0] = _g;		value[2][1] = _h;		value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec1, Vec3 _vec2, float _g, float _h, float _i)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];		value[0][2] = _vec1[2];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];		value[1][2] = _vec2[2];
	value[2][0] = _g;			value[2][1] = _h;			value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec1, Vec3 _vec2, Vec3 _vec3)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];		value[0][2] = _vec1[2];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];		value[1][2] = _vec2[2];
	value[2][0] = _vec3[0];		value[2][1] = _vec3[1];		value[2][2] = _vec3[2];
}

Mat3::Mat3(const Mat3& _copy)
{
	value[0][0] = _copy[0][0];		value[0][1] = _copy[0][1];		value[0][2] = _copy[0][2];
	value[1][0] = _copy[1][0];		value[1][1] = _copy[1][1];		value[1][2] = _copy[1][2];
	value[2][0] = _copy[2][0];		value[2][1] = _copy[2][1];		value[2][2] = _copy[2][2];
}


//####################### FUNCTIONS #######################

Vec3 Mat3::Diagonal() const
{
	return { value[0][0], value[1][1], value[2][2] };
}

void Mat3::Transpose()
{
								float temp01 = value[0][1]; float temp02 = value[0][2];
	float temp10 = value[1][0];								float temp12 = value[1][2];
	float temp20 = value[2][0]; float temp21 = value[2][1];	
	
							value[0][1] = temp10;	value[0][2] = temp20;
	value[1][0] = temp01;							value[1][2] = temp21;
	value[2][0] = temp02;	value[2][1] = temp12;
}

float Mat3::Trace() const
{
	return value[0][0] + value[1][1] + value[2][2];
}

void Mat3::Opposite()
{
	value[0][0] *= -1;		value[0][1] *= -1;		value[0][2] *= -1;
	value[1][0] *= -1;		value[1][1] *= -1;		value[1][2] *= -1;
	value[2][0] *= -1;		value[2][1] *= -1;		value[2][2] *= -1;
}

float Mat3::Det() const
{
	float a = value[0][0]; float b = value[0][1]; float c = value[0][2];
	float d = value[1][0]; float e = value[1][1]; float f = value[1][2];
	float g = value[2][0]; float h = value[2][1]; float i = value[2][2];
	return a*e*i - a*f*h + b*f*g - b*d*i + c*d*h - c*e*g;
}

void Mat3::Inverse()
{
	float det = Det();
	det = 1.f / det;
	float a = value[0][0]; float b = value[0][1]; float c = value[0][2];
	float d = value[1][0]; float e = value[1][1]; float f = value[1][2];
	float g = value[2][0]; float h = value[2][1]; float i = value[2][2];

	value[0][0] = det * (e*i - f*h);	value[0][1] = det * (c*h - b*i);	value[0][2] = det * (b*f - c*e);
	value[1][0] = det * (f*g - d*i);	value[1][1] = det * (a*i - c*g);	value[1][2] = det * (c*d - a*f);
	value[2][0] = det * (d*h - e*g);	value[2][1] = det * (b*g - a*h);	value[2][2] = det * (a*e - b*d);
}

void Mat3::RotateX(float _theta)
{
	value[0][0] = 1.f;	value[0][1] = 0.f;			value[0][2] = 0.f;
	value[1][0] = 0.f;	value[1][1] = cosf(_theta);	value[1][2] = -sinf(_theta);
	value[2][0] = 0.f;	value[2][1] = sinf(_theta);	value[2][2] = cosf(_theta);
}

void Mat3::RotateY(float _theta)
{
	value[0][0] = cosf(_theta);		value[0][1] = 0.f;	value[0][2] = sinf(_theta);
	value[1][0] = 0.f;				value[1][1] = 1.f;	value[1][2] = 0.f;
	value[2][0] = -sinf(_theta);	value[2][1] = 0.f;	value[2][2] = cosf(_theta);
}

void Mat3::RotateZ(float _theta)
{
	value[0][0] = cosf(_theta);		value[0][1] = sinf(_theta);	value[0][2] = 0.f;
	value[1][0] = -sinf(_theta);	value[1][1] = cosf(_theta);	value[1][2] = 0.f;
	value[2][0] = 0.f;				value[2][1] = 0.f;			value[2][2] = 1.f;
}

void Mat3::Rotate(Vec3 _theta)
{
	*this = Mat3();
	*this *= s_RotateX(_theta[0]);
	*this *= s_RotateY(_theta[1]);
	*this *= s_RotateZ(_theta[2]);
}

void Mat3::Translate(Vec3 _translate)
{
	value[0][0] = 1.f;	value[0][1] = 0.f;	value[0][2] = _translate[0];
	value[1][0] = 0.f;	value[1][1] = 1.f;	value[1][2] = _translate[1];
	value[2][0] = 0.f;	value[2][1] = 0.f;	value[2][2] = _translate[2];
}

void Mat3::Scale(Vec3 _scale)
{
	value[0][0] = _scale[0];	value[0][1] = 0.f;			value[0][2] = 0.f;
	value[1][0] = 0.f;			value[1][1] = _scale[1];	value[1][2] = 0.f;
	value[2][0] = 0.f;			value[2][1] = 0.f;			value[2][2] = _scale[2];
}

void Mat3::TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	*this = Mat3();
	*this *= s_Translate(_translate);
	*this *= s_Rotate(_rotate);
	*this *= s_Scale(_scale);
}

void Mat3::Print() const
{
	std::cout << "|" << value[0][0] << ", " << value[0][1] << ", " << value[0][2] << "|" << std::endl
			  << "|" << value[1][0] << ", " << value[1][1] << ", " << value[1][2] << "|" << std::endl
			  << "|" << value[2][0] << ", " << value[2][1] << ", " << value[2][2] << "|" << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec3 Mat3::s_Diagonal(Mat3 _mat)
{
	return { _mat[0][0] , _mat[1][1], _mat[2][2] };
}

Mat3 Mat3::s_Transpose(Mat3 _mat)
{
	return { _mat[0][0], _mat[1][0], _mat[2][0],
			 _mat[0][1], _mat[1][1], _mat[2][1],
			 _mat[0][2], _mat[1][2], _mat[2][2] };
}

float Mat3::s_Trace(Mat3 _mat)
{
	return _mat[0][0] + _mat[1][1] + _mat[2][2];
}

Mat3 Mat3::s_Opposite(Mat3 _mat)
{
	return { -_mat[0][0], -_mat[0][1], -_mat[0][2],
			 -_mat[1][0], -_mat[1][1], -_mat[1][2],
			 -_mat[2][0], -_mat[2][1],-_mat[2][2]
	};
}

float Mat3::s_Det(Mat3 _mat)
{
	float a = _mat[0][0]; float b = _mat[0][1]; float c = _mat[0][2];
	float d = _mat[1][0]; float e = _mat[1][1]; float f = _mat[1][2];
	float g = _mat[2][0]; float h = _mat[2][1]; float i = _mat[2][2];
	return a * e * i - a * f * h + b * f * g - b * d * i + c * d * h - c * e * g;
}

Mat3 Mat3::s_Inverse(Mat3 _mat)
{
	float det = s_Det(_mat);
	det = 1.f / det;
	float a = _mat[0][0]; float b = _mat[0][1]; float c = _mat[0][2];
	float d = _mat[1][0]; float e = _mat[1][1]; float f = _mat[1][2];
	float g = _mat[2][0]; float h = _mat[2][1]; float i = _mat[2][2];

	return {	det* (e * i - f * h),	det* (c * h - b * i),	det* (b * f - c * e),
				det* (f * g - d * i),	det* (a * i - c * g),	det* (c * d - a * f),
				det* (d * h - e * g),	det* (b * g - a * h),	det* (a * e - b * d)};
}

Mat3 Mat3::s_RotateX(float _theta)
{
	return { 1.f, 0.f,			0.f,
			 0.f, cosf(_theta),	-sinf(_theta),
			 0.f, sinf(_theta),	cosf(_theta) };
}

Mat3 Mat3::s_RotateY(float _theta)
{
	return { cosf(_theta),	0.f, sinf(_theta),
			 0.f,			1.f, 0.f,
			 -sinf(_theta),	0.f, cosf(_theta) };
}

Mat3 Mat3::s_RotateZ(float _theta)
{
	return { cosf(_theta),	sinf(_theta),	0.f,
			 -sinf(_theta),	cosf(_theta),	0.f,
			 0.f,			0.f,			1.f };
}

Mat3 Mat3::s_Rotate(Vec3 _theta)
{
	Mat3 mat3;
	mat3 *= s_RotateX(_theta[0]);
	mat3 *= s_RotateY(_theta[1]);
	mat3 *= s_RotateZ(_theta[2]);
	return mat3;
}

Mat3 Mat3::s_Translate(Vec3 _translate)
{
	return { 1.f, 0.f, _translate[0],
			 0.f, 1.f, _translate[1],
			 0.f, 0.f, _translate[2] };
}

Mat3 Mat3::s_Scale(Vec3 _scale)
{
	return { _scale[0],	0.f,		0.f,
			 0.f,		_scale[1],	0.f,
			 0.f,		0.f,		_scale[2] };
}

Mat3 Mat3::s_TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	Mat3 TRS;
	TRS *= s_Translate(_translate);
	TRS *= s_Rotate(_rotate);
	TRS *= s_Scale(_scale);
	return TRS;
}

void Mat3::s_Print(Mat3 _mat)
{
	std::cout << "|" << _mat[0][0] << ", " << _mat[0][1] << ", " << _mat[0][2] << "|" << std::endl
			  << "|" << _mat[1][0] << ", " << _mat[1][1] << ", " << _mat[1][2] << "|" << std::endl
			  << "|" << _mat[2][0] << ", " << _mat[2][1] << ", " << _mat[2][2] << "|" << std::endl;
}


//####################### OPERATORS #######################

Mat3 Mat3::operator+(float _scalar) const
{
	return { value[0][0] + _scalar, value[0][1] + _scalar, value[0][2] + _scalar,
			 value[1][0] + _scalar, value[1][1] + _scalar, value[1][2] + _scalar,
			 value[2][0] + _scalar, value[2][1] + _scalar, value[2][2] + _scalar };
}

Mat3 Mat3::operator+(Mat3 _mat) const
{
	return { value[0][0] + _mat[0][0], value[0][1] + _mat[0][1], value[0][2] + _mat[0][2],
			 value[1][0] + _mat[1][0], value[1][1] + _mat[1][1], value[1][2] + _mat[1][2],
			 value[2][0] + _mat[2][0], value[2][1] + _mat[2][1], value[2][2] + _mat[2][2] };
}

Mat3 Mat3::operator-(float _scalar) const
{
	return { value[0][0] - _scalar, value[0][1] - _scalar, value[0][2] - _scalar,
			 value[1][0] - _scalar, value[1][1] - _scalar, value[1][2] - _scalar,
			 value[2][0] - _scalar, value[2][1] - _scalar, value[2][2] - _scalar };
}

Mat3 Mat3::operator-(Mat3 _mat) const
{
	return { value[0][0] - _mat[0][0], value[0][1] - _mat[0][1], value[0][2] - _mat[0][2],
			 value[1][0] - _mat[1][0], value[1][1] - _mat[1][1], value[1][2] - _mat[1][2],
			 value[2][0] - _mat[2][0], value[2][1] - _mat[2][1], value[2][2] - _mat[2][2] };
}

Mat3 Mat3::operator*(float _scalar) const
{
	return { value[0][0] * _scalar, value[0][1] * _scalar, value[0][2] * _scalar,
			 value[1][0] * _scalar, value[1][1] * _scalar, value[1][2] * _scalar,
			 value[2][0] * _scalar, value[2][1] * _scalar, value[2][2] * _scalar };
}

Vec3 Mat3::operator*(Vec3 _vec) const
{
	return { value[0][0] * _vec[0] + value[0][1] * _vec[1] + value[0][2] * _vec[2],
			 value[1][0] * _vec[0] + value[1][1] * _vec[1] + value[1][2] * _vec[2],
			 value[2][0] * _vec[0] + value[2][1] * _vec[1] + value[2][2] * _vec[2] };
}

Mat3 Mat3::operator*(Mat3 _mat) const
{
	return { value[0][0] * _mat[0][0] + value[0][1] * _mat[1][0] + value[0][2] * _mat[2][0],
			 value[0][0] * _mat[0][1] + value[0][1] * _mat[1][1] + value[0][2] * _mat[2][1],
			 value[0][0] * _mat[0][2] + value[0][1] * _mat[1][2] + value[0][2] * _mat[2][2],
			 value[1][0] * _mat[0][0] + value[1][1] * _mat[1][0] + value[1][2] * _mat[2][0],
			 value[1][0] * _mat[0][1] + value[1][1] * _mat[1][1] + value[1][2] * _mat[2][1],
			 value[1][0] * _mat[0][2] + value[1][1] * _mat[1][2] + value[1][2] * _mat[2][2],
			 value[2][0] * _mat[0][0] + value[2][1] * _mat[1][0] + value[2][2] * _mat[2][0],
			 value[2][0] * _mat[0][1] + value[2][1] * _mat[1][1] + value[2][2] * _mat[2][1],
			 value[2][0] * _mat[0][2] + value[2][1] * _mat[1][2] + value[2][2] * _mat[2][2] };
}

void Mat3::operator+=(float _scalar)
{
	value[0][0] += _scalar;		value[0][1] += _scalar;		value[0][2] += _scalar;
	value[1][0] += _scalar;		value[1][1] += _scalar;		value[1][2] += _scalar;
	value[2][0] += _scalar;		value[2][1] += _scalar;		value[2][2] += _scalar;
}

void Mat3::operator+=(Mat3 _mat)
{
	value[0][0] += _mat[0][0];		value[0][1] += _mat[0][1];		value[0][2] += _mat[0][2];
	value[1][0] += _mat[1][0];		value[1][1] += _mat[1][1];		value[1][2] += _mat[1][2];
	value[2][0] += _mat[2][0];		value[2][1] += _mat[2][1];		value[2][2] += _mat[2][2];
}

void Mat3::operator-=(float _scalar)
{
	value[0][0] -= _scalar;		value[0][1] -= _scalar;		value[0][2] -= _scalar;
	value[1][0] -= _scalar;		value[1][1] -= _scalar;		value[1][2] -= _scalar;
	value[2][0] -= _scalar;		value[2][1] -= _scalar;		value[2][2] -= _scalar;
}

void Mat3::operator-=(Mat3 _mat)
{
	value[0][0] -= _mat[0][0];		value[0][1] -= _mat[0][1];		value[0][2] -= _mat[0][2];
	value[1][0] -= _mat[1][0];		value[1][1] -= _mat[1][1];		value[1][2] -= _mat[1][2];
	value[2][0] -= _mat[2][0];		value[2][1] -= _mat[2][1];		value[2][2] -= _mat[2][2];
}

void Mat3::operator*=(float _scalar)
{
	value[0][0] *= _scalar;		value[0][1] *= _scalar;		value[0][2] *= _scalar;
	value[1][0] *= _scalar;		value[1][1] *= _scalar;		value[1][2] *= _scalar;
	value[2][0] *= _scalar;		value[2][1] *= _scalar;		value[2][2] *= _scalar;
}

void Mat3::operator*=(Mat3 _mat)
{
	float temp00 = value[0][0]; float temp01 = value[0][1]; float temp02 = value[0][2];
	float temp10 = value[1][0]; float temp11 = value[1][1]; float temp12 = value[1][2];
	float temp20 = value[2][0]; float temp21 = value[2][1]; float temp22 = value[2][2];

	value[0][0] *= temp00 * _mat[0][0] + temp01 * _mat[1][0] + temp02 * _mat[2][0];
	value[0][1] *= temp00 * _mat[0][1] + temp01 * _mat[1][1] + temp02 * _mat[2][1];
	value[0][2] *= temp00 * _mat[0][2] + temp01 * _mat[1][2] + temp02 * _mat[2][2];
	value[1][0] *= temp10 * _mat[0][0] + temp11 * _mat[1][0] + temp12 * _mat[2][0];
	value[1][1] *= temp10 * _mat[0][1] + temp11 * _mat[1][1] + temp12 * _mat[2][1];
	value[1][2] *= temp10 * _mat[0][2] + temp11 * _mat[1][2] + temp12 * _mat[2][2];
	value[2][0] *= temp20 * _mat[0][0] + temp21 * _mat[1][0] + temp22 * _mat[2][0];
	value[2][1] *= temp20 * _mat[0][1] + temp21 * _mat[1][1] + temp22 * _mat[2][1];
	value[2][2] *= temp20 * _mat[0][2] + temp21 * _mat[1][2] + temp22 * _mat[2][2];
}

Vec3 Mat3::operator[](int _i) const
{
	if (_i == 0 || _i == 1 || _i == 2)
		return { value[_i][0], value[_i][1], value[_i][2] };
	return { NAN, NAN, NAN }; // TODO Replace
}

void Mat3::operator=(float _scalar)
{
	value[0][0] = _scalar;		value[0][1] = _scalar;		value[0][2] = _scalar;
	value[1][0] = _scalar;		value[1][1] = _scalar;		value[1][2] = _scalar;
	value[2][0] = _scalar;		value[2][1] = _scalar;		value[2][2] = _scalar;
}

void Mat3::operator=(Mat3 _mat)
{
	value[0][0] = _mat[0][0];		value[0][1] = _mat[0][1];		value[0][2] = _mat[0][2];
	value[1][0] = _mat[1][0];		value[1][1] = _mat[1][1];		value[1][2] = _mat[1][2];
	value[2][0] = _mat[2][0];		value[2][1] = _mat[2][1];		value[2][2] = _mat[2][2];
}

bool Mat3::operator==(Mat3 _mat) const
{
	return	fabs(value[0][0] - _mat[0][0]) <= Tools::epsilon && fabs(value[0][1] - _mat[0][1]) <= Tools::epsilon && fabs(value[0][2] - _mat[0][2]) <= Tools::epsilon &&
			fabs(value[1][0] - _mat[1][0]) <= Tools::epsilon && fabs(value[1][1] - _mat[1][1]) <= Tools::epsilon && fabs(value[1][2] - _mat[1][2]) <= Tools::epsilon &&
			fabs(value[2][0] - _mat[2][0]) <= Tools::epsilon && fabs(value[2][1] - _mat[2][1]) <= Tools::epsilon && fabs(value[2][2] - _mat[2][2]) <= Tools::epsilon;
}

bool Mat3::operator!=(Mat3 _mat) const
{
	return	fabs(value[0][0] - _mat[0][0]) >= Tools::epsilon || fabs(value[0][1] - _mat[0][1]) >= Tools::epsilon || fabs(value[0][2] - _mat[0][2]) >= Tools::epsilon ||
			fabs(value[1][0] - _mat[1][0]) >= Tools::epsilon || fabs(value[1][1] - _mat[1][1]) >= Tools::epsilon || fabs(value[1][2] - _mat[1][2]) >= Tools::epsilon ||
			fabs(value[2][0] - _mat[2][0]) >= Tools::epsilon || fabs(value[2][1] - _mat[2][1]) >= Tools::epsilon || fabs(value[2][2] - _mat[2][2]) >= Tools::epsilon;
}