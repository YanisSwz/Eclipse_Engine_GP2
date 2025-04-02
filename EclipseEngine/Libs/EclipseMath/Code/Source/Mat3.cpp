#include "Mat3.hpp"
#include "Vec3.hpp"
#include "Tools.hpp"
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Mat3::Mat3(float _scalar)
{
	m_value[0][0] = _scalar;	m_value[0][1] = _scalar;	m_value[0][2] = _scalar;
	m_value[1][0] = _scalar;	m_value[1][1] = _scalar;	m_value[1][2] = _scalar;
	m_value[2][0] = _scalar;	m_value[2][1] = _scalar;	m_value[2][2] = _scalar;
}

Mat3::Mat3(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i)
{
	m_value[0][0] = _a;	m_value[0][1] = _b;	m_value[0][2] = _c;
	m_value[1][0] = _d;	m_value[1][1] = _e;	m_value[1][2] = _f;
	m_value[2][0] = _g;	m_value[2][1] = _h;	m_value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec, float _d, float _e, float _f, float _g, float _h, float _i)
{
	m_value[0][0] = _vec[0];	m_value[0][1] = _vec[1];	m_value[0][2] = _vec[2];
	m_value[1][0] = _d;		m_value[1][1] = _e;		m_value[1][2] = _f;
	m_value[2][0] = _g;		m_value[2][1] = _h;		m_value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec1, Vec3 _vec2, float _g, float _h, float _i)
{
	m_value[0][0] = _vec1[0];		m_value[0][1] = _vec1[1];		m_value[0][2] = _vec1[2];
	m_value[1][0] = _vec2[0];		m_value[1][1] = _vec2[1];		m_value[1][2] = _vec2[2];
	m_value[2][0] = _g;			m_value[2][1] = _h;			m_value[2][2] = _i;
}

Mat3::Mat3(Vec3 _vec1, Vec3 _vec2, Vec3 _vec3)
{
	m_value[0][0] = _vec1[0];		m_value[0][1] = _vec1[1];		m_value[0][2] = _vec1[2];
	m_value[1][0] = _vec2[0];		m_value[1][1] = _vec2[1];		m_value[1][2] = _vec2[2];
	m_value[2][0] = _vec3[0];		m_value[2][1] = _vec3[1];		m_value[2][2] = _vec3[2];
}

Mat3::Mat3(const Mat3& _copy)
{
	m_value[0][0] = _copy[0][0];		m_value[0][1] = _copy[0][1];		m_value[0][2] = _copy[0][2];
	m_value[1][0] = _copy[1][0];		m_value[1][1] = _copy[1][1];		m_value[1][2] = _copy[1][2];
	m_value[2][0] = _copy[2][0];		m_value[2][1] = _copy[2][1];		m_value[2][2] = _copy[2][2];
}


//####################### FUNCTIONS #######################

Vec3 Mat3::Diagonal() const
{
	return { m_value[0][0], m_value[1][1], m_value[2][2] };
}

void Mat3::Transpose()
{
								float temp01 = m_value[0][1]; float temp02 = m_value[0][2];
	float temp10 = m_value[1][0];								float temp12 = m_value[1][2];
	float temp20 = m_value[2][0]; float temp21 = m_value[2][1];	
	
							m_value[0][1] = temp10;	m_value[0][2] = temp20;
	m_value[1][0] = temp01;							m_value[1][2] = temp21;
	m_value[2][0] = temp02;	m_value[2][1] = temp12;
}

float Mat3::Trace() const
{
	return m_value[0][0] + m_value[1][1] + m_value[2][2];
}

void Mat3::Opposite()
{
	m_value[0][0] *= -1;		m_value[0][1] *= -1;		m_value[0][2] *= -1;
	m_value[1][0] *= -1;		m_value[1][1] *= -1;		m_value[1][2] *= -1;
	m_value[2][0] *= -1;		m_value[2][1] *= -1;		m_value[2][2] *= -1;
}

float Mat3::Det() const
{
	float a = m_value[0][0]; float b = m_value[0][1]; float c = m_value[0][2];
	float d = m_value[1][0]; float e = m_value[1][1]; float f = m_value[1][2];
	float g = m_value[2][0]; float h = m_value[2][1]; float i = m_value[2][2];
	return a*e*i - a*f*h + b*f*g - b*d*i + c*d*h - c*e*g;
}

void Mat3::Inverse()
{
	float det = Det();
	det = 1.f / det;
	float a = m_value[0][0]; float b = m_value[0][1]; float c = m_value[0][2];
	float d = m_value[1][0]; float e = m_value[1][1]; float f = m_value[1][2];
	float g = m_value[2][0]; float h = m_value[2][1]; float i = m_value[2][2];

	m_value[0][0] = det * (e*i - f*h);	m_value[0][1] = det * (c*h - b*i);	m_value[0][2] = det * (b*f - c*e);
	m_value[1][0] = det * (f*g - d*i);	m_value[1][1] = det * (a*i - c*g);	m_value[1][2] = det * (c*d - a*f);
	m_value[2][0] = det * (d*h - e*g);	m_value[2][1] = det * (b*g - a*h);	m_value[2][2] = det * (a*e - b*d);
}

void Mat3::SetRotationX(float _theta)
{
	m_value[0][0] = 1.f;	m_value[0][1] = 0.f;			m_value[0][2] = 0.f;
	m_value[1][0] = 0.f;	m_value[1][1] = cosf(_theta);	m_value[1][2] = -sinf(_theta);
	m_value[2][0] = 0.f;	m_value[2][1] = sinf(_theta);	m_value[2][2] = cosf(_theta);
}

void Mat3::SetRotationY(float _theta)
{
	m_value[0][0] = cosf(_theta);		m_value[0][1] = 0.f;	m_value[0][2] = sinf(_theta);
	m_value[1][0] = 0.f;				m_value[1][1] = 1.f;	m_value[1][2] = 0.f;
	m_value[2][0] = -sinf(_theta);	m_value[2][1] = 0.f;	m_value[2][2] = cosf(_theta);
}

void Mat3::SetRotationZ(float _theta)
{
	m_value[0][0] = cosf(_theta);		m_value[0][1] = sinf(_theta);	m_value[0][2] = 0.f;
	m_value[1][0] = -sinf(_theta);	m_value[1][1] = cosf(_theta);	m_value[1][2] = 0.f;
	m_value[2][0] = 0.f;				m_value[2][1] = 0.f;			m_value[2][2] = 1.f;
}

void Mat3::Rotate(Vec3 _theta)
{
	*this = Mat3();
	*this *= RotationX(_theta[0]);
	*this *= RotationY(_theta[1]);
	*this *= RotationZ(_theta[2]);
}

void Mat3::Translate(Vec3 _translate)
{
	m_value[0][0] = 1.f;	m_value[0][1] = 0.f;	m_value[0][2] = _translate[0];
	m_value[1][0] = 0.f;	m_value[1][1] = 1.f;	m_value[1][2] = _translate[1];
	m_value[2][0] = 0.f;	m_value[2][1] = 0.f;	m_value[2][2] = _translate[2];
}

void Mat3::Scale(Vec3 _scale)
{
	m_value[0][0] = _scale[0];	m_value[0][1] = 0.f;			m_value[0][2] = 0.f;
	m_value[1][0] = 0.f;			m_value[1][1] = _scale[1];	m_value[1][2] = 0.f;
	m_value[2][0] = 0.f;			m_value[2][1] = 0.f;			m_value[2][2] = _scale[2];
}

void Mat3::TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	*this = Mat3();
	*this *= Translation(_translate);
	*this *= Rotation(_rotate);
	*this *= Scaling(_scale);
}

void Mat3::Print() const
{
	std::cout << "|" << m_value[0][0] << ", " << m_value[0][1] << ", " << m_value[0][2] << "|" << std::endl
			  << "|" << m_value[1][0] << ", " << m_value[1][1] << ", " << m_value[1][2] << "|" << std::endl
			  << "|" << m_value[2][0] << ", " << m_value[2][1] << ", " << m_value[2][2] << "|" << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec3 Mat3::Diagonal(Mat3 _mat)
{
	return { _mat[0][0] , _mat[1][1], _mat[2][2] };
}

Mat3 Mat3::Transpose(Mat3 _mat)
{
	return { _mat[0][0], _mat[1][0], _mat[2][0],
			 _mat[0][1], _mat[1][1], _mat[2][1],
			 _mat[0][2], _mat[1][2], _mat[2][2] };
}

float Mat3::Trace(Mat3 _mat)
{
	return _mat[0][0] + _mat[1][1] + _mat[2][2];
}

Mat3 Mat3::Opposite(Mat3 _mat)
{
	return { -_mat[0][0], -_mat[0][1], -_mat[0][2],
			 -_mat[1][0], -_mat[1][1], -_mat[1][2],
			 -_mat[2][0], -_mat[2][1],-_mat[2][2]
	};
}

float Mat3::Det(Mat3 _mat)
{
	float a = _mat[0][0]; float b = _mat[0][1]; float c = _mat[0][2];
	float d = _mat[1][0]; float e = _mat[1][1]; float f = _mat[1][2];
	float g = _mat[2][0]; float h = _mat[2][1]; float i = _mat[2][2];
	return a * e * i - a * f * h + b * f * g - b * d * i + c * d * h - c * e * g;
}

Mat3 Mat3::Inverse(Mat3 _mat)
{
	float det = Det(_mat);
	det = 1.f / det;
	float a = _mat[0][0]; float b = _mat[0][1]; float c = _mat[0][2];
	float d = _mat[1][0]; float e = _mat[1][1]; float f = _mat[1][2];
	float g = _mat[2][0]; float h = _mat[2][1]; float i = _mat[2][2];

	return {	det* (e * i - f * h),	det* (c * h - b * i),	det* (b * f - c * e),
				det* (f * g - d * i),	det* (a * i - c * g),	det* (c * d - a * f),
				det* (d * h - e * g),	det* (b * g - a * h),	det* (a * e - b * d)};
}

Mat3 Mat3::RotationX(float _theta)
{
	return { 1.f, 0.f,			0.f,
			 0.f, cosf(_theta),	-sinf(_theta),
			 0.f, sinf(_theta),	cosf(_theta) };
}

Mat3 Mat3::RotationY(float _theta)
{
	return { cosf(_theta),	0.f, sinf(_theta),
			 0.f,			1.f, 0.f,
			 -sinf(_theta),	0.f, cosf(_theta) };
}

Mat3 Mat3::RotationZ(float _theta)
{
	return { cosf(_theta),	sinf(_theta),	0.f,
			 -sinf(_theta),	cosf(_theta),	0.f,
			 0.f,			0.f,			1.f };
}

Mat3 Mat3::Rotation(Vec3 _theta)
{
	Mat3 mat3;
	mat3 *= RotationX(_theta[0]);
	mat3 *= RotationY(_theta[1]);
	mat3 *= RotationZ(_theta[2]);
	return mat3;
}

Mat3 Mat3::Translation(Vec3 _translate)
{
	return { 1.f, 0.f, _translate[0],
			 0.f, 1.f, _translate[1],
			 0.f, 0.f, _translate[2] };
}

Mat3 Mat3::Scaling(Vec3 _scale)
{
	return { _scale[0],	0.f,		0.f,
			 0.f,		_scale[1],	0.f,
			 0.f,		0.f,		_scale[2] };
}

Mat3 Mat3::GetTRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	Mat3 TRS;
	TRS *= Translation(_translate);
	TRS *= Rotation(_rotate);
	TRS *= Scaling(_scale);
	return TRS;
}

void Mat3::Print(Mat3 _mat)
{
	std::cout << "|" << _mat[0][0] << ", " << _mat[0][1] << ", " << _mat[0][2] << "|" << std::endl
			  << "|" << _mat[1][0] << ", " << _mat[1][1] << ", " << _mat[1][2] << "|" << std::endl
			  << "|" << _mat[2][0] << ", " << _mat[2][1] << ", " << _mat[2][2] << "|" << std::endl;
}


//####################### OPERATORS #######################

Mat3 Mat3::operator+(float _scalar) const
{
	return { m_value[0][0] + _scalar, m_value[0][1] + _scalar, m_value[0][2] + _scalar,
			 m_value[1][0] + _scalar, m_value[1][1] + _scalar, m_value[1][2] + _scalar,
			 m_value[2][0] + _scalar, m_value[2][1] + _scalar, m_value[2][2] + _scalar };
}

Mat3 Mat3::operator+(Mat3 _mat) const
{
	return { m_value[0][0] + _mat[0][0], m_value[0][1] + _mat[0][1], m_value[0][2] + _mat[0][2],
			 m_value[1][0] + _mat[1][0], m_value[1][1] + _mat[1][1], m_value[1][2] + _mat[1][2],
			 m_value[2][0] + _mat[2][0], m_value[2][1] + _mat[2][1], m_value[2][2] + _mat[2][2] };
}

Mat3 Mat3::operator-(float _scalar) const
{
	return { m_value[0][0] - _scalar, m_value[0][1] - _scalar, m_value[0][2] - _scalar,
			 m_value[1][0] - _scalar, m_value[1][1] - _scalar, m_value[1][2] - _scalar,
			 m_value[2][0] - _scalar, m_value[2][1] - _scalar, m_value[2][2] - _scalar };
}

Mat3 Mat3::operator-(Mat3 _mat) const
{
	return { m_value[0][0] - _mat[0][0], m_value[0][1] - _mat[0][1], m_value[0][2] - _mat[0][2],
			 m_value[1][0] - _mat[1][0], m_value[1][1] - _mat[1][1], m_value[1][2] - _mat[1][2],
			 m_value[2][0] - _mat[2][0], m_value[2][1] - _mat[2][1], m_value[2][2] - _mat[2][2] };
}

Mat3 Mat3::operator*(float _scalar) const
{
	return { m_value[0][0] * _scalar, m_value[0][1] * _scalar, m_value[0][2] * _scalar,
			 m_value[1][0] * _scalar, m_value[1][1] * _scalar, m_value[1][2] * _scalar,
			 m_value[2][0] * _scalar, m_value[2][1] * _scalar, m_value[2][2] * _scalar };
}

Vec3 Mat3::operator*(Vec3 _vec) const
{
	return { m_value[0][0] * _vec[0] + m_value[0][1] * _vec[1] + m_value[0][2] * _vec[2],
			 m_value[1][0] * _vec[0] + m_value[1][1] * _vec[1] + m_value[1][2] * _vec[2],
			 m_value[2][0] * _vec[0] + m_value[2][1] * _vec[1] + m_value[2][2] * _vec[2] };
}

Mat3 Mat3::operator*(Mat3 _mat) const
{
	return { m_value[0][0] * _mat[0][0] + m_value[0][1] * _mat[1][0] + m_value[0][2] * _mat[2][0],
			 m_value[0][0] * _mat[0][1] + m_value[0][1] * _mat[1][1] + m_value[0][2] * _mat[2][1],
			 m_value[0][0] * _mat[0][2] + m_value[0][1] * _mat[1][2] + m_value[0][2] * _mat[2][2],
			 m_value[1][0] * _mat[0][0] + m_value[1][1] * _mat[1][0] + m_value[1][2] * _mat[2][0],
			 m_value[1][0] * _mat[0][1] + m_value[1][1] * _mat[1][1] + m_value[1][2] * _mat[2][1],
			 m_value[1][0] * _mat[0][2] + m_value[1][1] * _mat[1][2] + m_value[1][2] * _mat[2][2],
			 m_value[2][0] * _mat[0][0] + m_value[2][1] * _mat[1][0] + m_value[2][2] * _mat[2][0],
			 m_value[2][0] * _mat[0][1] + m_value[2][1] * _mat[1][1] + m_value[2][2] * _mat[2][1],
			 m_value[2][0] * _mat[0][2] + m_value[2][1] * _mat[1][2] + m_value[2][2] * _mat[2][2] };
}

void Mat3::operator+=(float _scalar)
{
	m_value[0][0] += _scalar;		m_value[0][1] += _scalar;		m_value[0][2] += _scalar;
	m_value[1][0] += _scalar;		m_value[1][1] += _scalar;		m_value[1][2] += _scalar;
	m_value[2][0] += _scalar;		m_value[2][1] += _scalar;		m_value[2][2] += _scalar;
}

void Mat3::operator+=(Mat3 _mat)
{
	m_value[0][0] += _mat[0][0];		m_value[0][1] += _mat[0][1];		m_value[0][2] += _mat[0][2];
	m_value[1][0] += _mat[1][0];		m_value[1][1] += _mat[1][1];		m_value[1][2] += _mat[1][2];
	m_value[2][0] += _mat[2][0];		m_value[2][1] += _mat[2][1];		m_value[2][2] += _mat[2][2];
}

void Mat3::operator-=(float _scalar)
{
	m_value[0][0] -= _scalar;		m_value[0][1] -= _scalar;		m_value[0][2] -= _scalar;
	m_value[1][0] -= _scalar;		m_value[1][1] -= _scalar;		m_value[1][2] -= _scalar;
	m_value[2][0] -= _scalar;		m_value[2][1] -= _scalar;		m_value[2][2] -= _scalar;
}

void Mat3::operator-=(Mat3 _mat)
{
	m_value[0][0] -= _mat[0][0];		m_value[0][1] -= _mat[0][1];		m_value[0][2] -= _mat[0][2];
	m_value[1][0] -= _mat[1][0];		m_value[1][1] -= _mat[1][1];		m_value[1][2] -= _mat[1][2];
	m_value[2][0] -= _mat[2][0];		m_value[2][1] -= _mat[2][1];		m_value[2][2] -= _mat[2][2];
}

void Mat3::operator*=(float _scalar)
{
	m_value[0][0] *= _scalar;		m_value[0][1] *= _scalar;		m_value[0][2] *= _scalar;
	m_value[1][0] *= _scalar;		m_value[1][1] *= _scalar;		m_value[1][2] *= _scalar;
	m_value[2][0] *= _scalar;		m_value[2][1] *= _scalar;		m_value[2][2] *= _scalar;
}

void Mat3::operator*=(Mat3 _mat)
{
	float temp00 = m_value[0][0]; float temp01 = m_value[0][1]; float temp02 = m_value[0][2];
	float temp10 = m_value[1][0]; float temp11 = m_value[1][1]; float temp12 = m_value[1][2];
	float temp20 = m_value[2][0]; float temp21 = m_value[2][1]; float temp22 = m_value[2][2];

	m_value[0][0] *= temp00 * _mat[0][0] + temp01 * _mat[1][0] + temp02 * _mat[2][0];
	m_value[0][1] *= temp00 * _mat[0][1] + temp01 * _mat[1][1] + temp02 * _mat[2][1];
	m_value[0][2] *= temp00 * _mat[0][2] + temp01 * _mat[1][2] + temp02 * _mat[2][2];
	m_value[1][0] *= temp10 * _mat[0][0] + temp11 * _mat[1][0] + temp12 * _mat[2][0];
	m_value[1][1] *= temp10 * _mat[0][1] + temp11 * _mat[1][1] + temp12 * _mat[2][1];
	m_value[1][2] *= temp10 * _mat[0][2] + temp11 * _mat[1][2] + temp12 * _mat[2][2];
	m_value[2][0] *= temp20 * _mat[0][0] + temp21 * _mat[1][0] + temp22 * _mat[2][0];
	m_value[2][1] *= temp20 * _mat[0][1] + temp21 * _mat[1][1] + temp22 * _mat[2][1];
	m_value[2][2] *= temp20 * _mat[0][2] + temp21 * _mat[1][2] + temp22 * _mat[2][2];
}

Vec3 Mat3::operator[](int _i) const
{
	if (_i == 0 || _i == 1 || _i == 2)
		return { m_value[_i][0], m_value[_i][1], m_value[_i][2] };
	return { NAN, NAN, NAN }; // TODO Replace
}

void Mat3::operator=(float _scalar)
{
	m_value[0][0] = _scalar;		m_value[0][1] = _scalar;		m_value[0][2] = _scalar;
	m_value[1][0] = _scalar;		m_value[1][1] = _scalar;		m_value[1][2] = _scalar;
	m_value[2][0] = _scalar;		m_value[2][1] = _scalar;		m_value[2][2] = _scalar;
}

void Mat3::operator=(Mat3 _mat)
{
	m_value[0][0] = _mat[0][0];		m_value[0][1] = _mat[0][1];		m_value[0][2] = _mat[0][2];
	m_value[1][0] = _mat[1][0];		m_value[1][1] = _mat[1][1];		m_value[1][2] = _mat[1][2];
	m_value[2][0] = _mat[2][0];		m_value[2][1] = _mat[2][1];		m_value[2][2] = _mat[2][2];
}

bool Mat3::operator==(Mat3 _mat) const
{
	return	fabs(m_value[0][0] - _mat[0][0]) <= Tools::epsilon && fabs(m_value[0][1] - _mat[0][1]) <= Tools::epsilon && fabs(m_value[0][2] - _mat[0][2]) <= Tools::epsilon &&
			fabs(m_value[1][0] - _mat[1][0]) <= Tools::epsilon && fabs(m_value[1][1] - _mat[1][1]) <= Tools::epsilon && fabs(m_value[1][2] - _mat[1][2]) <= Tools::epsilon &&
			fabs(m_value[2][0] - _mat[2][0]) <= Tools::epsilon && fabs(m_value[2][1] - _mat[2][1]) <= Tools::epsilon && fabs(m_value[2][2] - _mat[2][2]) <= Tools::epsilon;
}

bool Mat3::operator!=(Mat3 _mat) const
{
	return	fabs(m_value[0][0] - _mat[0][0]) >= Tools::epsilon || fabs(m_value[0][1] - _mat[0][1]) >= Tools::epsilon || fabs(m_value[0][2] - _mat[0][2]) >= Tools::epsilon ||
			fabs(m_value[1][0] - _mat[1][0]) >= Tools::epsilon || fabs(m_value[1][1] - _mat[1][1]) >= Tools::epsilon || fabs(m_value[1][2] - _mat[1][2]) >= Tools::epsilon ||
			fabs(m_value[2][0] - _mat[2][0]) >= Tools::epsilon || fabs(m_value[2][1] - _mat[2][1]) >= Tools::epsilon || fabs(m_value[2][2] - _mat[2][2]) >= Tools::epsilon;
}