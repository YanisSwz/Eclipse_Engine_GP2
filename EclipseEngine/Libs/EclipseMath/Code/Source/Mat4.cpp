#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Tools.hpp"
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Mat4::Mat4(float _scalar)
{
	m_value[0][0] = _scalar;		m_value[0][1] = _scalar;		m_value[0][2] = _scalar;		m_value[0][3] = _scalar;
	m_value[1][0] = _scalar;		m_value[1][1] = _scalar;		m_value[1][2] = _scalar;		m_value[1][3] = _scalar;
	m_value[2][0] = _scalar;		m_value[2][1] = _scalar;		m_value[2][2] = _scalar;		m_value[2][3] = _scalar;
	m_value[3][0] = _scalar;		m_value[3][1] = _scalar;		m_value[3][2] = _scalar;		m_value[3][3] = _scalar;
}

Mat4::Mat4(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	m_value[0][0] = _a;		m_value[0][1] = _b;		m_value[0][2] = _c;		m_value[0][3] = _d;
	m_value[1][0] = _e;		m_value[1][1] = _f;		m_value[1][2] = _g;		m_value[1][3] = _h;
	m_value[2][0] = _i;		m_value[2][1] = _j;		m_value[2][2] = _k;		m_value[2][3] = _l;
	m_value[3][0] = _m;		m_value[3][1] = _n;		m_value[3][2] = _o;		m_value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	m_value[0][0] = _vec[0];		m_value[0][1] = _vec[1];		m_value[0][2] = _vec[2];		m_value[0][3] = _vec[3];
	m_value[1][0] = _e;			m_value[1][1] = _f;			m_value[1][2] = _g;			m_value[1][3] = _h;
	m_value[2][0] = _i;			m_value[2][1] = _j;			m_value[2][2] = _k;			m_value[2][3] = _l;
	m_value[3][0] = _m;			m_value[3][1] = _n;			m_value[3][2] = _o;			m_value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	m_value[0][0] = _vec1[0];		m_value[0][1] = _vec1[1];		m_value[0][2] = _vec1[2];		m_value[0][3] = _vec1[3];
	m_value[1][0] = _vec2[0];		m_value[1][1] = _vec2[1];		m_value[1][2] = _vec2[2];		m_value[1][3] = _vec2[3];
	m_value[2][0] = _i;			m_value[2][1] = _j;			m_value[2][2] = _k;			m_value[2][3] = _l;
	m_value[3][0] = _m;			m_value[3][1] = _n;			m_value[3][2] = _o;			m_value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, float _m, float _n, float _o, float _p)
{
	m_value[0][0] = _vec1[0];		m_value[0][1] = _vec1[1];		m_value[0][2] = _vec1[2];		m_value[0][3] = _vec1[3];
	m_value[1][0] = _vec2[0];		m_value[1][1] = _vec2[1];		m_value[1][2] = _vec2[2];		m_value[1][3] = _vec2[3];
	m_value[2][0] = _vec3[0];		m_value[2][1] = _vec3[1];		m_value[2][2] = _vec3[2];		m_value[2][3] = _vec3[3];
	m_value[3][0] = _m;			m_value[3][1] = _n;			m_value[3][2] = _o;			m_value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, Vec4 _vec4)
{
	m_value[0][0] = _vec1[0];		m_value[0][1] = _vec1[1];		m_value[0][2] = _vec1[2];		m_value[0][3] = _vec1[3];
	m_value[1][0] = _vec2[0];		m_value[1][1] = _vec2[1];		m_value[1][2] = _vec2[2];		m_value[1][3] = _vec2[3];
	m_value[2][0] = _vec3[0];		m_value[2][1] = _vec3[1];		m_value[2][2] = _vec3[2];		m_value[2][3] = _vec3[3];
	m_value[3][0] = _vec4[0];		m_value[3][1] = _vec4[1];		m_value[3][2] = _vec4[2];		m_value[3][3] = _vec4[3];
}

Mat4::Mat4(const Mat4& _copy)
{
	m_value[0][0] = _copy[0][0];		m_value[0][1] = _copy[0][1];		m_value[0][2] = _copy[0][2];		m_value[0][3] = _copy[0][3];
	m_value[1][0] = _copy[1][0];		m_value[1][1] = _copy[1][1];		m_value[1][2] = _copy[1][2];		m_value[1][3] = _copy[1][3];
	m_value[2][0] = _copy[2][0];		m_value[2][1] = _copy[2][1];		m_value[2][2] = _copy[2][2];		m_value[2][3] = _copy[2][3];
	m_value[3][0] = _copy[3][0];		m_value[3][1] = _copy[3][1];		m_value[3][2] = _copy[3][2];		m_value[3][3] = _copy[3][3];
}


//####################### FUNCTIONS #######################

float& Mat4::GetValues()
{
	return *m_value[0];
}

const float* Mat4::GetValuesPointer()
{
	return &m_value[0][0];
}

Vec4 Mat4::Diagonal() const
{
	return { m_value[0][0], m_value[1][1], m_value[2][2], m_value[3][3] };
}

void Mat4::Transpose()
{
	float temp01 = m_value[0][1]; float temp02 = m_value[0][2]; float temp03 = m_value[0][3];
	float temp10 = m_value[1][0];								float temp12 = m_value[1][2]; float temp13 = m_value[1][3];
	float temp20 = m_value[2][0]; float temp21 = m_value[2][1];								float temp23 = m_value[2][3];
	float temp30 = m_value[3][0]; float temp31 = m_value[3][1]; float temp32 = m_value[3][2];

	m_value[0][1] = temp10;	m_value[0][2] = temp20;	m_value[0][3] = temp30;
	m_value[1][0] = temp01;							m_value[1][2] = temp21;	m_value[1][3] = temp31;
	m_value[2][0] = temp02;	m_value[2][1] = temp12;							m_value[2][3] = temp32;
	m_value[3][0] = temp03;	m_value[3][1] = temp13;	m_value[3][2] = temp23;
}

float Mat4::Trace() const
{
	return m_value[0][0] + m_value[1][1] + m_value[2][2] + m_value[3][3];
}

void Mat4::Opposite()
{
	m_value[0][0] *= -1; m_value[0][1] *= -1; m_value[0][2] *= -1; m_value[0][3] *= -1;
	m_value[1][0] *= -1; m_value[1][1] *= -1; m_value[1][2] *= -1; m_value[1][3] *= -1;
	m_value[2][0] *= -1; m_value[2][1] *= -1; m_value[2][2] *= -1; m_value[2][3] *= -1;
	m_value[3][0] *= -1; m_value[3][1] *= -1; m_value[3][2] *= -1; m_value[3][3] *= -1;
}

float Mat4::Det() const
{
	float a = m_value[0][0]; float b = m_value[0][1]; float c = m_value[0][2]; float d = m_value[0][3];
	float e = m_value[1][0]; float f = m_value[1][1]; float g = m_value[1][2]; float h = m_value[1][3];
	float i = m_value[2][0]; float j = m_value[2][1]; float k = m_value[2][2]; float l = m_value[2][3];
	float m = m_value[3][0]; float n = m_value[3][1]; float o = m_value[3][2]; float p = m_value[3][3];

	float temp1 = a * (f*k*p - f*l*o - g*j*p + g*l*n + h*j*o - h*k*n);
	float temp2 = -b * (e*k*p - e*l*o - g*i*p + g*l*m + h*i*o - h*k*m);
	float temp3 = c * (e*j*p - e*l*n - f*i*p + f*l*m + h*i*n - h*j*m);
	float temp4 = -d * (e*j*o - e*k*n - f*i*o + f*k*m + g*i*n - g*j*m);

	return temp1 + temp2 + temp3 + temp4;
}

void Mat4::Inverse()
{
	Mat4 inv;
	inv.m_value[0][0] = m_value[1][1] * m_value[2][2] * m_value[3][3] -
		m_value[1][1] * m_value[2][3] * m_value[3][2] -
		m_value[2][1] * m_value[1][2] * m_value[3][3] +
		m_value[2][1] * m_value[1][3] * m_value[3][2] +
		m_value[3][1] * m_value[1][2] * m_value[2][3] -
		m_value[3][1] * m_value[1][3] * m_value[2][2];

	inv.m_value[1][0] = -m_value[1][0] * m_value[2][2] * m_value[3][3] +
		m_value[1][0] * m_value[2][3] * m_value[3][2] +
		m_value[2][0] * m_value[1][2] * m_value[3][3] -
		m_value[2][0] * m_value[1][3] * m_value[3][2] -
		m_value[3][0] * m_value[1][2] * m_value[2][3] +
		m_value[3][0] * m_value[1][3] * m_value[2][2];

	inv.m_value[2][0] = m_value[1][0] * m_value[2][1] * m_value[3][3] -
		m_value[1][0] * m_value[2][3] * m_value[3][1] -
		m_value[2][0] * m_value[1][1] * m_value[3][3] +
		m_value[2][0] * m_value[1][3] * m_value[3][1] +
		m_value[3][0] * m_value[1][1] * m_value[2][3] -
		m_value[3][0] * m_value[1][3] * m_value[2][1];

	inv.m_value[3][0] = -m_value[1][0] * m_value[2][1] * m_value[3][2] +
		m_value[1][0] * m_value[2][2] * m_value[3][1] +
		m_value[2][0] * m_value[1][1] * m_value[3][2] -
		m_value[2][0] * m_value[1][2] * m_value[3][1] -
		m_value[3][0] * m_value[1][1] * m_value[2][2] +
		m_value[3][0] * m_value[1][2] * m_value[2][1];

	inv.m_value[0][1] = -m_value[0][1] * m_value[2][2] * m_value[3][3] +
		m_value[0][1] * m_value[2][3] * m_value[3][2] +
		m_value[2][1] * m_value[0][2] * m_value[3][3] -
		m_value[2][1] * m_value[0][3] * m_value[3][2] -
		m_value[3][1] * m_value[0][2] * m_value[2][3] +
		m_value[3][1] * m_value[0][3] * m_value[2][2];

	inv.m_value[1][1] = m_value[0][0] * m_value[2][2] * m_value[3][3] -
		m_value[0][0] * m_value[2][3] * m_value[3][2] -
		m_value[2][0] * m_value[0][2] * m_value[3][3] +
		m_value[2][0] * m_value[0][3] * m_value[3][2] +
		m_value[3][0] * m_value[0][2] * m_value[2][3] -
		m_value[3][0] * m_value[0][3] * m_value[2][2];

	inv.m_value[2][1] = -m_value[0][0] * m_value[2][1] * m_value[3][3] +
		m_value[0][0] * m_value[2][3] * m_value[3][1] +
		m_value[2][0] * m_value[0][1] * m_value[3][3] -
		m_value[2][0] * m_value[0][3] * m_value[3][1] -
		m_value[3][0] * m_value[0][1] * m_value[2][3] +
		m_value[3][0] * m_value[0][3] * m_value[2][1];

	inv.m_value[3][1] = m_value[0][0] * m_value[2][1] * m_value[3][2] -
		m_value[0][0] * m_value[2][2] * m_value[3][1] -
		m_value[2][0] * m_value[0][1] * m_value[3][2] +
		m_value[2][0] * m_value[0][2] * m_value[3][1] +
		m_value[3][0] * m_value[0][1] * m_value[2][2] -
		m_value[3][0] * m_value[0][2] * m_value[2][1];

	inv.m_value[0][2] = m_value[0][1] * m_value[1][2] * m_value[3][3] -
		m_value[0][1] * m_value[1][3] * m_value[3][2] -
		m_value[1][1] * m_value[0][2] * m_value[3][3] +
		m_value[1][1] * m_value[0][3] * m_value[3][2] +
		m_value[3][1] * m_value[0][2] * m_value[1][3] -
		m_value[3][1] * m_value[0][3] * m_value[1][2];

	inv.m_value[1][2] = -m_value[0][0] * m_value[1][2] * m_value[3][3] +
		m_value[0][0] * m_value[1][3] * m_value[3][2] +
		m_value[1][0] * m_value[0][2] * m_value[3][3] -
		m_value[1][0] * m_value[0][3] * m_value[3][2] -
		m_value[3][0] * m_value[0][2] * m_value[1][3] +
		m_value[3][0] * m_value[0][3] * m_value[1][2];

	inv.m_value[2][2] = m_value[0][0] * m_value[1][1] * m_value[3][3] -
		m_value[0][0] * m_value[1][3] * m_value[3][1] -
		m_value[1][0] * m_value[0][1] * m_value[3][3] +
		m_value[1][0] * m_value[0][3] * m_value[3][1] +
		m_value[3][0] * m_value[0][1] * m_value[1][3] -
		m_value[3][0] * m_value[0][3] * m_value[1][1];

	inv.m_value[3][2] = -m_value[0][0] * m_value[1][1] * m_value[3][2] +
		m_value[0][0] * m_value[1][2] * m_value[3][1] +
		m_value[1][0] * m_value[0][1] * m_value[3][2] -
		m_value[1][0] * m_value[0][2] * m_value[3][1] -
		m_value[3][0] * m_value[0][1] * m_value[1][2] +
		m_value[3][0] * m_value[0][2] * m_value[1][1];

	inv.m_value[0][3] = -m_value[0][1] * m_value[1][2] * m_value[2][3] +
		m_value[0][1] * m_value[1][3] * m_value[2][2] +
		m_value[1][1] * m_value[0][2] * m_value[2][3] -
		m_value[1][1] * m_value[0][3] * m_value[2][2] -
		m_value[2][1] * m_value[0][2] * m_value[1][3] +
		m_value[2][1] * m_value[0][3] * m_value[1][2];

	inv.m_value[1][3] = m_value[0][0] * m_value[1][2] * m_value[2][3] -
		m_value[0][0] * m_value[1][3] * m_value[2][2] -
		m_value[1][0] * m_value[0][2] * m_value[2][3] +
		m_value[1][0] * m_value[0][3] * m_value[2][2] +
		m_value[2][0] * m_value[0][2] * m_value[1][3] -
		m_value[2][0] * m_value[0][3] * m_value[1][2];

	inv.m_value[2][3] = -m_value[0][0] * m_value[1][1] * m_value[2][3] +
		m_value[0][0] * m_value[1][3] * m_value[2][1] +
		m_value[1][0] * m_value[0][1] * m_value[2][3] -
		m_value[1][0] * m_value[0][3] * m_value[2][1] -
		m_value[2][0] * m_value[0][1] * m_value[1][3] +
		m_value[2][0] * m_value[0][3] * m_value[1][1];

	inv.m_value[3][3] = m_value[0][0] * m_value[1][1] * m_value[2][2] -
		m_value[0][0] * m_value[1][2] * m_value[2][1] -
		m_value[1][0] * m_value[0][1] * m_value[2][2] +
		m_value[1][0] * m_value[0][2] * m_value[2][1] +
		m_value[2][0] * m_value[0][1] * m_value[1][2] -
		m_value[2][0] * m_value[0][2] * m_value[1][1];

	float det = m_value[0][0] * inv.m_value[0][0] + m_value[0][1] * inv.m_value[1][0] + m_value[0][2] * inv.m_value[2][0] + m_value[0][3] * inv.m_value[3][0];
	if (det == 0)
		return;
	det = 1.f / det;
	*this = inv * det;
}

void Mat4::SetRotationX(float _theta)
{
	m_value[0][0] = 1.f;	m_value[0][1] = 0.f;			m_value[0][2] = 0.f;				m_value[0][3] = 0.f;
	m_value[1][0] = 0.f;	m_value[1][1] = cosf(_theta);	m_value[1][2] = -sinf(_theta);	m_value[1][3] = 0.f;
	m_value[2][0] = 0.f;	m_value[2][1] = sinf(_theta);	m_value[2][2] = cosf(_theta);		m_value[2][3] = 0.f;
	m_value[3][0] = 0.f;	m_value[3][1] = 0.f;			m_value[3][2] = 0.f;				m_value[3][3] = 1.f;
}

void Mat4::SetRotationY(float _theta)
{
	m_value[0][0] = cosf(_theta);		m_value[0][1] = 0.f;	m_value[0][2] = sinf(_theta);		m_value[0][3] = 0.f;
	m_value[1][0] = 0.f;				m_value[1][1] = 1.f;	m_value[1][2] = 0.f;				m_value[1][3] = 0.f;
	m_value[2][0] = -sinf(_theta);	m_value[2][1] = 0.f;	m_value[2][2] = cosf(_theta);		m_value[2][3] = 0.f;
	m_value[3][0] = 0.f;				m_value[3][1] = 0.f;	m_value[3][2] = 0.f;				m_value[3][3] = 1.f;
}

void Mat4::SetRotationZ(float _theta)
{
	m_value[0][0] = cosf(_theta);		m_value[0][1] = sinf(_theta);	m_value[0][2] = 0.f;		m_value[0][3] = 0.f;
	m_value[1][0] = -sinf(_theta);	m_value[1][1] = cosf(_theta);	m_value[1][2] = 0.f;		m_value[1][3] = 0.f;
	m_value[2][0] = 0.f;				m_value[2][1] = 0.f;			m_value[2][2] = 1.f;		m_value[2][3] = 0.f;
	m_value[3][0] = 0.f;				m_value[3][1] = 0.f;			m_value[3][2] = 0.f;		m_value[3][3] = 1.f;
}

void Mat4::SetRotation(Vec4 _theta)
{
	*this = Mat4();
	*this *= RotationX(_theta[0]);
	*this *= RotationY(_theta[1]);
	*this *= RotationZ(_theta[2]);
}

void Mat4::SetTranslation(Vec4 _translate)
{
	m_value[0][0] = 1.f;		m_value[0][1] = 0.f;		m_value[0][2] = 0.f;		m_value[0][3] = _translate[0];
	m_value[1][0] = 0.f;		m_value[1][1] = 1.f;		m_value[1][2] = 0.f;		m_value[1][3] = _translate[1];
	m_value[2][0] = 0.f;		m_value[2][1] = 0.f;		m_value[2][2] = 1.f;		m_value[2][3] = _translate[2];
	m_value[3][0] = 0.f;		m_value[3][1] = 0.f;		m_value[3][2] = 0.f;		m_value[3][3] = _translate[3];
}

void Mat4::SetScale(Vec4 _scale)
{
	m_value[0][0] = _scale[0];	m_value[0][1] = 0.f;			m_value[0][2] = 0.f;			m_value[0][3] = 0.f;
	m_value[1][0] = 0.f;			m_value[1][1] = _scale[1];	m_value[1][2] = 0.f;			m_value[1][3] = 0.f;
	m_value[2][0] = 0.f;			m_value[2][1] = 0.f;			m_value[2][2] = _scale[2];	m_value[2][3] = 0.f;
	m_value[3][0] = 0.f;			m_value[3][1] = 0.f;			m_value[3][2] = 0.f;			m_value[3][3] = _scale[3];
}

void Mat4::SetTRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	*this = Mat4();
	*this *= Translation(_translate);
	*this *= Rotation(_rotate);
	*this *= Scale(_scale);
}

void Mat4::SetTRS(Vec4 _translate, Vec4 _rotate, Vec4 _scale)
{
	*this = Mat4();
	*this *= Translation(_translate);
	*this *= Rotation(_rotate);
	*this *= Scale(_scale);
}

void Mat4::SetPerspectiveMatrix(int _width, int _height, float _fov, float _near, float _far)
{
	float fovRad = Tools::ToRad(_fov);
	float aspect = static_cast<float>(_width) / static_cast<float>(_height);
	m_value[0][0] = 1.f / (aspect * tanf(fovRad / 2.f));
	m_value[0][1] = 0.f;
	m_value[0][2] = 0.f;
	m_value[0][3] = 0.f;
	m_value[1][0] = 0.f;
	m_value[1][1] = 1.f / (tanf(fovRad / 2.f));
	m_value[1][2] = 0.f;
	m_value[1][3] = 0.f;
	m_value[2][0] = 0.f;
	m_value[2][1] = 0.f;
	m_value[2][2] = -1.f * (_far + _near) / (_far - _near);
	m_value[2][3] = -1.f * (2.f * _far * _near) / (_far - _near);
	m_value[3][0] = 0.f;
	m_value[3][1] = 0.f;
	m_value[3][2] = -1.f;
	m_value[3][3] = 0.f;
}

void Mat4::SetViewMatrix(Vec3 _eye, Vec3 _at, Vec3 _up)
{
	Vec3 frwd = Vec3{ _at, _eye };
	frwd.Normalize();
	Vec3 right = Vec3::CrossProduct(frwd, _up);
	right.Normalize();
	_up.Normalize();

	m_value[0][0] = right.x;
	m_value[0][1] = right.y;
	m_value[0][2] = right.z;
	m_value[0][3] = -right.DotProduct(_at);

	m_value[1][0] = _up.x;
	m_value[1][1] = _up.y;
	m_value[1][2] = _up.z;
	m_value[1][3] = -_up.DotProduct(_at);

	m_value[2][0] = -frwd.x;
	m_value[2][1] = -frwd.y;
	m_value[2][2] = -frwd.z;
	m_value[2][3] = frwd.DotProduct(_at);

	m_value[3][0] = 0.0f;
	m_value[3][1] = 0.0f;
	m_value[3][2] = 0.0f;
	m_value[3][3] = 1.0f;
}

void Mat4::Print() const
{
	std::cout << "|" << m_value[0][0] << ", " << m_value[0][1] << ", " << m_value[0][2] << ", " << m_value[0][3] << "|" << std::endl
		<< "|" << m_value[1][0] << ", " << m_value[1][1] << ", " << m_value[1][2] << ", " << m_value[1][3] << "|" << std::endl
		<< "|" << m_value[2][0] << ", " << m_value[2][1] << ", " << m_value[2][2] << ", " << m_value[2][3] << "|" << std::endl
		<< "|" << m_value[3][0] << ", " << m_value[3][1] << ", " << m_value[3][2] << ", " << m_value[3][3] << "|" << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec4 Mat4::Diagonal(Mat4 _mat)
{
	return { _mat[0][0], _mat[1][1], _mat[2][2], _mat[3][3] };
}

Mat4 Mat4::Transpose(Mat4 _mat)
{
	return { _mat[0][0], _mat[1][0], _mat[2][0], _mat[3][0],
			 _mat[0][1], _mat[1][1], _mat[2][1], _mat[3][1],
			 _mat[0][2], _mat[1][2], _mat[2][2], _mat[3][2],
			 _mat[0][3], _mat[1][3], _mat[2][3], _mat[3][3] };
}

float Mat4::Trace(Mat4 _mat)
{
	return  _mat[0][0] + _mat[1][1] + _mat[2][2] + _mat[3][3];
}

Mat4 Mat4::Opposite(Mat4 _mat)
{
	return { -_mat[0][0], -_mat[0][1], -_mat[0][2], -_mat[0][3],
			 -_mat[1][0], -_mat[1][1], -_mat[1][2], -_mat[1][3],
			 -_mat[2][0], -_mat[2][1], -_mat[2][2], -_mat[2][3],
			 -_mat[3][0], -_mat[3][1], -_mat[3][2], -_mat[3][3] };
}

float Mat4::Det(Mat4 _mat)
{	
	float a = _mat[0][0]; float b = _mat[0][1]; float c = _mat[0][2]; float d = _mat[0][3];
	float e = _mat[1][0]; float f = _mat[1][1]; float g = _mat[1][2]; float h = _mat[1][3];
	float i = _mat[2][0]; float j = _mat[2][1]; float k = _mat[2][2]; float l = _mat[2][3];
	float m = _mat[3][0]; float n = _mat[3][1]; float o = _mat[3][2]; float p = _mat[3][3];

	float temp1 = a * (f*k*p - f*l*o - g*j*p + g*l*n + h*j*o - h*k*n);
	float temp2 = -b * (e*k*p - e*l*o - g*i*p + g*l*m + h*i*o - h*k*m);
	float temp3 = c * (e*j*p - e*l*n - f*i*p + f*l*m + h*i*n - h*j*m);
	float temp4 = -d * (e*j*o - e*k*n - f*i*o + f*k*m + g*i*n - g*j*m);

	return temp1 + temp2 + temp3 + temp4;
}

Mat4 Mat4::Inverse(Mat4 _mat)
{
	Mat4 inv;
	inv.m_value[0][0] =   _mat[1][1] * _mat[2][2] * _mat[3][3] -
						_mat[1][1] * _mat[2][3] * _mat[3][2] -
						_mat[2][1] * _mat[1][2] * _mat[3][3] +
						_mat[2][1] * _mat[1][3] * _mat[3][2] +
						_mat[3][1] * _mat[1][2] * _mat[2][3] -
						_mat[3][1] * _mat[1][3] * _mat[2][2];

	inv.m_value[1][0] =   -_mat[1][0] * _mat[2][2] * _mat[3][3] +
						_mat[1][0] * _mat[2][3] * _mat[3][2] +
						_mat[2][0] * _mat[1][2] * _mat[3][3] -
						_mat[2][0] * _mat[1][3] * _mat[3][2] -
						_mat[3][0] * _mat[1][2] * _mat[2][3] +
						_mat[3][0] * _mat[1][3] * _mat[2][2];

	inv.m_value[2][0] =   _mat[1][0] * _mat[2][1] * _mat[3][3] -
						_mat[1][0] * _mat[2][3] * _mat[3][1] -
						_mat[2][0] * _mat[1][1] * _mat[3][3] +
						_mat[2][0] * _mat[1][3] * _mat[3][1] +
						_mat[3][0] * _mat[1][1] * _mat[2][3] -
						_mat[3][0] * _mat[1][3] * _mat[2][1];

	inv.m_value[3][0] =   -_mat[1][0] * _mat[2][1] * _mat[3][2] +
						_mat[1][0] * _mat[2][2] * _mat[3][1] +
						_mat[2][0] * _mat[1][1] * _mat[3][2] -
						_mat[2][0] * _mat[1][2] * _mat[3][1] -
						_mat[3][0] * _mat[1][1] * _mat[2][2] +
						_mat[3][0] * _mat[1][2] * _mat[2][1];

	inv.m_value[0][1] =   -_mat[0][1] * _mat[2][2] * _mat[3][3] +
						_mat[0][1] * _mat[2][3] * _mat[3][2] +
						_mat[2][1] * _mat[0][2] * _mat[3][3] -
						_mat[2][1] * _mat[0][3] * _mat[3][2] -
						_mat[3][1] * _mat[0][2] * _mat[2][3] +
						_mat[3][1] * _mat[0][3] * _mat[2][2];

	inv.m_value[1][1] =   _mat[0][0] * _mat[2][2] * _mat[3][3] -
						_mat[0][0] * _mat[2][3] * _mat[3][2] -
						_mat[2][0] * _mat[0][2] * _mat[3][3] +
						_mat[2][0] * _mat[0][3] * _mat[3][2] +
						_mat[3][0] * _mat[0][2] * _mat[2][3] -
						_mat[3][0] * _mat[0][3] * _mat[2][2];

	inv.m_value[2][1] =   -_mat[0][0] * _mat[2][1] * _mat[3][3] +
						_mat[0][0] * _mat[2][3] * _mat[3][1] +
						_mat[2][0] * _mat[0][1] * _mat[3][3] -
						_mat[2][0] * _mat[0][3] * _mat[3][1] -
						_mat[3][0] * _mat[0][1] * _mat[2][3] +
						_mat[3][0] * _mat[0][3] * _mat[2][1];

	inv.m_value[3][1] =   _mat[0][0] * _mat[2][1] * _mat[3][2] -
						_mat[0][0] * _mat[2][2] * _mat[3][1] -
						_mat[2][0] * _mat[0][1] * _mat[3][2] +
						_mat[2][0] * _mat[0][2] * _mat[3][1] +
						_mat[3][0] * _mat[0][1] * _mat[2][2] -
						_mat[3][0] * _mat[0][2] * _mat[2][1];

	inv.m_value[0][2] =   _mat[0][1] * _mat[1][2] * _mat[3][3] -
						_mat[0][1] * _mat[1][3] * _mat[3][2] -
						_mat[1][1] * _mat[0][2] * _mat[3][3] +
						_mat[1][1] * _mat[0][3] * _mat[3][2] +
						_mat[3][1] * _mat[0][2] * _mat[1][3] -
						_mat[3][1] * _mat[0][3] * _mat[1][2];

	inv.m_value[1][2] =   -_mat[0][0] * _mat[1][2] * _mat[3][3] +
						_mat[0][0] * _mat[1][3] * _mat[3][2] +
						_mat[1][0] * _mat[0][2] * _mat[3][3] -
						_mat[1][0] * _mat[0][3] * _mat[3][2] -
						_mat[3][0] * _mat[0][2] * _mat[1][3] +
						_mat[3][0] * _mat[0][3] * _mat[1][2];

	inv.m_value[2][2] =   _mat[0][0] * _mat[1][1] * _mat[3][3] -
						_mat[0][0] * _mat[1][3] * _mat[3][1] -
						_mat[1][0] * _mat[0][1] * _mat[3][3] +
						_mat[1][0] * _mat[0][3] * _mat[3][1] +
						_mat[3][0] * _mat[0][1] * _mat[1][3] -
						_mat[3][0] * _mat[0][3] * _mat[1][1];

	inv.m_value[3][2] =   -_mat[0][0] * _mat[1][1] * _mat[3][2] +
						_mat[0][0] * _mat[1][2] * _mat[3][1] +
						_mat[1][0] * _mat[0][1] * _mat[3][2] -
						_mat[1][0] * _mat[0][2] * _mat[3][1] -
						_mat[3][0] * _mat[0][1] * _mat[1][2] +
						_mat[3][0] * _mat[0][2] * _mat[1][1];

	inv.m_value[0][3] =   -_mat[0][1] * _mat[1][2] * _mat[2][3] +
						_mat[0][1] * _mat[1][3] * _mat[2][2] +
						_mat[1][1] * _mat[0][2] * _mat[2][3] -
						_mat[1][1] * _mat[0][3] * _mat[2][2] -
						_mat[2][1] * _mat[0][2] * _mat[1][3] +
						_mat[2][1] * _mat[0][3] * _mat[1][2];

	inv.m_value[1][3] =   _mat[0][0] * _mat[1][2] * _mat[2][3] -
						_mat[0][0] * _mat[1][3] * _mat[2][2] -
						_mat[1][0] * _mat[0][2] * _mat[2][3] +
						_mat[1][0] * _mat[0][3] * _mat[2][2] +
						_mat[2][0] * _mat[0][2] * _mat[1][3] -
						_mat[2][0] * _mat[0][3] * _mat[1][2];

	inv.m_value[2][3] =   -_mat[0][0] * _mat[1][1] * _mat[2][3] +
						_mat[0][0] * _mat[1][3] * _mat[2][1] +
						_mat[1][0] * _mat[0][1] * _mat[2][3] -
						_mat[1][0] * _mat[0][3] * _mat[2][1] -
						_mat[2][0] * _mat[0][1] * _mat[1][3] +
						_mat[2][0] * _mat[0][3] * _mat[1][1];

	inv.m_value[3][3] =   _mat[0][0] * _mat[1][1] * _mat[2][2] -
						_mat[0][0] * _mat[1][2] * _mat[2][1] -
						_mat[1][0] * _mat[0][1] * _mat[2][2] +
						_mat[1][0] * _mat[0][2] * _mat[2][1] +
						_mat[2][0] * _mat[0][1] * _mat[1][2] -
						_mat[2][0] * _mat[0][2] * _mat[1][1];

	float det = _mat[0][0] * inv.m_value[0][0] + _mat[0][1] * inv.m_value[1][0] + _mat[0][2] * inv.m_value[2][0] + _mat[0][3] * inv.m_value[3][0];
	if (det == 0)
		return _mat;
	det = 1.f / det;
	return inv * det;
}

Mat4 Mat4::RotationX(float _theta)
{
	return { 1.f,	0.f,			0.f,			0.f,
			 0.f,	cosf(_theta),	-sinf(_theta),	0.f,
			 0.f,	sinf(_theta),	cosf(_theta),	0.f,
			 0.f,	0.f,			0.f,			1.f };
}

Mat4 Mat4::RotationY(float _theta)
{
	return { cosf(_theta),	0.f,	sinf(_theta),	0.f,
			 0.f,			1.f,	0.f,			0.f,
			 -sinf(_theta), 0.f,	cosf(_theta),	0.f,
			 0.f,			0.f,	0.f,			1.f };
}

Mat4 Mat4::RotationZ(float _theta)
{
	return { cosf(_theta),	sinf(_theta),	0.f,	0.f,
			 -sinf(_theta), cosf(_theta),	0.f,	0.f,
			 0.f,			0.f,			1.f,	0.f,
			 0.f,			0.f,			0.f,	1.f
	};
}

Mat4 Mat4::Rotation(Vec3 _theta)
{
	Mat4 mat;
	mat *= RotationX(_theta[0]);
	mat *= RotationY(_theta[1]);
	mat *= RotationZ(_theta[2]);
	return mat;
}

Mat4 Mat4::Rotation(Vec4 _theta)
{
	Mat4 mat;
	mat *= RotationX(_theta[0]);
	mat *= RotationY(_theta[1]);
	mat *= RotationZ(_theta[2]);
	return mat;
}

Mat4 Mat4::Rotation(Quat _rota)
{
	Mat3 rot = Quat::QuatToMatrix(_rota);
	Mat4 mat
	{
		rot[0][0], rot[0][1], rot[0][2], 0.f,
		rot[1][0], rot[1][1], rot[1][2], 0.f,
		rot[2][0], rot[2][1], rot[2][2], 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	return mat;
}

Mat4 Mat4::Translation(Vec3 _translate)
{
	return { 1.f,	0.f,	0.f,	_translate[0],
			 0.f,	1.f,	0.f,	_translate[1],
			 0.f,	0.f,	1.f,	_translate[2],
			 0.f,	0.f,	0.f,	1.f };
}

Mat4 Mat4::Translation(Vec4 _translate)
{
	return { 1.f,	0.f,	0.f,	_translate[0],
			 0.f,	1.f,	0.f,	_translate[1],
			 0.f,	0.f,	1.f,	_translate[2],
			 0.f,	0.f,	0.f,	_translate[3] };
}

Mat4 Mat4::Scale(Vec3 _scale)
{
	return { _scale[0],	0.f,		0.f,		0.f,
			 0.f,		_scale[1],	0.f,		0.f,
			 0.f,		0.f,		_scale[2],	0.f,
			 0.f,		0.f,		0.f,		1.f };
}

Mat4 Mat4::Scale(Vec4 _scale)
{
	return { _scale[0],	0.f,		0.f,		0.f,
			 0.f,		_scale[1],	0.f,		0.f,
			 0.f,		0.f,		_scale[2],	0.f,
			 0.f,		0.f,		0.f,		_scale[3] };
}

Mat4 Mat4::TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	Mat4 TRS;
	TRS *= Translation(_translate);
	TRS *= Rotation(_rotate);
	TRS *= Scale(_scale);
	return TRS;
}

Mat4 Mat4::TRS(Vec4 _translate, Vec4 _rotate, Vec4 _scale)
{
	Mat4 TRS;
	TRS *= Translation(_translate);
	TRS *= Rotation(_rotate);
	TRS *= Scale(_scale);
	return TRS;
}

Mat4 Mat4::TRS(Vec3 _translate, Quat _rotate, Vec3 _scale)
{
	Mat4 TRS;
	TRS *= Translation(_translate);
	TRS *= Rotation(_rotate);
	TRS *= Scale(_scale);
	return TRS;
}

Mat4 Mat4::PerspectiveMatrix(int _width, int _height, float _fov, float _near, float _far)
{
	if (_width == 0 || _height == 0)
		return Mat4();

	float aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
	float fovRad = _fov * Tools::PI / 180.f;
	return { 1.f / (aspectRatio * tanf(fovRad / 2.f)), 0.f, 0.f, 0.f,
		0.f, 1.f / (tanf(fovRad / 2.f)), 0.f, 0.f,
		0.f, 0.f, -1.f * (_far + _near) / (_far - _near), -1.f * (2.f * _far * _near) / (_far - _near),
		0.f, 0.f, -1.f, 0.f };
}

Mat4 Mat4::ViewMatrix(Vec3 _eye, Vec3 _at, Vec3 _up)
{
	Vec3 frwd = Vec3{ _at, _eye };
	frwd.Normalize();
	Vec3 right = Vec3::CrossProduct(frwd, _up);
	right.Normalize();
	Vec3 _newUp = Vec3::CrossProduct(right, frwd);
	_newUp.Normalize();

	return {
	right.x, right.y, right.z, -right.DotProduct(_at),
	_newUp.x, _newUp.y, _newUp.z, -_newUp.DotProduct(_at),
	-frwd.x, -frwd.y, -frwd.z, frwd.DotProduct(_at),
	0.0f, 0.0f, 0.0f, 1.0f
	};
}

void Mat4::Print(Mat4 _mat)
{
	std::cout << "|" << _mat[0][0] << ", " << _mat[0][1] << ", " << _mat[0][2] << ", " << _mat[0][3] << "|" << std::endl
		<< "|" << _mat[1][0] << ", " << _mat[1][1] << ", " << _mat[1][2] << ", " << _mat[1][3] << "|" << std::endl
		<< "|" << _mat[2][0] << ", " << _mat[2][1] << ", " << _mat[2][2] << ", " << _mat[2][3] << "|" << std::endl
		<< "|" << _mat[3][0] << ", " << _mat[3][1] << ", " << _mat[3][2] << ", " << _mat[3][3] << "|" << std::endl;
}


//####################### OPERATORS #######################

Mat4 Mat4::operator+(float _scalar) const
{
	return { m_value[0][0] + _scalar, m_value[0][1] + _scalar, m_value[0][2] + _scalar, m_value[0][3] + _scalar,
			 m_value[1][0] + _scalar, m_value[1][1] + _scalar, m_value[1][2] + _scalar, m_value[1][3] + _scalar,
			 m_value[2][0] + _scalar, m_value[2][1] + _scalar, m_value[2][2] + _scalar, m_value[2][3] + _scalar,
			 m_value[3][0] + _scalar, m_value[3][1] + _scalar, m_value[3][2] + _scalar, m_value[3][3] + _scalar };
}

Mat4 Mat4::operator+(Mat4 _mat) const
{
	return { m_value[0][0] + _mat[0][0], m_value[0][1] + _mat[0][1], m_value[0][2] + _mat[0][2], m_value[0][3] + _mat[0][3],
			 m_value[1][0] + _mat[1][0], m_value[1][1] + _mat[1][1], m_value[1][2] + _mat[1][2], m_value[1][3] + _mat[1][3],
			 m_value[2][0] + _mat[2][0], m_value[2][1] + _mat[2][1], m_value[2][2] + _mat[2][2], m_value[2][3] + _mat[2][3],
			 m_value[3][0] + _mat[3][0], m_value[3][1] + _mat[3][1], m_value[3][2] + _mat[3][2], m_value[3][3] + _mat[3][3] };
}

Mat4 Mat4::operator-(float _scalar) const
{
	return { m_value[0][0] - _scalar, m_value[0][1] - _scalar, m_value[0][2] - _scalar, m_value[0][3] - _scalar,
			 m_value[1][0] - _scalar, m_value[1][1] - _scalar, m_value[1][2] - _scalar, m_value[1][3] - _scalar,
			 m_value[2][0] - _scalar, m_value[2][1] - _scalar, m_value[2][2] - _scalar, m_value[2][3] - _scalar,
			 m_value[3][0] - _scalar, m_value[3][1] - _scalar, m_value[3][2] - _scalar, m_value[3][3] - _scalar };
}

Mat4 Mat4::operator-(Mat4 _mat) const
{
	return { m_value[0][0] - _mat[0][0], m_value[0][1] - _mat[0][1], m_value[0][2] - _mat[0][2], m_value[0][3] - _mat[0][3],
			 m_value[1][0] - _mat[1][0], m_value[1][1] - _mat[1][1], m_value[1][2] - _mat[1][2], m_value[1][3] - _mat[1][3],
			 m_value[2][0] - _mat[2][0], m_value[2][1] - _mat[2][1], m_value[2][2] - _mat[2][2], m_value[2][3] - _mat[2][3],
			 m_value[3][0] - _mat[3][0], m_value[3][1] - _mat[3][1], m_value[3][2] - _mat[3][2], m_value[3][3] - _mat[3][3] };
}

Mat4 Mat4::operator*(float _scalar) const
{
	return { m_value[0][0] * _scalar, m_value[0][1] * _scalar, m_value[0][2] * _scalar, m_value[0][3] * _scalar,
			 m_value[1][0] * _scalar, m_value[1][1] * _scalar, m_value[1][2] * _scalar, m_value[1][3] * _scalar,
			 m_value[2][0] * _scalar, m_value[2][1] * _scalar, m_value[2][2] * _scalar, m_value[2][3] * _scalar,
			 m_value[3][0] * _scalar, m_value[3][1] * _scalar, m_value[3][2] * _scalar, m_value[3][3] * _scalar };
}

Vec4 Mat4::operator*(Vec3 _vec) const
{
	return { m_value[0][0] * _vec[0] + m_value[0][1] * _vec[1] + m_value[0][2] * _vec[2],
			 m_value[1][0] * _vec[0] + m_value[1][1] * _vec[1] + m_value[1][2] * _vec[2],
			 m_value[2][0] * _vec[0] + m_value[2][1] * _vec[1] + m_value[2][2] * _vec[2],
			 m_value[3][0] * _vec[0] + m_value[3][1] * _vec[1] + m_value[3][2] * _vec[2] };
}

Vec4 Mat4::operator*(Vec4 _vec) const
{
	return { m_value[0][0] * _vec[0] + m_value[0][1] * _vec[1] + m_value[0][2] * _vec[2] + m_value[0][3] * _vec[3],
			 m_value[1][0] * _vec[0] + m_value[1][1] * _vec[1] + m_value[1][2] * _vec[2] + m_value[1][3] * _vec[3],
			 m_value[2][0] * _vec[0] + m_value[2][1] * _vec[1] + m_value[2][2] * _vec[2] + m_value[2][3] * _vec[3],
			 m_value[3][0] * _vec[0] + m_value[3][1] * _vec[1] + m_value[3][2] * _vec[2] + m_value[3][3] * _vec[3] };
}

Mat4 Mat4::operator*(Mat4 _mat) const
{
	return { m_value[0][0] * _mat[0][0] + m_value[0][1] * _mat[1][0] + m_value[0][2] * _mat[2][0] + m_value[0][3] * _mat[3][0],
			 m_value[0][0] * _mat[0][1] + m_value[0][1] * _mat[1][1] + m_value[0][2] * _mat[2][1] + m_value[0][3] * _mat[3][1],
			 m_value[0][0] * _mat[0][2] + m_value[0][1] * _mat[1][2] + m_value[0][2] * _mat[2][2] + m_value[0][3] * _mat[3][2],
			 m_value[0][0] * _mat[0][3] + m_value[0][1] * _mat[1][3] + m_value[0][2] * _mat[2][3] + m_value[0][3] * _mat[3][3],

			 m_value[1][0] * _mat[0][0] + m_value[1][1] * _mat[1][0] + m_value[1][2] * _mat[2][0] + m_value[1][3] * _mat[3][0],
			 m_value[1][0] * _mat[0][1] + m_value[1][1] * _mat[1][1] + m_value[1][2] * _mat[2][1] + m_value[1][3] * _mat[3][1],
			 m_value[1][0] * _mat[0][2] + m_value[1][1] * _mat[1][2] + m_value[1][2] * _mat[2][2] + m_value[1][3] * _mat[3][2],
			 m_value[1][0] * _mat[0][3] + m_value[1][1] * _mat[1][3] + m_value[1][2] * _mat[2][3] + m_value[1][3] * _mat[3][3],

			 m_value[2][0] * _mat[0][0] + m_value[2][1] * _mat[1][0] + m_value[2][2] * _mat[2][0] + m_value[2][3] * _mat[3][0],
			 m_value[2][0] * _mat[0][1] + m_value[2][1] * _mat[1][1] + m_value[2][2] * _mat[2][1] + m_value[2][3] * _mat[3][1],
			 m_value[2][0] * _mat[0][2] + m_value[2][1] * _mat[1][2] + m_value[2][2] * _mat[2][2] + m_value[2][3] * _mat[3][2],
			 m_value[2][0] * _mat[0][3] + m_value[2][1] * _mat[1][3] + m_value[2][2] * _mat[2][3] + m_value[2][3] * _mat[3][3],

			 m_value[3][0] * _mat[0][0] + m_value[3][1] * _mat[1][0] + m_value[3][2] * _mat[2][0] + m_value[3][3] * _mat[3][0],
			 m_value[3][0] * _mat[0][1] + m_value[3][1] * _mat[1][1] + m_value[3][2] * _mat[2][1] + m_value[3][3] * _mat[3][1],
			 m_value[3][0] * _mat[0][2] + m_value[3][1] * _mat[1][2] + m_value[3][2] * _mat[2][2] + m_value[3][3] * _mat[3][2],
			 m_value[3][0] * _mat[0][3] + m_value[3][1] * _mat[1][3] + m_value[3][2] * _mat[2][3] + m_value[3][3] * _mat[3][3] };
}

void Mat4::operator+=(float _scalar)
{
	m_value[0][0] += _scalar;	m_value[0][1] += _scalar;	m_value[0][2] += _scalar;	m_value[0][3] += _scalar;
	m_value[1][0] += _scalar;	m_value[1][1] += _scalar;	m_value[1][2] += _scalar;	m_value[1][3] += _scalar;
	m_value[2][0] += _scalar;	m_value[2][1] += _scalar;	m_value[2][2] += _scalar;	m_value[2][3] += _scalar;
	m_value[3][0] += _scalar;	m_value[3][1] += _scalar;	m_value[3][2] += _scalar;	m_value[3][3] += _scalar;
}

void Mat4::operator+=(Mat4 _mat)
{
	m_value[0][0] += _mat[0][0];	m_value[0][1] += _mat[0][1];	m_value[0][2] += _mat[0][2];	m_value[0][3] += _mat[0][3];
	m_value[1][0] += _mat[1][0];	m_value[1][1] += _mat[1][1];	m_value[1][2] += _mat[1][2];	m_value[1][3] += _mat[1][3];
	m_value[2][0] += _mat[2][0];	m_value[2][1] += _mat[2][1];	m_value[2][2] += _mat[2][2];	m_value[2][3] += _mat[2][3];
	m_value[3][0] += _mat[3][0];	m_value[3][1] += _mat[3][1];	m_value[3][2] += _mat[3][2];	m_value[3][3] += _mat[3][3];
}

void Mat4::operator-=(float _scalar)
{
	m_value[0][0] -= _scalar;	m_value[0][1] -= _scalar;	m_value[0][2] -= _scalar;	m_value[0][3] -= _scalar;
	m_value[1][0] -= _scalar;	m_value[1][1] -= _scalar;	m_value[1][2] -= _scalar;	m_value[1][3] -= _scalar;
	m_value[2][0] -= _scalar;	m_value[2][1] -= _scalar;	m_value[2][2] -= _scalar;	m_value[2][3] -= _scalar;
	m_value[3][0] -= _scalar;	m_value[3][1] -= _scalar;	m_value[3][2] -= _scalar;	m_value[3][3] -= _scalar;
}

void Mat4::operator-=(Mat4 _mat)
{
	m_value[0][0] -= _mat[0][0];	m_value[0][1] -= _mat[0][1];	m_value[0][2] -= _mat[0][2];	m_value[0][3] -= _mat[0][3];
	m_value[1][0] -= _mat[1][0];	m_value[1][1] -= _mat[1][1];	m_value[1][2] -= _mat[1][2];	m_value[1][3] -= _mat[1][3];
	m_value[2][0] -= _mat[2][0];	m_value[2][1] -= _mat[2][1];	m_value[2][2] -= _mat[2][2];	m_value[2][3] -= _mat[2][3];
	m_value[3][0] -= _mat[3][0];	m_value[3][1] -= _mat[3][1];	m_value[3][2] -= _mat[3][2];	m_value[3][3] -= _mat[3][3];
}

void Mat4::operator*=(float _scalar)
{
	m_value[0][0] *= _scalar;		m_value[0][1] *= _scalar;		m_value[0][2] *= _scalar;		m_value[0][3] *= _scalar;
	m_value[1][0] *= _scalar;		m_value[1][1] *= _scalar;		m_value[1][2] *= _scalar;		m_value[1][3] *= _scalar;
	m_value[2][0] *= _scalar;		m_value[2][1] *= _scalar;		m_value[2][2] *= _scalar;		m_value[2][3] *= _scalar;
	m_value[3][0] *= _scalar;		m_value[3][1] *= _scalar;		m_value[3][2] *= _scalar;		m_value[3][3] *= _scalar;
}

void Mat4::operator*=(Mat4 _mat)
{
	float temp00 = m_value[0][0]; float temp01 = m_value[0][1]; float temp02 = m_value[0][2]; float temp03 = m_value[0][3];
	float temp10 = m_value[1][0]; float temp11 = m_value[1][1]; float temp12 = m_value[1][2]; float temp13 = m_value[1][3];
	float temp20 = m_value[2][0]; float temp21 = m_value[2][1]; float temp22 = m_value[2][2]; float temp23 = m_value[2][3];
	float temp30 = m_value[3][0]; float temp31 = m_value[3][1]; float temp32 = m_value[3][2]; float temp33 = m_value[3][3];

	m_value[0][0] = temp00 * _mat[0][0] + temp01 * _mat[1][0] + temp02 * _mat[2][0] + temp03 * _mat[3][0];
	m_value[0][1] = temp00 * _mat[0][1] + temp01 * _mat[1][1] + temp02 * _mat[2][1] + temp03 * _mat[3][1];
	m_value[0][2] = temp00 * _mat[0][2] + temp01 * _mat[1][2] + temp02 * _mat[2][2] + temp03 * _mat[3][2];
	m_value[0][3] = temp00 * _mat[0][3] + temp01 * _mat[1][3] + temp02 * _mat[2][3] + temp03 * _mat[3][3];

	m_value[1][0] = temp10 * _mat[0][0] + temp11 * _mat[1][0] + temp12 * _mat[2][0] + temp13 * _mat[3][0];
	m_value[1][1] = temp10 * _mat[0][1] + temp11 * _mat[1][1] + temp12 * _mat[2][1] + temp13 * _mat[3][1];
	m_value[1][2] = temp10 * _mat[0][2] + temp11 * _mat[1][2] + temp12 * _mat[2][2] + temp13 * _mat[3][2];
	m_value[1][3] = temp10 * _mat[0][3] + temp11 * _mat[1][3] + temp12 * _mat[2][3] + temp13 * _mat[3][3];

	m_value[2][0] = temp20 * _mat[0][0] + temp21 * _mat[1][0] + temp22 * _mat[2][0] + temp23 * _mat[3][0];
	m_value[2][1] = temp20 * _mat[0][1] + temp21 * _mat[1][1] + temp22 * _mat[2][1] + temp23 * _mat[3][1];
	m_value[2][2] = temp20 * _mat[0][2] + temp21 * _mat[1][2] + temp22 * _mat[2][2] + temp23 * _mat[3][2];
	m_value[2][3] = temp20 * _mat[0][3] + temp21 * _mat[1][3] + temp22 * _mat[2][3] + temp23 * _mat[3][3];

	m_value[3][0] = temp30 * _mat[0][0] + temp31 * _mat[1][0] + temp32 * _mat[2][0] + temp33 * _mat[3][0];
	m_value[3][1] = temp30 * _mat[0][1] + temp31 * _mat[1][1] + temp32 * _mat[2][1] + temp33 * _mat[3][1];
	m_value[3][2] = temp30 * _mat[0][2] + temp31 * _mat[1][2] + temp32 * _mat[2][2] + temp33 * _mat[3][2];
	m_value[3][3] = temp30 * _mat[0][3] + temp31 * _mat[1][3] + temp32 * _mat[2][3] + temp33 * _mat[3][3];
}

Vec4 Mat4::operator[](int _i) const
{
	if (_i == 0 || _i == 1 || _i == 2 || _i == 3)
		return { m_value[_i][0], m_value[_i][1], m_value[_i][2], m_value[_i][3] };
	return { NAN, NAN, NAN, NAN }; // TODO Replace
}

void Mat4::operator=(float _scalar)
{
	m_value[0][0] = _scalar;		m_value[0][1] = _scalar;		m_value[0][2] = _scalar;		m_value[0][3] = _scalar;
	m_value[1][0] = _scalar;		m_value[1][1] = _scalar;		m_value[1][2] = _scalar;		m_value[1][3] = _scalar;
	m_value[2][0] = _scalar;		m_value[2][1] = _scalar;		m_value[2][2] = _scalar;		m_value[2][3] = _scalar;
	m_value[3][0] = _scalar;		m_value[3][1] = _scalar;		m_value[3][2] = _scalar;		m_value[3][3] = _scalar;
}

void Mat4::operator=(Mat4 _mat)
{
	m_value[0][0] = _mat[0][0];		m_value[0][1] = _mat[0][1];		m_value[0][2] = _mat[0][2];		m_value[0][3] = _mat[0][3];
	m_value[1][0] = _mat[1][0];		m_value[1][1] = _mat[1][1];		m_value[1][2] = _mat[1][2];		m_value[1][3] = _mat[1][3];
	m_value[2][0] = _mat[2][0];		m_value[2][1] = _mat[2][1];		m_value[2][2] = _mat[2][2];		m_value[2][3] = _mat[2][3];
	m_value[3][0] = _mat[3][0];		m_value[3][1] = _mat[3][1];		m_value[3][2] = _mat[3][2];		m_value[3][3] = _mat[3][3];
}

bool Mat4::operator==(Mat4 _mat) const
{
	return	fabs(m_value[0][0] - _mat[0][0]) <= Tools::epsilon && fabs(m_value[0][1] - _mat[0][1]) <= Tools::epsilon && fabs(m_value[0][2] - _mat[0][2]) <= Tools::epsilon && fabs(m_value[0][3] - _mat[0][3]) <= Tools::epsilon &&
			fabs(m_value[1][0] - _mat[1][0]) <= Tools::epsilon && fabs(m_value[1][1] - _mat[1][1]) <= Tools::epsilon && fabs(m_value[1][2] - _mat[1][2]) <= Tools::epsilon && fabs(m_value[1][3] - _mat[1][3]) <= Tools::epsilon &&
			fabs(m_value[2][0] - _mat[2][0]) <= Tools::epsilon && fabs(m_value[2][1] - _mat[2][1]) <= Tools::epsilon && fabs(m_value[2][2] - _mat[2][2]) <= Tools::epsilon && fabs(m_value[2][3] - _mat[2][3]) <= Tools::epsilon &&
			fabs(m_value[3][0] - _mat[3][0]) <= Tools::epsilon && fabs(m_value[3][1] - _mat[3][1]) <= Tools::epsilon && fabs(m_value[3][2] - _mat[3][2]) <= Tools::epsilon && fabs(m_value[3][3] - _mat[3][3]) <= Tools::epsilon;
}

bool Mat4::operator!=(Mat4 _mat) const
{
	return	fabs(m_value[0][0] - _mat[0][0]) >= Tools::epsilon || fabs(m_value[0][1] - _mat[0][1]) >= Tools::epsilon || fabs(m_value[0][2] - _mat[0][2]) >= Tools::epsilon || fabs(m_value[0][3] - _mat[0][3]) >= Tools::epsilon ||
			fabs(m_value[1][0] - _mat[1][0]) >= Tools::epsilon || fabs(m_value[1][1] - _mat[1][1]) >= Tools::epsilon || fabs(m_value[1][2] - _mat[1][2]) >= Tools::epsilon || fabs(m_value[1][3] - _mat[1][3]) >= Tools::epsilon ||
			fabs(m_value[2][0] - _mat[2][0]) >= Tools::epsilon || fabs(m_value[2][1] - _mat[2][1]) >= Tools::epsilon || fabs(m_value[2][2] - _mat[2][2]) >= Tools::epsilon || fabs(m_value[2][3] - _mat[2][3]) >= Tools::epsilon ||
			fabs(m_value[3][0] - _mat[3][0]) >= Tools::epsilon || fabs(m_value[3][1] - _mat[3][1]) >= Tools::epsilon || fabs(m_value[3][2] - _mat[3][2]) >= Tools::epsilon || fabs(m_value[3][3] - _mat[3][3]) >= Tools::epsilon;
}