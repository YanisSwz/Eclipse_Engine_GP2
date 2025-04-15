#pragma once
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Quat.hpp"

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
		const float* GetValuesPointer();
		Vec4 Diagonal() const;
		void Transpose();
		float Trace() const;
		void Opposite();
		float Det() const;
		void Inverse();
		void SetRotationX(float _theta);
		void SetRotationY(float _theta);
		void SetRotationZ(float _theta);
		void SetRotation(Vec4 _theta);
		void SetTranslation(Vec4 _translate);
		void SetScale(Vec4 _scale);
		void SetTRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		void SetTRS(Vec4 _translate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _rotate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _scale = { 1.f, 1.f, 1.f, 1.f });
		void SetPerspectiveMatrix(int _width, int _height, float _fov, float _near, float _far);
		void SetViewMatrix(Vec3 _eye, Vec3 _at, Vec3 _up);
		void Print() const;

		// Static Functions
		static Vec4 Diagonal(Mat4 _mat);
		static Mat4 Transpose(Mat4 _mat);
		static float Trace(Mat4 _mat);
		static Mat4 Opposite(Mat4 _mat);
		static float Det(Mat4 _mat);
		static Mat4 Inverse(Mat4 _mat);
		static Mat4 RotationX(float _theta);
		static Mat4 RotationY(float _theta);
		static Mat4 RotationZ(float _theta);
		static Mat4 Rotation(Vec3 _theta);
		static Mat4 Rotation(Vec4 _theta);
		static Mat4 Rotation(Quat _rota);
		static Mat4 Translation(Vec3 _translate);
		static Mat4 Translation(Vec4 _translate);
		static Mat4 Scale(Vec3 _scale);
		static Mat4 Scale(Vec4 _scale);
		static Mat4 TRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Vec3 _rotate = { 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		static Mat4 TRS(Vec4 _translate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _rotate = { 0.f, 0.f, 0.f, 0.f }, Vec4 _scale = { 1.f, 1.f, 1.f, 1.f });
		static Mat4 TRS(Vec3 _translate = { 0.f, 0.f, 0.f }, Quat _rotate = { 1.f, 0.f, 0.f, 0.f }, Vec3 _scale = { 1.f, 1.f, 1.f });
		static Mat4 PerspectiveMatrix(int _width, int _height, float _fov, float _near, float _far);
		static Mat4 ViewMatrix(Vec3 _eye, Vec3 _at, Vec3 _up);
		static void Print(Mat4 _mat);

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
		float m_value[4][4] = { {1.f, 0.f, 0.f, 0.f}, {0.f, 1.f, 0.f, 0.f}, {0.f, 0.f, 1.f, 0.f}, {0.f, 0.f, 0.f, 1.f} };
	};
}