#include "Quat.hpp"
#include "Tools.hpp"
#include "Vec3.hpp"
#include <iostream>
#include <algorithm>
using namespace Math;

Quat::Quat(float _w, float _x, float _y, float _z)
{
	if (fabsf(_w) > Tools::epsilon)
		w = static_cast<float>(_w);

	if (fabsf(_x) > Tools::epsilon)
		x = static_cast<float>(_x);

	if (fabsf(_y) > Tools::epsilon)
		y = static_cast<float>(_y);

	if (fabsf(_z) > Tools::epsilon)
		z = static_cast<float>(_z);
}

Quat::Quat(float _w, Vec3 _v)
{
	if (fabsf(_w) > Tools::epsilon)
		w = static_cast<float>(_w);

	if (fabsf(_v.x) > Tools::epsilon)
		x = static_cast<float>(_v.x);

	if (fabsf(_v.y) > Tools::epsilon)
		y = static_cast<float>(_v.y);

	if (fabsf(_v.z) > Tools::epsilon)
		z = static_cast<float>(_v.z);
}

Quat Quat::QuaternionEuler(float yaw, float pitch, float roll)
{
	if (fabsf(yaw) > Tools::epsilon)
		yaw = Tools::ToRad(static_cast<float>(yaw));

	if (fabsf(pitch) > Tools::epsilon)
		pitch = Tools::ToRad(static_cast<float>(pitch));

	if (fabsf(roll) > Tools::epsilon)
		roll = Tools::ToRad(static_cast<float>(roll));

	float cr = cos(roll * 0.5f);
	float sr = sin(roll * 0.5f);
	float cp = cos(pitch * 0.5f);
	float sp = sin(pitch * 0.5f);
	float cy = cos(yaw * 0.5f);
	float sy = sin(yaw * 0.5f);

	Quat q = Quat::Identity();
	q.w = cr * cp * cy - sr * sp * sy;
	q.x = cr * cp * sy + sr * sp * cy;
	q.y = cr * sp * cy - sr * cp * sy;
	q.z = sr * cp * cy + cr * sp * sy;


	return q;
}

void Quat::Print() const
{
	std::cout << "Quaternion(" << w << ", " << x << ", " << y << ", " << z << ")" << std::endl;
}

void Quat::SetIdentity()
{
	w = 1.f;
	x = y = z = 0.f;
}

Vec3 Quat::GetEulerAnglesDegXYZ() const
{
	Quat q = Quat::Normalized(*this);

	float aa = q.w * q.w, bb = q.x * q.x, cc = q.y * q.y, dd = q.z * q.z;

	float m00 = aa + bb - cc - dd;
	float m01 = 2.f * (q.x * q.y - q.w * q.z);
	float m02 = 2.f * (q.x * q.z + q.w * q.y);
	float m11 = aa - bb + cc - dd;
	float m12 = 2.f * (q.y * q.z - q.w * q.x);
	float m21 = 2.f * (q.y * q.z + q.w * q.x);
	float m22 = aa - bb - cc + dd;

	if (fabs(m02) < 1.0f)
		return Vec3
		(
			Tools::ToDeg(atan2f(-m12, m22)),
			Tools::ToDeg(asinf(m02)),
			Tools::ToDeg(atan2f(-m01, m00))
		);

	// Gimbal lock (full rotation around X)
	else
		return Vec3
		(
			Tools::ToDeg(atan2f(m21, m11)),
			(m02 > 0.0f) ? Tools::ToDeg(Tools::PI / 2.f) : Tools::ToDeg(-Tools::PI / 2.f),
			0.0f
		);
}

Vec3 Quat::GetEulerAnglesRadXYZ() const
{
	Quat q = Quat::Normalized(*this);

	float aa = q.w * q.w, bb = q.x * q.x, cc = q.y * q.y, dd = q.z * q.z;

	float m00 = aa + bb - cc - dd;
	float m01 = 2.f * (q.x * q.y - q.w * q.z);
	float m02 = 2.f * (q.x * q.z + q.w * q.y);
	float m11 = aa - bb + cc - dd;
	float m12 = 2.f * (q.y * q.z - q.w * q.x);
	float m21 = 2.f * (q.y * q.z + q.w * q.x);
	float m22 = aa - bb - cc + dd;

	if (fabs(m02) < 1.0f)
		return Vec3
		(
			atan2f(-m12, m22),
			asinf(m02),
			atan2f(-m01, m00)
		);

	// Gimbal lock (full rotation around X)
	else
		return Vec3
		(
			atan2f(m21, m11),
			(m02 > 0.0f) ? Tools::PI / 2.f : -Tools::PI / 2.f,
			0.0f
		);
}

Vec3 Quat::GetEulerAnglesRadZYX() const
{
	Quat q = Quat::Normalized(*this);

	Vec3 angles{ 0.f, 0.f, 0.f };

	// roll (x-axis rotation)
	float sinr_cosp = 2.f * (q.w * q.x + q.y * q.z);
	float cosr_cosp = 1.f - 2.f * (q.x * q.x + q.y * q.y);
	angles.x = atan2f(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	float sinp = sqrt(1.f + 2.f * (q.w * q.y - q.x * q.z));
	float cosp = sqrt(1.f - 2.f * (q.w * q.y - q.x * q.z));
	angles.y = 2.f * atan2f(sinp, cosp) - Tools::PI / 2.f;

	// yaw (z-axis rotation)
	float siny_cosp = 2.f * (q.w * q.z + q.x * q.y);
	float cosy_cosp = 1.f - 2.f * (q.y * q.y + q.z * q.z);
	angles.z = atan2f(siny_cosp, cosy_cosp);

	return angles;
}

Vec3 Quat::GetEulerAnglesDegZYX() const
{
	Quat q = Quat::Normalized(*this);

	Vec3 angles{ 0.f, 0.f, 0.f };

	// roll (x-axis rotation)
	float sinr_cosp = 2.f * (q.w * q.x + q.y * q.z);
	float cosr_cosp = 1.f - 2.f * (q.x * q.x + q.y * q.y);
	angles.x = Tools::ToDeg(atan2f(sinr_cosp, cosr_cosp));

	// pitch (y-axis rotation)
	float sinp = sqrt(1.f + 2.f * (q.w * q.y - q.x * q.z));
	float cosp = sqrt(1.f - 2.f * (q.w * q.y - q.x * q.z));
	angles.y = Tools::ToDeg(2.f * atan2f(sinp, cosp) - Tools::PI / 2.f);

	// yaw (z-axis rotation)
	float siny_cosp = 2.f * (q.w * q.z + q.x * q.y);
	float cosy_cosp = 1.f - 2.f * (q.y * q.y + q.z * q.z);
	angles.z = Tools::ToDeg(atan2f(siny_cosp, cosy_cosp));

	return angles;
}

float Quat::Norm() const
{
	return sqrt(w * w + x * x + y * y + z * z);
}

void Quat::Normalize()
{
	float d = Norm();
	if (d >= Tools::epsilon)
	{
		w /= d;
		x /= d;
		y /= d;
		z /= d;
	}
}

float Quat::DotProduct(Quat _q1) const
{
	return _q1.w * w + _q1.x * x + _q1.y * y + _q1.z * z;
}

void Quat::Inverse()
{
	if (Norm() <= Tools::epsilon)
	{
		printf("Can't be inverted");
	}
	float n = Norm() * Norm();

	w /= n;
	x = -x / n;
	y = -y / n;
	z = -z / n;
}

void Quat::HamiltonProduct(Quat _q1)
{
	float a1 = w;
	float a2 = _q1.w;
	Vec3 v1(x, y, z);
	Vec3 v2(_q1.x, _q1.y, _q1.z);

	w = a1 * a2 - Vec3::DotProduct(v1, v2);
	Vec3 v = v2 * a1 + v1 * a2 + Vec3::CrossProduct(v1, v2);
	x = v.x;
	y = v.y;
	z = v.z;
}

void Quat::Rotate(Quat _q1)
{
	Quat q = Normalized(_q1);
	*this = q * *this * Conjugate(q);
}

Vec3 Quat::Rotate(Vec3 _v) const
{
	Quat r = Quat::Rotate(Quat(0.f, _v), Quat::Normalized(*this));
	return Vec3(r.x, r.y, r.z);
}

Mat3 Quat::QuatToMatrix() const
{
	return Mat3
	(
		2.f * (w * w + x * x) - 1.f, 2.f * (x * y - z * w), 2.f * (x * z + y * w),
		2.f * (x * y + z * w), 2.f * (w * w + y * y) - 1.f, 2.f * (y * z - x * w),
		2.f * (x * z - y * w), 2.f * (y * z + x * w), 2.f * (w * w + z * z) - 1.f
	);
}

Mat4 Quat::GetTransformMatrix(Vec3 _translation) const
{
	Mat3 rot = Quat::QuatToMatrix(*this);
	return Mat4
	(
		rot[0][0], rot[0][1], rot[0][2], _translation.x,
		rot[1][0], rot[1][1], rot[1][2], _translation.y,
		rot[2][0], rot[2][1], rot[2][2], _translation.z,
		0.f, 0.f, 0.f, 1.f
	);
}

void Quat::Slerp(Quat _q2, float _t)
{
	float dot = Quat::DotProduct(*this, _q2);
	Quat q2Copy = _q2;

	if (dot < 0.0f)
	{
		dot = -dot;
		q2Copy = -_q2;
	}

	if (dot > 1.f - Tools::epsilon)
	{
		*this = *this * (1.0f - _t) + q2Copy * _t;
		return;
	}

	float theta = acosf(dot);
	float sinTheta = sqrtf(1.0f - dot * dot);

	float factor1 = sinf((1.0f - _t) * theta) / sinTheta;
	float factor2 = sinf(_t * theta) / sinTheta;


	w = factor1 * w + factor2 * q2Copy.w;
	x = factor1 * x + factor2 * q2Copy.x;
	y = factor1 * y + factor2 * q2Copy.y;
	z = factor1 * z + factor2 * q2Copy.z;
}

//####################### OPERATORS #######################

Quat Quat::operator*(Quat _q) const
{
	return Quat
	(
		w * _q.w - x * _q.x - y * _q.y - z * _q.z,
		x * _q.w + w * _q.x - z * _q.y + y * _q.z,
		y * _q.w + z * _q.x + w * _q.y - x * _q.z,
		z * _q.w - y * _q.x + x * _q.y + w * _q.z
	);
}
Quat Quat::operator*(float _f) const
{
	return Quat(w * _f, x * _f, y * _f, z * _f);
}
Quat Quat::operator/(float _f) const
{
	if (_f <= Tools::epsilon)
		return Quat::Identity();
	return Quat(w / _f, x / _f, y / _f, z / _f);
}
void Quat::operator/=(float _f)
{
	if (_f <= Tools::epsilon)
		return;
	w /= _f;
	x /= _f;
	y /= _f;
	z /= _f;
}


//####################### STATIC FUNCTIONS #######################

void Quat::Print(Quat _q)
{
	std::cout << "Quaternion(" << _q.w << ", " << _q.x << ", " << _q.y << ", " << _q.z << ")" << std::endl;
}

Vec3 Quat::GetEulerAngles(Quat _q)
{
	Quat q = Quat::Normalized(_q);

	float aa = q.w * q.w, bb = q.x * q.x, cc = q.y * q.y, dd = q.z * q.z;

	float m00 = aa + bb - cc - dd;
	float m01 = 2.f * (q.x * q.y - q.w * q.z);
	float m02 = 2.f * (q.x * q.z + q.w * q.y);
	float m11 = aa - bb + cc - dd;
	float m12 = 2.f * (q.y * q.z - q.w * q.x);
	float m21 = 2.f * (q.y * q.z + q.w * q.x);
	float m22 = aa - bb - cc + dd;


	if (fabs(m02) < 1.0f)
		return Vec3
		(
			Tools::ToDeg(atan2f(-m12, m22)),
			Tools::ToDeg(asinf(m02)),
			Tools::ToDeg(atan2f(-m01, m00))
		);

	// Gimbal lock (full rotation around X)
	else
		return Vec3
		(
			Tools::ToDeg(atan2f(m21, m11)),
			(m02 > 0.0f) ? Tools::ToDeg(Tools::PI / 2.f) : Tools::ToDeg(-Tools::PI / 2.f),
			0.0f
		);
}

float Quat::Norm(Quat _q)
{
	return sqrt(_q.w * _q.w + _q.x * _q.x + _q.y * _q.y + _q.z * _q.z);
}

Quat Quat::Normalized(Quat _q)
{
	float d = _q.Norm();
	if (d >= Tools::epsilon)
		return Quat
		(
			_q.w /= d,
			_q.x /= d,
			_q.y /= d,
			_q.z /= d
		);
	return _q;
}

float Quat::DotProduct(Quat _q1, Quat _q2)
{
	return _q1.w * _q2.w + _q1.x * _q2.x + _q1.y * _q2.y + _q1.z * _q2.z;
}

Quat Quat::Inverse(Quat _q)
{
	if (_q.Norm() <= Tools::epsilon)
	{
		printf("Can't be inverted");
		return Quat::Identity();
	}
	float n = _q.Norm() * _q.Norm();

	return Quat(_q.w / n, -_q.x / n, -_q.y / n, -_q.z / n);
}

Quat Quat::HamiltonProduct(Quat _q1, Quat _q2)
{
	float a1 = _q1.w;
	float a2 = _q2.w;
	Vec3 v1(_q1.x, _q1.y, _q1.z);
	Vec3 v2(_q2.x, _q2.y, _q2.z);

	float a = a1 * a2 - Vec3::DotProduct(v1, v2);
	Vec3 v = v2 * a1 + v1 * a2 + Vec3::CrossProduct(v1, v2);

	return Quat(a, v);
}

Quat Quat::Rotate(Quat _q1, Quat _q2)
{
	Quat nQ = Normalized(_q2);
	Quat q = nQ * _q1 * Quat::Conjugate(nQ);
	return q;
}

Vec3 Quat::Rotate(Vec3 _v, Quat _q)
{
	Quat r = Quat::Rotate(Quat(0.f, _v), Quat::Normalized(_q));
	return Vec3(r.x, r.y, r.z);
}

Mat3 Quat::QuatToMatrix(Quat _q)
{
	Quat q = Normalized(_q);
	return Mat3
	(
		2.f * (q.w * q.w + q.x * q.x) - 1.f, 2.f * (q.x * q.y - q.z * q.w), 2.f * (q.x * q.z + q.y * q.w),
		2.f * (q.x * q.y + q.z * q.w), 2.f * (q.w * q.w + q.y * q.y) - 1.f, 2.f * (q.y * q.z - q.x * q.w),
		2.f * (q.x * q.z - q.y * q.w), 2.f * (q.y * q.z + q.x * q.w), 2.f * (q.w * q.w + q.z * q.z) - 1.f
	);
}

Mat4 Quat::GetTransformMatrix(Vec3 _translation, Quat _rotation)
{
	Mat3 rot = Quat::QuatToMatrix(_rotation);
	return Mat4
	(
		rot[0][0], rot[0][1], rot[0][2], _translation.x,
		rot[1][0], rot[1][1], rot[1][2], _translation.y,
		rot[2][0], rot[2][1], rot[2][2], _translation.z,
		0.f, 0.f, 0.f, 1.f
	);
}

Quat Quat::Slerp(Quat _q1, Quat _q2, float _t)
{
	float dot = Quat::DotProduct(_q1, _q2);
	Quat q2Copy = _q2;

	if (dot < 0.0f)
	{
		dot = -dot;
		q2Copy = -_q2;
	}

	if (dot > 1.f - Tools::epsilon)
		return _q1 * (1.0f - _t) + q2Copy * _t;

	float theta = acosf(dot);
	float sinTheta = sqrtf(1.0f - dot * dot);

	float factor1 = sinf((1.0f - _t) * theta) / sinTheta;
	float factor2 = sinf(_t * theta) / sinTheta;

	return {
		factor1 * _q1.w + factor2 * q2Copy.w,
		factor1 * _q1.x + factor2 * q2Copy.x,
		factor1 * _q1.y + factor2 * q2Copy.y,
		factor1 * _q1.z + factor2 * q2Copy.z };
}