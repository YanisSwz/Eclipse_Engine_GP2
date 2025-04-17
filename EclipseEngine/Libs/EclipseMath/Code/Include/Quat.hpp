#pragma once
#include "Vec3.hpp"
#include "Mat3.hpp"

namespace Math
{
	class Mat4;

	class Quat
	{
	public:

		//Constructors and destructor
		Quat(float _w = 1.f, float _x = 0.f, float _y = 0.f, float _z = 0.f);
		Quat(float _w = 1.f, Vec3 _v = Vec3());
		~Quat() = default;

		// Variables
		float w = 0.f;
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		// Operators
		inline Quat operator+(Quat _q) const { return Quat(w + _q.w, x + _q.x, y + _q.y, z + _q.z); }
		inline Quat operator-(Quat _q) const { return Quat(w - _q.w, x - _q.x, y - _q.y, z - _q.z); }
		inline Quat operator-() { return Quat(-w, -x, -y, -z); };
		inline void operator+=(Quat _q) { *this = *this + _q; };
		inline void operator-=(Quat _q) { *this = *this - _q; };
		Quat operator*(Quat _q) const;
		Quat operator*(float _f) const;
		Quat operator/(float _f) const;
		inline void operator*=(Quat _q) { *this = *this * _q; };
		inline void operator*=(float _f) { w *= _f; x *= _f; y *= _f; z *= _f; };
		void operator/=(float _f);

		// Functions
		void Print() const;
		void SetIdentity();
		Vec3 GetEulerAnglesDegXYZ() const;
		Vec3 GetEulerAnglesRadXYZ() const;
		Vec3 GetEulerAnglesDegZYX() const;
		Vec3 GetEulerAnglesRadZYX() const;
		float Norm() const;
		void Normalize();
		float DotProduct(Quat _q1) const;
		void Inverse();
		inline void Conjugate() { x = -x; y = -y; z = -z; }
		void HamiltonProduct(Quat _q1);
		void Rotate(Quat _q1);
		Vec3 Rotate(Vec3 _v) const;
		Mat3 QuatToMatrix() const;
		Mat4 GetTransformMatrix(Vec3 _translation) const;
		void Slerp(Quat _q1, float _t);

		// Static functions
		/// <summary>Returns a normalized quaternion using Euler angles. Order is XYZ </summary>
		/// <param name="_yaw">: X-axis rotation</param>
		/// <param name="_pitch">: Y-axis rotation</param>
		/// <param name="_roll">: Z-axis rotation</param>
		static Quat QuaternionEuler(float _yaw = 0.f, float _pitch = 0.f, float _roll = 0.f);
		static Quat QuaternionAxisAngle(Vec3 _axis, float _angle);
		static void Print(Quat _q);
		inline static Quat Identity() { return { 1.f, 0.f, 0.f, 0.f }; };
		static Vec3 GetEulerAngles(Quat _q);
		static float Norm(Quat _q);
		static Quat Normalized(Quat _q);
		static float DotProduct(Quat _q1, Quat _q2);
		static Quat Inverse(Quat _q);
		static inline Quat Conjugate(Quat _q) { return Quat(_q.w, -_q.x, -_q.y, -_q.z); }
		static Quat HamiltonProduct(Quat _q1, Quat _q2);
		static Quat Rotate(Quat _q1, Quat _q2);
		static Vec3 Rotate(Vec3 _v, Quat _q);
		static Mat3 QuatToMatrix(Quat _q);
		static Mat4 GetTransformMatrix(Vec3 _translation, Quat _rotation);
		static Quat Slerp(Quat _q1, Quat _q2, float _t);
	};

}