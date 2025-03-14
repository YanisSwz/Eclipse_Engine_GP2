#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Tools.hpp"
#include <iostream>
using namespace Math;


//####################### CONSTRUCTORS #######################

Mat4::Mat4(float _scalar)
{
	value[0][0] = _scalar;		value[0][1] = _scalar;		value[0][2] = _scalar;		value[0][3] = _scalar;
	value[1][0] = _scalar;		value[1][1] = _scalar;		value[1][2] = _scalar;		value[1][3] = _scalar;
	value[2][0] = _scalar;		value[2][1] = _scalar;		value[2][2] = _scalar;		value[2][3] = _scalar;
	value[3][0] = _scalar;		value[3][1] = _scalar;		value[3][2] = _scalar;		value[3][3] = _scalar;
}

Mat4::Mat4(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	value[0][0] = _a;		value[0][1] = _b;		value[0][2] = _c;		value[0][3] = _d;
	value[1][0] = _e;		value[1][1] = _f;		value[1][2] = _g;		value[1][3] = _h;
	value[2][0] = _i;		value[2][1] = _j;		value[2][2] = _k;		value[2][3] = _l;
	value[3][0] = _m;		value[3][1] = _n;		value[3][2] = _o;		value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	value[0][0] = _vec[0];		value[0][1] = _vec[1];		value[0][2] = _vec[2];		value[0][3] = _vec[3];
	value[1][0] = _e;			value[1][1] = _f;			value[1][2] = _g;			value[1][3] = _h;
	value[2][0] = _i;			value[2][1] = _j;			value[2][2] = _k;			value[2][3] = _l;
	value[3][0] = _m;			value[3][1] = _n;			value[3][2] = _o;			value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];		value[0][2] = _vec1[2];		value[0][3] = _vec1[3];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];		value[1][2] = _vec2[2];		value[1][3] = _vec2[3];
	value[2][0] = _i;			value[2][1] = _j;			value[2][2] = _k;			value[2][3] = _l;
	value[3][0] = _m;			value[3][1] = _n;			value[3][2] = _o;			value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, float _m, float _n, float _o, float _p)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];		value[0][2] = _vec1[2];		value[0][3] = _vec1[3];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];		value[1][2] = _vec2[2];		value[1][3] = _vec2[3];
	value[2][0] = _vec3[0];		value[2][1] = _vec3[1];		value[2][2] = _vec3[2];		value[2][3] = _vec3[3];
	value[3][0] = _m;			value[3][1] = _n;			value[3][2] = _o;			value[3][3] = _p;
}

Mat4::Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, Vec4 _vec4)
{
	value[0][0] = _vec1[0];		value[0][1] = _vec1[1];		value[0][2] = _vec1[2];		value[0][3] = _vec1[3];
	value[1][0] = _vec2[0];		value[1][1] = _vec2[1];		value[1][2] = _vec2[2];		value[1][3] = _vec2[3];
	value[2][0] = _vec3[0];		value[2][1] = _vec3[1];		value[2][2] = _vec3[2];		value[2][3] = _vec3[3];
	value[3][0] = _vec4[0];		value[3][1] = _vec4[1];		value[3][2] = _vec4[2];		value[3][3] = _vec4[3];
}

Mat4::Mat4(const Mat4& _copy)
{
	value[0][0] = _copy[0][0];		value[0][1] = _copy[0][1];		value[0][2] = _copy[0][2];		value[0][3] = _copy[0][3];
	value[1][0] = _copy[1][0];		value[1][1] = _copy[1][1];		value[1][2] = _copy[1][2];		value[1][3] = _copy[1][3];
	value[2][0] = _copy[2][0];		value[2][1] = _copy[2][1];		value[2][2] = _copy[2][2];		value[2][3] = _copy[2][3];
	value[3][0] = _copy[3][0];		value[3][1] = _copy[3][1];		value[3][2] = _copy[3][2];		value[3][3] = _copy[3][3];
}


//####################### FUNCTIONS #######################

float& Mat4::GetValues()
{
	return *value[0];
}

Vec4 Mat4::Diagonal() const
{
	return { value[0][0], value[1][1], value[2][2], value[3][3] };
}

void Mat4::Transpose()
{
	float temp01 = value[0][1]; float temp02 = value[0][2]; float temp03 = value[0][3];
	float temp10 = value[1][0];								float temp12 = value[1][2]; float temp13 = value[1][3];
	float temp20 = value[2][0]; float temp21 = value[2][1];								float temp23 = value[2][3];
	float temp30 = value[3][0]; float temp31 = value[3][1]; float temp32 = value[3][2];

	value[0][1] = temp10;	value[0][2] = temp20;	value[0][3] = temp30;
	value[1][0] = temp01;							value[1][2] = temp21;	value[1][3] = temp31;
	value[2][0] = temp02;	value[2][1] = temp12;							value[2][3] = temp32;
	value[3][0] = temp03;	value[3][1] = temp13;	value[3][2] = temp23;
}

float Mat4::Trace() const
{
	return value[0][0] + value[1][1] + value[2][2] + value[3][3];
}

void Mat4::Opposite()
{
	value[0][0] *= -1; value[0][1] *= -1; value[0][2] *= -1; value[0][3] *= -1;
	value[1][0] *= -1; value[1][1] *= -1; value[1][2] *= -1; value[1][3] *= -1;
	value[2][0] *= -1; value[2][1] *= -1; value[2][2] *= -1; value[2][3] *= -1;
	value[3][0] *= -1; value[3][1] *= -1; value[3][2] *= -1; value[3][3] *= -1;
}

float Mat4::Det() const
{
	float a = value[0][0]; float b = value[0][1]; float c = value[0][2]; float d = value[0][3];
	float e = value[1][0]; float f = value[1][1]; float g = value[1][2]; float h = value[1][3];
	float i = value[2][0]; float j = value[2][1]; float k = value[2][2]; float l = value[2][3];
	float m = value[3][0]; float n = value[3][1]; float o = value[3][2]; float p = value[3][3];

	float temp1 = a * (f*k*p - f*l*o - g*j*p + g*l*n + h*j*o - h*k*n);
	float temp2 = -b * (e*k*p - e*l*o - g*i*p + g*l*m + h*i*o - h*k*m);
	float temp3 = c * (e*j*p - e*l*n - f*i*p + f*l*m + h*i*n - h*j*m);
	float temp4 = -d * (e*j*o - e*k*n - f*i*o + f*k*m + g*i*n - g*j*m);

	return temp1 + temp2 + temp3 + temp4;
}

void Mat4::Inverse()
{
	Mat4 inv;
	inv.value[0][0] = value[1][1] * value[2][2] * value[3][3] -
		value[1][1] * value[2][3] * value[3][2] -
		value[2][1] * value[1][2] * value[3][3] +
		value[2][1] * value[1][3] * value[3][2] +
		value[3][1] * value[1][2] * value[2][3] -
		value[3][1] * value[1][3] * value[2][2];

	inv.value[1][0] = -value[1][0] * value[2][2] * value[3][3] +
		value[1][0] * value[2][3] * value[3][2] +
		value[2][0] * value[1][2] * value[3][3] -
		value[2][0] * value[1][3] * value[3][2] -
		value[3][0] * value[1][2] * value[2][3] +
		value[3][0] * value[1][3] * value[2][2];

	inv.value[2][0] = value[1][0] * value[2][1] * value[3][3] -
		value[1][0] * value[2][3] * value[3][1] -
		value[2][0] * value[1][1] * value[3][3] +
		value[2][0] * value[1][3] * value[3][1] +
		value[3][0] * value[1][1] * value[2][3] -
		value[3][0] * value[1][3] * value[2][1];

	inv.value[3][0] = -value[1][0] * value[2][1] * value[3][2] +
		value[1][0] * value[2][2] * value[3][1] +
		value[2][0] * value[1][1] * value[3][2] -
		value[2][0] * value[1][2] * value[3][1] -
		value[3][0] * value[1][1] * value[2][2] +
		value[3][0] * value[1][2] * value[2][1];

	inv.value[0][1] = -value[0][1] * value[2][2] * value[3][3] +
		value[0][1] * value[2][3] * value[3][2] +
		value[2][1] * value[0][2] * value[3][3] -
		value[2][1] * value[0][3] * value[3][2] -
		value[3][1] * value[0][2] * value[2][3] +
		value[3][1] * value[0][3] * value[2][2];

	inv.value[1][1] = value[0][0] * value[2][2] * value[3][3] -
		value[0][0] * value[2][3] * value[3][2] -
		value[2][0] * value[0][2] * value[3][3] +
		value[2][0] * value[0][3] * value[3][2] +
		value[3][0] * value[0][2] * value[2][3] -
		value[3][0] * value[0][3] * value[2][2];

	inv.value[2][1] = -value[0][0] * value[2][1] * value[3][3] +
		value[0][0] * value[2][3] * value[3][1] +
		value[2][0] * value[0][1] * value[3][3] -
		value[2][0] * value[0][3] * value[3][1] -
		value[3][0] * value[0][1] * value[2][3] +
		value[3][0] * value[0][3] * value[2][1];

	inv.value[3][1] = value[0][0] * value[2][1] * value[3][2] -
		value[0][0] * value[2][2] * value[3][1] -
		value[2][0] * value[0][1] * value[3][2] +
		value[2][0] * value[0][2] * value[3][1] +
		value[3][0] * value[0][1] * value[2][2] -
		value[3][0] * value[0][2] * value[2][1];

	inv.value[0][2] = value[0][1] * value[1][2] * value[3][3] -
		value[0][1] * value[1][3] * value[3][2] -
		value[1][1] * value[0][2] * value[3][3] +
		value[1][1] * value[0][3] * value[3][2] +
		value[3][1] * value[0][2] * value[1][3] -
		value[3][1] * value[0][3] * value[1][2];

	inv.value[1][2] = -value[0][0] * value[1][2] * value[3][3] +
		value[0][0] * value[1][3] * value[3][2] +
		value[1][0] * value[0][2] * value[3][3] -
		value[1][0] * value[0][3] * value[3][2] -
		value[3][0] * value[0][2] * value[1][3] +
		value[3][0] * value[0][3] * value[1][2];

	inv.value[2][2] = value[0][0] * value[1][1] * value[3][3] -
		value[0][0] * value[1][3] * value[3][1] -
		value[1][0] * value[0][1] * value[3][3] +
		value[1][0] * value[0][3] * value[3][1] +
		value[3][0] * value[0][1] * value[1][3] -
		value[3][0] * value[0][3] * value[1][1];

	inv.value[3][2] = -value[0][0] * value[1][1] * value[3][2] +
		value[0][0] * value[1][2] * value[3][1] +
		value[1][0] * value[0][1] * value[3][2] -
		value[1][0] * value[0][2] * value[3][1] -
		value[3][0] * value[0][1] * value[1][2] +
		value[3][0] * value[0][2] * value[1][1];

	inv.value[0][3] = -value[0][1] * value[1][2] * value[2][3] +
		value[0][1] * value[1][3] * value[2][2] +
		value[1][1] * value[0][2] * value[2][3] -
		value[1][1] * value[0][3] * value[2][2] -
		value[2][1] * value[0][2] * value[1][3] +
		value[2][1] * value[0][3] * value[1][2];

	inv.value[1][3] = value[0][0] * value[1][2] * value[2][3] -
		value[0][0] * value[1][3] * value[2][2] -
		value[1][0] * value[0][2] * value[2][3] +
		value[1][0] * value[0][3] * value[2][2] +
		value[2][0] * value[0][2] * value[1][3] -
		value[2][0] * value[0][3] * value[1][2];

	inv.value[2][3] = -value[0][0] * value[1][1] * value[2][3] +
		value[0][0] * value[1][3] * value[2][1] +
		value[1][0] * value[0][1] * value[2][3] -
		value[1][0] * value[0][3] * value[2][1] -
		value[2][0] * value[0][1] * value[1][3] +
		value[2][0] * value[0][3] * value[1][1];

	inv.value[3][3] = value[0][0] * value[1][1] * value[2][2] -
		value[0][0] * value[1][2] * value[2][1] -
		value[1][0] * value[0][1] * value[2][2] +
		value[1][0] * value[0][2] * value[2][1] +
		value[2][0] * value[0][1] * value[1][2] -
		value[2][0] * value[0][2] * value[1][1];

	float det = value[0][0] * inv.value[0][0] + value[0][1] * inv.value[1][0] + value[0][2] * inv.value[2][0] + value[0][3] * inv.value[3][0];
	if (det == 0)
		return;
	det = 1.f / det;
	*this = inv * det;
}

void Mat4::RotateX(float _theta)
{
	value[0][0] = 1.f;	value[0][1] = 0.f;			value[0][2] = 0.f;				value[0][3] = 0.f;
	value[1][0] = 0.f;	value[1][1] = cosf(_theta);	value[1][2] = -sinf(_theta);	value[1][3] = 0.f;
	value[2][0] = 0.f;	value[2][1] = sinf(_theta);	value[2][2] = cosf(_theta);		value[2][3] = 0.f;
	value[3][0] = 0.f;	value[3][1] = 0.f;			value[3][2] = 0.f;				value[3][3] = 1.f;
}

void Mat4::RotateY(float _theta)
{
	value[0][0] = cosf(_theta);		value[0][1] = 0.f;	value[0][2] = sinf(_theta);		value[0][3] = 0.f;
	value[1][0] = 0.f;				value[1][1] = 1.f;	value[1][2] = 0.f;				value[1][3] = 0.f;
	value[2][0] = -sinf(_theta);	value[2][1] = 0.f;	value[2][2] = cosf(_theta);		value[2][3] = 0.f;
	value[3][0] = 0.f;				value[3][1] = 0.f;	value[3][2] = 0.f;				value[3][3] = 1.f;
}

void Mat4::RotateZ(float _theta)
{
	value[0][0] = cosf(_theta);		value[0][1] = sinf(_theta);	value[0][2] = 0.f;		value[0][3] = 0.f;
	value[1][0] = -sinf(_theta);	value[1][1] = cosf(_theta);	value[1][2] = 0.f;		value[1][3] = 0.f;
	value[2][0] = 0.f;				value[2][1] = 0.f;			value[2][2] = 1.f;		value[2][3] = 0.f;
	value[3][0] = 0.f;				value[3][1] = 0.f;			value[3][2] = 0.f;		value[3][3] = 1.f;
}

void Mat4::Rotate(Vec4 _theta)
{
	*this = Mat4();
	*this *= s_RotateX(_theta[0]);
	*this *= s_RotateY(_theta[1]);
	*this *= s_RotateZ(_theta[2]);
}

void Mat4::Translate(Vec4 _translate)
{
	value[0][0] = 1.f;		value[0][1] = 0.f;		value[0][2] = 0.f;		value[0][3] = _translate[0];
	value[1][0] = 0.f;		value[1][1] = 1.f;		value[1][2] = 0.f;		value[1][3] = _translate[1];
	value[2][0] = 0.f;		value[2][1] = 0.f;		value[2][2] = 1.f;		value[2][3] = _translate[2];
	value[3][0] = 0.f;		value[3][1] = 0.f;		value[3][2] = 0.f;		value[3][3] = _translate[3];
}

void Mat4::Scale(Vec4 _scale)
{
	value[0][0] = _scale[0];	value[0][1] = 0.f;			value[0][2] = 0.f;			value[0][3] = 0.f;
	value[1][0] = 0.f;			value[1][1] = _scale[1];	value[1][2] = 0.f;			value[1][3] = 0.f;
	value[2][0] = 0.f;			value[2][1] = 0.f;			value[2][2] = _scale[2];	value[2][3] = 0.f;
	value[3][0] = 0.f;			value[3][1] = 0.f;			value[3][2] = 0.f;			value[3][3] = _scale[3];
}

void Mat4::TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	*this = Mat4();
	*this *= s_Translate(_translate);
	*this *= s_Rotate(_rotate);
	*this *= s_Scale(_scale);
}

void Mat4::TRS(Vec4 _translate, Vec4 _rotate, Vec4 _scale)
{
	*this = Mat4();
	*this *= s_Translate(_translate);
	*this *= s_Rotate(_rotate);
	*this *= s_Scale(_scale);
}

void Mat4::Print() const
{
	std::cout << "|" << value[0][0] << ", " << value[0][1] << ", " << value[0][2] << ", " << value[0][3] << "|" << std::endl
		<< "|" << value[1][0] << ", " << value[1][1] << ", " << value[1][2] << ", " << value[1][3] << "|" << std::endl
		<< "|" << value[2][0] << ", " << value[2][1] << ", " << value[2][2] << ", " << value[2][3] << "|" << std::endl
		<< "|" << value[3][0] << ", " << value[3][1] << ", " << value[3][2] << ", " << value[3][3] << "|" << std::endl;
}


//####################### STATIC FUNCTIONS #######################

Vec4 Mat4::s_Diagonal(Mat4 _mat)
{
	return { _mat[0][0], _mat[1][1], _mat[2][2], _mat[3][3] };
}

Mat4 Mat4::s_Transpose(Mat4 _mat)
{
	return { _mat[0][0], _mat[1][0], _mat[2][0], _mat[3][0],
			 _mat[0][1], _mat[1][1], _mat[2][1], _mat[3][1],
			 _mat[0][2], _mat[1][2], _mat[2][2], _mat[3][2],
			 _mat[0][3], _mat[1][3], _mat[2][3], _mat[3][3] };
}

float Mat4::s_Trace(Mat4 _mat)
{
	return  _mat[0][0] + _mat[1][1] + _mat[2][2] + _mat[3][3];
}

Mat4 Mat4::s_Opposite(Mat4 _mat)
{
	return { -_mat[0][0], -_mat[0][1], -_mat[0][2], -_mat[0][3],
			 -_mat[1][0], -_mat[1][1], -_mat[1][2], -_mat[1][3],
			 -_mat[2][0], -_mat[2][1], -_mat[2][2], -_mat[2][3],
			 -_mat[3][0], -_mat[3][1], -_mat[3][2], -_mat[3][3] };
}

float Mat4::s_Det(Mat4 _mat)
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

Mat4 Mat4::s_Inverse(Mat4 _mat)
{
	Mat4 inv;
	inv.value[0][0] =   _mat[1][1] * _mat[2][2] * _mat[3][3] -
						_mat[1][1] * _mat[2][3] * _mat[3][2] -
						_mat[2][1] * _mat[1][2] * _mat[3][3] +
						_mat[2][1] * _mat[1][3] * _mat[3][2] +
						_mat[3][1] * _mat[1][2] * _mat[2][3] -
						_mat[3][1] * _mat[1][3] * _mat[2][2];

	inv.value[1][0] =   -_mat[1][0] * _mat[2][2] * _mat[3][3] +
						_mat[1][0] * _mat[2][3] * _mat[3][2] +
						_mat[2][0] * _mat[1][2] * _mat[3][3] -
						_mat[2][0] * _mat[1][3] * _mat[3][2] -
						_mat[3][0] * _mat[1][2] * _mat[2][3] +
						_mat[3][0] * _mat[1][3] * _mat[2][2];

	inv.value[2][0] =   _mat[1][0] * _mat[2][1] * _mat[3][3] -
						_mat[1][0] * _mat[2][3] * _mat[3][1] -
						_mat[2][0] * _mat[1][1] * _mat[3][3] +
						_mat[2][0] * _mat[1][3] * _mat[3][1] +
						_mat[3][0] * _mat[1][1] * _mat[2][3] -
						_mat[3][0] * _mat[1][3] * _mat[2][1];

	inv.value[3][0] =   -_mat[1][0] * _mat[2][1] * _mat[3][2] +
						_mat[1][0] * _mat[2][2] * _mat[3][1] +
						_mat[2][0] * _mat[1][1] * _mat[3][2] -
						_mat[2][0] * _mat[1][2] * _mat[3][1] -
						_mat[3][0] * _mat[1][1] * _mat[2][2] +
						_mat[3][0] * _mat[1][2] * _mat[2][1];

	inv.value[0][1] =   -_mat[0][1] * _mat[2][2] * _mat[3][3] +
						_mat[0][1] * _mat[2][3] * _mat[3][2] +
						_mat[2][1] * _mat[0][2] * _mat[3][3] -
						_mat[2][1] * _mat[0][3] * _mat[3][2] -
						_mat[3][1] * _mat[0][2] * _mat[2][3] +
						_mat[3][1] * _mat[0][3] * _mat[2][2];

	inv.value[1][1] =   _mat[0][0] * _mat[2][2] * _mat[3][3] -
						_mat[0][0] * _mat[2][3] * _mat[3][2] -
						_mat[2][0] * _mat[0][2] * _mat[3][3] +
						_mat[2][0] * _mat[0][3] * _mat[3][2] +
						_mat[3][0] * _mat[0][2] * _mat[2][3] -
						_mat[3][0] * _mat[0][3] * _mat[2][2];

	inv.value[2][1] =   -_mat[0][0] * _mat[2][1] * _mat[3][3] +
						_mat[0][0] * _mat[2][3] * _mat[3][1] +
						_mat[2][0] * _mat[0][1] * _mat[3][3] -
						_mat[2][0] * _mat[0][3] * _mat[3][1] -
						_mat[3][0] * _mat[0][1] * _mat[2][3] +
						_mat[3][0] * _mat[0][3] * _mat[2][1];

	inv.value[3][1] =   _mat[0][0] * _mat[2][1] * _mat[3][2] -
						_mat[0][0] * _mat[2][2] * _mat[3][1] -
						_mat[2][0] * _mat[0][1] * _mat[3][2] +
						_mat[2][0] * _mat[0][2] * _mat[3][1] +
						_mat[3][0] * _mat[0][1] * _mat[2][2] -
						_mat[3][0] * _mat[0][2] * _mat[2][1];

	inv.value[0][2] =   _mat[0][1] * _mat[1][2] * _mat[3][3] -
						_mat[0][1] * _mat[1][3] * _mat[3][2] -
						_mat[1][1] * _mat[0][2] * _mat[3][3] +
						_mat[1][1] * _mat[0][3] * _mat[3][2] +
						_mat[3][1] * _mat[0][2] * _mat[1][3] -
						_mat[3][1] * _mat[0][3] * _mat[1][2];

	inv.value[1][2] =   -_mat[0][0] * _mat[1][2] * _mat[3][3] +
						_mat[0][0] * _mat[1][3] * _mat[3][2] +
						_mat[1][0] * _mat[0][2] * _mat[3][3] -
						_mat[1][0] * _mat[0][3] * _mat[3][2] -
						_mat[3][0] * _mat[0][2] * _mat[1][3] +
						_mat[3][0] * _mat[0][3] * _mat[1][2];

	inv.value[2][2] =   _mat[0][0] * _mat[1][1] * _mat[3][3] -
						_mat[0][0] * _mat[1][3] * _mat[3][1] -
						_mat[1][0] * _mat[0][1] * _mat[3][3] +
						_mat[1][0] * _mat[0][3] * _mat[3][1] +
						_mat[3][0] * _mat[0][1] * _mat[1][3] -
						_mat[3][0] * _mat[0][3] * _mat[1][1];

	inv.value[3][2] =   -_mat[0][0] * _mat[1][1] * _mat[3][2] +
						_mat[0][0] * _mat[1][2] * _mat[3][1] +
						_mat[1][0] * _mat[0][1] * _mat[3][2] -
						_mat[1][0] * _mat[0][2] * _mat[3][1] -
						_mat[3][0] * _mat[0][1] * _mat[1][2] +
						_mat[3][0] * _mat[0][2] * _mat[1][1];

	inv.value[0][3] =   -_mat[0][1] * _mat[1][2] * _mat[2][3] +
						_mat[0][1] * _mat[1][3] * _mat[2][2] +
						_mat[1][1] * _mat[0][2] * _mat[2][3] -
						_mat[1][1] * _mat[0][3] * _mat[2][2] -
						_mat[2][1] * _mat[0][2] * _mat[1][3] +
						_mat[2][1] * _mat[0][3] * _mat[1][2];

	inv.value[1][3] =   _mat[0][0] * _mat[1][2] * _mat[2][3] -
						_mat[0][0] * _mat[1][3] * _mat[2][2] -
						_mat[1][0] * _mat[0][2] * _mat[2][3] +
						_mat[1][0] * _mat[0][3] * _mat[2][2] +
						_mat[2][0] * _mat[0][2] * _mat[1][3] -
						_mat[2][0] * _mat[0][3] * _mat[1][2];

	inv.value[2][3] =   -_mat[0][0] * _mat[1][1] * _mat[2][3] +
						_mat[0][0] * _mat[1][3] * _mat[2][1] +
						_mat[1][0] * _mat[0][1] * _mat[2][3] -
						_mat[1][0] * _mat[0][3] * _mat[2][1] -
						_mat[2][0] * _mat[0][1] * _mat[1][3] +
						_mat[2][0] * _mat[0][3] * _mat[1][1];

	inv.value[3][3] =   _mat[0][0] * _mat[1][1] * _mat[2][2] -
						_mat[0][0] * _mat[1][2] * _mat[2][1] -
						_mat[1][0] * _mat[0][1] * _mat[2][2] +
						_mat[1][0] * _mat[0][2] * _mat[2][1] +
						_mat[2][0] * _mat[0][1] * _mat[1][2] -
						_mat[2][0] * _mat[0][2] * _mat[1][1];

	float det = _mat[0][0] * inv.value[0][0] + _mat[0][1] * inv.value[1][0] + _mat[0][2] * inv.value[2][0] + _mat[0][3] * inv.value[3][0];
	if (det == 0)
		return _mat;
	det = 1.f / det;
	return inv * det;
}

Mat4 Mat4::s_RotateX(float _theta)
{
	return { 1.f,	0.f,			0.f,			0.f,
			 0.f,	cosf(_theta),	-sinf(_theta),	0.f,
			 0.f,	sinf(_theta),	cosf(_theta),	0.f,
			 0.f,	0.f,			0.f,			1.f };
}

Mat4 Mat4::s_RotateY(float _theta)
{
	return { cosf(_theta),	0.f,	sinf(_theta),	0.f,
			 0.f,			1.f,	0.f,			0.f,
			 -sinf(_theta), 0.f,	cosf(_theta),	0.f,
			 0.f,			0.f,	0.f,			1.f };
}

Mat4 Mat4::s_RotateZ(float _theta)
{
	return { cosf(_theta),	sinf(_theta),	0.f,	0.f,
			 -sinf(_theta), cosf(_theta),	0.f,	0.f,
			 0.f,			0.f,			1.f,	0.f,
			 0.f,			0.f,			0.f,	1.f
	};
}

Mat4 Mat4::s_Rotate(Vec3 _theta)
{
	Mat4 mat;
	mat *= s_RotateX(_theta[0]);
	mat *= s_RotateY(_theta[1]);
	mat *= s_RotateZ(_theta[2]);
	return mat;
}

Mat4 Mat4::s_Rotate(Vec4 _theta)
{
	Mat4 mat;
	mat *= s_RotateX(_theta[0]);
	mat *= s_RotateY(_theta[1]);
	mat *= s_RotateZ(_theta[2]);
	return mat;
}

Mat4 Mat4::s_Translate(Vec3 _translate)
{
	return { 1.f,	0.f,	0.f,	_translate[0],
			 0.f,	1.f,	0.f,	_translate[1],
			 0.f,	0.f,	1.f,	_translate[2],
			 0.f,	0.f,	0.f,	1.f };
}

Mat4 Mat4::s_Translate(Vec4 _translate)
{
	return { 1.f,	0.f,	0.f,	_translate[0],
			 0.f,	1.f,	0.f,	_translate[1],
			 0.f,	0.f,	1.f,	_translate[2],
			 0.f,	0.f,	0.f,	_translate[3] };
}

Mat4 Mat4::s_Scale(Vec3 _scale)
{
	return { _scale[0],	0.f,		0.f,		0.f,
			 0.f,		_scale[1],	0.f,		0.f,
			 0.f,		0.f,		_scale[2],	0.f,
			 0.f,		0.f,		0.f,		1.f };
}

Mat4 Mat4::s_Scale(Vec4 _scale)
{
	return { _scale[0],	0.f,		0.f,		0.f,
			 0.f,		_scale[1],	0.f,		0.f,
			 0.f,		0.f,		_scale[2],	0.f,
			 0.f,		0.f,		0.f,		_scale[3] };
}

Mat4 Mat4::s_TRS(Vec3 _translate, Vec3 _rotate, Vec3 _scale)
{
	Mat4 TRS;
	TRS *= s_Translate(_translate);
	TRS *= s_Rotate(_rotate);
	TRS *= s_Scale(_scale);
	return TRS;
}

Mat4 Mat4::s_TRS(Vec4 _translate, Vec4 _rotate, Vec4 _scale)
{
	Mat4 TRS;
	TRS *= s_Translate(_translate);
	TRS *= s_Rotate(_rotate);
	TRS *= s_Scale(_scale);
	return TRS;
}

void Mat4::s_Print(Mat4 _mat)
{
	std::cout << "|" << _mat[0][0] << ", " << _mat[0][1] << ", " << _mat[0][2] << ", " << _mat[0][3] << "|" << std::endl
		<< "|" << _mat[1][0] << ", " << _mat[1][1] << ", " << _mat[1][2] << ", " << _mat[1][3] << "|" << std::endl
		<< "|" << _mat[2][0] << ", " << _mat[2][1] << ", " << _mat[2][2] << ", " << _mat[2][3] << "|" << std::endl
		<< "|" << _mat[3][0] << ", " << _mat[3][1] << ", " << _mat[3][2] << ", " << _mat[3][3] << "|" << std::endl;
}


//####################### OPERATORS #######################

Mat4 Mat4::operator+(float _scalar) const
{
	return { value[0][0] + _scalar, value[0][1] + _scalar, value[0][2] + _scalar, value[0][3] + _scalar,
			 value[1][0] + _scalar, value[1][1] + _scalar, value[1][2] + _scalar, value[1][3] + _scalar,
			 value[2][0] + _scalar, value[2][1] + _scalar, value[2][2] + _scalar, value[2][3] + _scalar,
			 value[3][0] + _scalar, value[3][1] + _scalar, value[3][2] + _scalar, value[3][3] + _scalar };
}

Mat4 Mat4::operator+(Mat4 _mat) const
{
	return { value[0][0] + _mat[0][0], value[0][1] + _mat[0][1], value[0][2] + _mat[0][2], value[0][3] + _mat[0][3],
			 value[1][0] + _mat[1][0], value[1][1] + _mat[1][1], value[1][2] + _mat[1][2], value[1][3] + _mat[1][3],
			 value[2][0] + _mat[2][0], value[2][1] + _mat[2][1], value[2][2] + _mat[2][2], value[2][3] + _mat[2][3],
			 value[3][0] + _mat[3][0], value[3][1] + _mat[3][1], value[3][2] + _mat[3][2], value[3][3] + _mat[3][3] };
}

Mat4 Mat4::operator-(float _scalar) const
{
	return { value[0][0] - _scalar, value[0][1] - _scalar, value[0][2] - _scalar, value[0][3] - _scalar,
			 value[1][0] - _scalar, value[1][1] - _scalar, value[1][2] - _scalar, value[1][3] - _scalar,
			 value[2][0] - _scalar, value[2][1] - _scalar, value[2][2] - _scalar, value[2][3] - _scalar,
			 value[3][0] - _scalar, value[3][1] - _scalar, value[3][2] - _scalar, value[3][3] - _scalar };
}

Mat4 Mat4::operator-(Mat4 _mat) const
{
	return { value[0][0] - _mat[0][0], value[0][1] - _mat[0][1], value[0][2] - _mat[0][2], value[0][3] - _mat[0][3],
			 value[1][0] - _mat[1][0], value[1][1] - _mat[1][1], value[1][2] - _mat[1][2], value[1][3] - _mat[1][3],
			 value[2][0] - _mat[2][0], value[2][1] - _mat[2][1], value[2][2] - _mat[2][2], value[2][3] - _mat[2][3],
			 value[3][0] - _mat[3][0], value[3][1] - _mat[3][1], value[3][2] - _mat[3][2], value[3][3] - _mat[3][3] };
}

Mat4 Mat4::operator*(float _scalar) const
{
	return { value[0][0] * _scalar, value[0][1] * _scalar, value[0][2] * _scalar, value[0][3] * _scalar,
			 value[1][0] * _scalar, value[1][1] * _scalar, value[1][2] * _scalar, value[1][3] * _scalar,
			 value[2][0] * _scalar, value[2][1] * _scalar, value[2][2] * _scalar, value[2][3] * _scalar,
			 value[3][0] * _scalar, value[3][1] * _scalar, value[3][2] * _scalar, value[3][3] * _scalar };
}

Vec4 Mat4::operator*(Vec3 _vec) const
{
	return { value[0][0] * _vec[0] + value[0][1] * _vec[1] + value[0][2] * _vec[2],
			 value[1][0] * _vec[0] + value[1][1] * _vec[1] + value[1][2] * _vec[2],
			 value[2][0] * _vec[0] + value[2][1] * _vec[1] + value[2][2] * _vec[2],
			 value[3][0] * _vec[0] + value[3][1] * _vec[1] + value[3][2] * _vec[2] };
}

Vec4 Mat4::operator*(Vec4 _vec) const
{
	return { value[0][0] * _vec[0] + value[0][1] * _vec[1] + value[0][2] * _vec[2] + value[0][3] * _vec[3],
			 value[1][0] * _vec[0] + value[1][1] * _vec[1] + value[1][2] * _vec[2] + value[1][3] * _vec[3],
			 value[2][0] * _vec[0] + value[2][1] * _vec[1] + value[2][2] * _vec[2] + value[2][3] * _vec[3],
			 value[3][0] * _vec[0] + value[3][1] * _vec[1] + value[3][2] * _vec[2] + value[3][3] * _vec[3] };
}

Mat4 Mat4::operator*(Mat4 _mat) const
{
	return { value[0][0] * _mat[0][0] + value[0][1] * _mat[1][0] + value[0][2] * _mat[2][0] + value[0][3] * _mat[3][0],
			 value[0][0] * _mat[0][1] + value[0][1] * _mat[1][1] + value[0][2] * _mat[2][1] + value[0][3] * _mat[3][1],
			 value[0][0] * _mat[0][2] + value[0][1] * _mat[1][2] + value[0][2] * _mat[2][2] + value[0][3] * _mat[3][2],
			 value[0][0] * _mat[0][3] + value[0][1] * _mat[1][3] + value[0][2] * _mat[2][3] + value[0][3] * _mat[3][3],

			 value[1][0] * _mat[0][0] + value[1][1] * _mat[1][0] + value[1][2] * _mat[2][0] + value[1][3] * _mat[3][0],
			 value[1][0] * _mat[0][1] + value[1][1] * _mat[1][1] + value[1][2] * _mat[2][1] + value[1][3] * _mat[3][1],
			 value[1][0] * _mat[0][2] + value[1][1] * _mat[1][2] + value[1][2] * _mat[2][2] + value[1][3] * _mat[3][2],
			 value[1][0] * _mat[0][3] + value[1][1] * _mat[1][3] + value[1][2] * _mat[2][3] + value[1][3] * _mat[3][3],

			 value[2][0] * _mat[0][0] + value[2][1] * _mat[1][0] + value[2][2] * _mat[2][0] + value[2][3] * _mat[3][0],
			 value[2][0] * _mat[0][1] + value[2][1] * _mat[1][1] + value[2][2] * _mat[2][1] + value[2][3] * _mat[3][1],
			 value[2][0] * _mat[0][2] + value[2][1] * _mat[1][2] + value[2][2] * _mat[2][2] + value[2][3] * _mat[3][2],
			 value[2][0] * _mat[0][3] + value[2][1] * _mat[1][3] + value[2][2] * _mat[2][3] + value[2][3] * _mat[3][3],

			 value[3][0] * _mat[0][0] + value[3][1] * _mat[1][0] + value[3][2] * _mat[2][0] + value[3][3] * _mat[3][0],
			 value[3][0] * _mat[0][1] + value[3][1] * _mat[1][1] + value[3][2] * _mat[2][1] + value[3][3] * _mat[3][1],
			 value[3][0] * _mat[0][2] + value[3][1] * _mat[1][2] + value[3][2] * _mat[2][2] + value[3][3] * _mat[3][2],
			 value[3][0] * _mat[0][3] + value[3][1] * _mat[1][3] + value[3][2] * _mat[2][3] + value[3][3] * _mat[3][3] };
}

void Mat4::operator+=(float _scalar)
{
	value[0][0] += _scalar;	value[0][1] += _scalar;	value[0][2] += _scalar;	value[0][3] += _scalar;
	value[1][0] += _scalar;	value[1][1] += _scalar;	value[1][2] += _scalar;	value[1][3] += _scalar;
	value[2][0] += _scalar;	value[2][1] += _scalar;	value[2][2] += _scalar;	value[2][3] += _scalar;
	value[3][0] += _scalar;	value[3][1] += _scalar;	value[3][2] += _scalar;	value[3][3] += _scalar;
}

void Mat4::operator+=(Mat4 _mat)
{
	value[0][0] += _mat[0][0];	value[0][1] += _mat[0][1];	value[0][2] += _mat[0][2];	value[0][3] += _mat[0][3];
	value[1][0] += _mat[1][0];	value[1][1] += _mat[1][1];	value[1][2] += _mat[1][2];	value[1][3] += _mat[1][3];
	value[2][0] += _mat[2][0];	value[2][1] += _mat[2][1];	value[2][2] += _mat[2][2];	value[2][3] += _mat[2][3];
	value[3][0] += _mat[3][0];	value[3][1] += _mat[3][1];	value[3][2] += _mat[3][2];	value[3][3] += _mat[3][3];
}

void Mat4::operator-=(float _scalar)
{
	value[0][0] -= _scalar;	value[0][1] -= _scalar;	value[0][2] -= _scalar;	value[0][3] -= _scalar;
	value[1][0] -= _scalar;	value[1][1] -= _scalar;	value[1][2] -= _scalar;	value[1][3] -= _scalar;
	value[2][0] -= _scalar;	value[2][1] -= _scalar;	value[2][2] -= _scalar;	value[2][3] -= _scalar;
	value[3][0] -= _scalar;	value[3][1] -= _scalar;	value[3][2] -= _scalar;	value[3][3] -= _scalar;
}

void Mat4::operator-=(Mat4 _mat)
{
	value[0][0] -= _mat[0][0];	value[0][1] -= _mat[0][1];	value[0][2] -= _mat[0][2];	value[0][3] -= _mat[0][3];
	value[1][0] -= _mat[1][0];	value[1][1] -= _mat[1][1];	value[1][2] -= _mat[1][2];	value[1][3] -= _mat[1][3];
	value[2][0] -= _mat[2][0];	value[2][1] -= _mat[2][1];	value[2][2] -= _mat[2][2];	value[2][3] -= _mat[2][3];
	value[3][0] -= _mat[3][0];	value[3][1] -= _mat[3][1];	value[3][2] -= _mat[3][2];	value[3][3] -= _mat[3][3];
}

void Mat4::operator*=(float _scalar)
{
	value[0][0] *= _scalar;		value[0][1] *= _scalar;		value[0][2] *= _scalar;		value[0][3] *= _scalar;
	value[1][0] *= _scalar;		value[1][1] *= _scalar;		value[1][2] *= _scalar;		value[1][3] *= _scalar;
	value[2][0] *= _scalar;		value[2][1] *= _scalar;		value[2][2] *= _scalar;		value[2][3] *= _scalar;
	value[3][0] *= _scalar;		value[3][1] *= _scalar;		value[3][2] *= _scalar;		value[3][3] *= _scalar;
}

void Mat4::operator*=(Mat4 _mat)
{
	float temp00 = value[0][0]; float temp01 = value[0][1]; float temp02 = value[0][2]; float temp03 = value[0][3];
	float temp10 = value[1][0]; float temp11 = value[1][1]; float temp12 = value[1][2]; float temp13 = value[1][3];
	float temp20 = value[2][0]; float temp21 = value[2][1]; float temp22 = value[2][2]; float temp23 = value[2][3];
	float temp30 = value[3][0]; float temp31 = value[3][1]; float temp32 = value[3][2]; float temp33 = value[3][3];

	value[0][0] = temp00 * _mat[0][0] + temp01 * _mat[1][0] + temp02 * _mat[2][0] + temp03 * _mat[3][0];
	value[0][1] = temp00 * _mat[0][1] + temp01 * _mat[1][1] + temp02 * _mat[2][1] + temp03 * _mat[3][1];
	value[0][2] = temp00 * _mat[0][2] + temp01 * _mat[1][2] + temp02 * _mat[2][2] + temp03 * _mat[3][2];
	value[0][3] = temp00 * _mat[0][3] + temp01 * _mat[1][3] + temp02 * _mat[2][3] + temp03 * _mat[3][3];

	value[1][0] = temp10 * _mat[0][0] + temp11 * _mat[1][0] + temp12 * _mat[2][0] + temp13 * _mat[3][0];
	value[1][1] = temp10 * _mat[0][1] + temp11 * _mat[1][1] + temp12 * _mat[2][1] + temp13 * _mat[3][1];
	value[1][2] = temp10 * _mat[0][2] + temp11 * _mat[1][2] + temp12 * _mat[2][2] + temp13 * _mat[3][2];
	value[1][3] = temp10 * _mat[0][3] + temp11 * _mat[1][3] + temp12 * _mat[2][3] + temp13 * _mat[3][3];

	value[2][0] = temp20 * _mat[0][0] + temp21 * _mat[1][0] + temp22 * _mat[2][0] + temp23 * _mat[3][0];
	value[2][1] = temp20 * _mat[0][1] + temp21 * _mat[1][1] + temp22 * _mat[2][1] + temp23 * _mat[3][1];
	value[2][2] = temp20 * _mat[0][2] + temp21 * _mat[1][2] + temp22 * _mat[2][2] + temp23 * _mat[3][2];
	value[2][3] = temp20 * _mat[0][3] + temp21 * _mat[1][3] + temp22 * _mat[2][3] + temp23 * _mat[3][3];

	value[3][0] = temp30 * _mat[0][0] + temp31 * _mat[1][0] + temp32 * _mat[2][0] + temp33 * _mat[3][0];
	value[3][1] = temp30 * _mat[0][1] + temp31 * _mat[1][1] + temp32 * _mat[2][1] + temp33 * _mat[3][1];
	value[3][2] = temp30 * _mat[0][2] + temp31 * _mat[1][2] + temp32 * _mat[2][2] + temp33 * _mat[3][2];
	value[3][3] = temp30 * _mat[0][3] + temp31 * _mat[1][3] + temp32 * _mat[2][3] + temp33 * _mat[3][3];
}

Vec4 Mat4::operator[](int _i) const
{
	if (_i == 0 || _i == 1 || _i == 2 || _i == 3)
		return { value[_i][0], value[_i][1], value[_i][2], value[_i][3] };
	return { NAN, NAN, NAN, NAN }; // TODO Replace
}

void Mat4::operator=(float _scalar)
{
	value[0][0] = _scalar;		value[0][1] = _scalar;		value[0][2] = _scalar;		value[0][3] = _scalar;
	value[1][0] = _scalar;		value[1][1] = _scalar;		value[1][2] = _scalar;		value[1][3] = _scalar;
	value[2][0] = _scalar;		value[2][1] = _scalar;		value[2][2] = _scalar;		value[2][3] = _scalar;
	value[3][0] = _scalar;		value[3][1] = _scalar;		value[3][2] = _scalar;		value[3][3] = _scalar;
}

void Mat4::operator=(Mat4 _mat)
{
	value[0][0] = _mat[0][0];		value[0][1] = _mat[0][1];		value[0][2] = _mat[0][2];		value[0][3] = _mat[0][3];
	value[1][0] = _mat[1][0];		value[1][1] = _mat[1][1];		value[1][2] = _mat[1][2];		value[1][3] = _mat[1][3];
	value[2][0] = _mat[2][0];		value[2][1] = _mat[2][1];		value[2][2] = _mat[2][2];		value[2][3] = _mat[2][3];
	value[3][0] = _mat[3][0];		value[3][1] = _mat[3][1];		value[3][2] = _mat[3][2];		value[3][3] = _mat[3][3];
}

bool Mat4::operator==(Mat4 _mat) const
{
	return	fabs(value[0][0] - _mat[0][0]) <= Tools::epsilon && fabs(value[0][1] - _mat[0][1]) <= Tools::epsilon && fabs(value[0][2] - _mat[0][2]) <= Tools::epsilon && fabs(value[0][3] - _mat[0][3]) <= Tools::epsilon &&
			fabs(value[1][0] - _mat[1][0]) <= Tools::epsilon && fabs(value[1][1] - _mat[1][1]) <= Tools::epsilon && fabs(value[1][2] - _mat[1][2]) <= Tools::epsilon && fabs(value[1][3] - _mat[1][3]) <= Tools::epsilon &&
			fabs(value[2][0] - _mat[2][0]) <= Tools::epsilon && fabs(value[2][1] - _mat[2][1]) <= Tools::epsilon && fabs(value[2][2] - _mat[2][2]) <= Tools::epsilon && fabs(value[2][3] - _mat[2][3]) <= Tools::epsilon &&
			fabs(value[3][0] - _mat[3][0]) <= Tools::epsilon && fabs(value[3][1] - _mat[3][1]) <= Tools::epsilon && fabs(value[3][2] - _mat[3][2]) <= Tools::epsilon && fabs(value[3][3] - _mat[3][3]) <= Tools::epsilon;
}

bool Mat4::operator!=(Mat4 _mat) const
{
	return	fabs(value[0][0] - _mat[0][0]) >= Tools::epsilon || fabs(value[0][1] - _mat[0][1]) >= Tools::epsilon || fabs(value[0][2] - _mat[0][2]) >= Tools::epsilon || fabs(value[0][3] - _mat[0][3]) >= Tools::epsilon ||
			fabs(value[1][0] - _mat[1][0]) >= Tools::epsilon || fabs(value[1][1] - _mat[1][1]) >= Tools::epsilon || fabs(value[1][2] - _mat[1][2]) >= Tools::epsilon || fabs(value[1][3] - _mat[1][3]) >= Tools::epsilon ||
			fabs(value[2][0] - _mat[2][0]) >= Tools::epsilon || fabs(value[2][1] - _mat[2][1]) >= Tools::epsilon || fabs(value[2][2] - _mat[2][2]) >= Tools::epsilon || fabs(value[2][3] - _mat[2][3]) >= Tools::epsilon ||
			fabs(value[3][0] - _mat[3][0]) >= Tools::epsilon || fabs(value[3][1] - _mat[3][1]) >= Tools::epsilon || fabs(value[3][2] - _mat[3][2]) >= Tools::epsilon || fabs(value[3][3] - _mat[3][3]) >= Tools::epsilon;
}