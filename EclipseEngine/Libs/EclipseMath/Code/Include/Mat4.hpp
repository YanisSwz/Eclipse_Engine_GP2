#pragma once
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace Math
{
	class Mat4
	{
	public:
		// Constructor
		Mat4() = default;
		Mat4(float _scalar);
		Mat4(float _a, float _b, float _c, float _d, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p);
		Mat4(Vec4 _vec, float _e, float _f, float _g, float _h, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p);
		Mat4(Vec4 _vec1, Vec4 _vec2, float _i, float _j, float _k, float _l, float _m, float _n, float _o, float _p);
		Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, float _m, float _n, float _o, float _p);
		Mat4(Vec4 _vec1, Vec4 _vec2, Vec4 _vec3, Vec4 _vec4);
		Mat4(const Mat4& _copy);

		~Mat4() = default;

		// Functions
		float& GetValues();
		Vec4 Diagonal() const;
		void Transpose();
		float Trace() const;
		void Opposite();
		float Det() const;
		void Inverse();
		void RotateX(float _theta);
		void RotateY(float _theta);
		void RotateZ(float _theta);
		void Rotate(Vec4 _theta);
		void Translate(Vec4 _translate);
		void Scale(Vec4 _scale);
		void TRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		void TRS(Vec4 _translate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _rotate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _scale = { 1.f, 1.f, 1.f, 1.f });
		void Print() const;

		// Static Functions
		static Vec4 s_Diagonal(Mat4 _mat);
		static Mat4 s_Transpose(Mat4 _mat);
		static float s_Trace(Mat4 _mat);
		static Mat4 s_Opposite(Mat4 _mat);
		static float s_Det(Mat4 _mat);
		static Mat4 s_Inverse(Mat4 _mat);
		static Mat4 s_RotateX(float _theta);
		static Mat4 s_RotateY(float _theta);
		static Mat4 s_RotateZ(float _theta);
		static Mat4 s_Rotate(Vec3 _theta);
		static Mat4 s_Rotate(Vec4 _theta);
		static Mat4 s_Translate(Vec3 _translate);
		static Mat4 s_Translate(Vec4 _translate);
		static Mat4 s_Scale(Vec3 _scale);
		static Mat4 s_Scale(Vec4 _scale);
		static Mat4 s_TRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		static Mat4 s_TRS(Vec4 _translate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _rotate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _scale = { 1.f, 1.f, 1.f, 1.f });
		static void s_Print(Mat4 _mat);

		// Operator *
		Mat4 operator+(float _scalar) const;
		Mat4 operator+(Mat4 _mat) const;
		Mat4 operator-(float _scalar) const;
		Mat4 operator-(Mat4 _mat) const;
		Mat4 operator*(float _scalar) const;
		Vec4 operator*(Vec3 _vec) const;
		Vec4 operator*(Vec4 _vec) const;
		Mat4 operator*(Mat4 _mat) const;

		// Operator *=
		void operator+=(float _scalar);
		void operator+=(Mat4 _mat);
		void operator-=(float _scalar);
		void operator-=(Mat4 _mat);
		void operator*=(float _scalar);
		void operator*=(Mat4 _mat);

		// Operator []
		Vec4 operator[](int _i) const;

		// Operator =
		void operator=(float _scalar);
		void operator=(Mat4 _mat);

		// Operator == / !=
		bool operator==(Mat4 _mat) const;
		bool operator!=(Mat4 _mat) const;

	private:
		float value[4][4] = { {1.f, 0.f, 0.f, 0.f}, {0.f, 1.f, 0.f, 0.f}, {0.f, 0.f, 1.f, 0.f}, {0.f, 0.f, 0.f, 1.f} };
	};
}