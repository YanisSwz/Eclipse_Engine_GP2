#pragma once
#include "Vec3.hpp"

namespace Math
{
	class Mat3
	{
	public:
		// Constructor
		Mat3() = default;
		Mat3(float _scalar);
		Mat3(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i);
		Mat3(Vec3 _vec, float _d, float _e, float _f, float _g, float _h, float _i);
		Mat3(Vec3 _vec1, Vec3 _vec2, float _g, float _h, float _i);
		Mat3(Vec3 _vec1, Vec3 _vec2, Vec3 _vec3);
		Mat3(const Mat3& _copy);
		~Mat3() = default;
		
		// Functions
		Vec3 Diagonal() const;
		void Transpose();
		float Trace() const;
		void Opposite();
		float Det() const;
		void Inverse();
		void SetRotationX(float _theta);
		void SetRotationY(float _theta);
		void SetRotationZ(float _theta);
		void Rotate(Vec3 _theta);
		void Translate(Vec3 _translate);
		void Scale(Vec3 _scale);
		void TRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		void Print() const;

		// Static Functions
		static Vec3 Diagonal(Mat3 _mat);
		static Mat3 Transpose(Mat3 _mat);
		static float Trace(Mat3 _mat);
		static Mat3 Opposite(Mat3 _mat);
		static float Det(Mat3 _mat);
		static Mat3 Inverse(Mat3 _mat);
		static Mat3 RotationX(float _theta);
		static Mat3 RotationY(float _theta);
		static Mat3 RotationZ(float _theta);
		static Mat3 Rotation(Vec3 _theta);
		static Mat3 Translation(Vec3 _translate);
		static Mat3 Scaling(Vec3 _scale);
		static Mat3 GetTRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		static void Print(Mat3 _mat);
		
		// Operator *
		Mat3 operator+(float _scalar) const;
		Mat3 operator+(Mat3 _mat) const;
		Mat3 operator-(float _scalar) const;
		Mat3 operator-(Mat3 _mat) const;
		Mat3 operator*(float _scalar) const;
		Vec3 operator*(Vec3 _vec) const;
		Mat3 operator*(Mat3 _mat) const;
		
		// Operator *=
		void operator+=(float _scalar);
		void operator+=(Mat3 _mat);
		void operator-=(float _scalar);
		void operator-=(Mat3 _mat);
		void operator*=(float _scalar);
		void operator*=(Mat3 _mat);
		
		// Operator []
		Vec3 operator[](int _i) const;
		
		// Operator =
		void operator=(float _scalar);
		void operator=(Mat3 _mat);

		// Operator == / !=
		bool operator==(Mat3 _mat) const;
		bool operator!=(Mat3 _mat) const;

	private:
		float m_value[3][3] = { {1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f} };
	};
}