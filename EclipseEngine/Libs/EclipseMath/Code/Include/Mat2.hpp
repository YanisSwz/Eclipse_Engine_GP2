#pragma once

namespace Math
{
	class Vec2;
	class Vec3;
	class Vec4;

	class Mat2
	{
	public:
		// Constructor
		Mat2() = default;
		Mat2(float _scalar);
		Mat2(float _a, float _b, float _c, float _d);
		Mat2(Vec2 _vec, float _c, float _d);
		Mat2(Vec2 _vec1, Vec2 _vec2);
		Mat2(Vec3 _vec, float _d);
		Mat2(Vec4 _vec);
		Mat2(const Mat2& _copy);
		~Mat2() = default;

		// Functions
		Vec2 Diagonal() const;
		void Transpose();
		float Trace() const;
		void Opposite();
		float Det() const;
		void Inverse();
		void Rotate(float _theta);
		void Print() const;

		// Static Functions
		static Vec2 s_Diagonal(Mat2 _mat);
		static Mat2 s_Transpose(Mat2 _mat);
		static float s_Trace(Mat2 _mat);
		static Mat2 s_Opposite(Mat2 _mat);
		static float s_Det(Mat2 _mat);
		static Mat2 s_Inverse(Mat2 _mat);
		static Mat2 s_Rotate(float _theta);
		static void s_Print(Mat2 _mat);

		// Operator *
		Mat2 operator+(float _scalar) const;
		Mat2 operator+(Mat2 _mat) const;
		Mat2 operator-(float _scalar) const;
		Mat2 operator-(Mat2 _mat) const;
		Mat2 operator*(float _scalar) const;
		Vec2 operator*(Vec2 _vec) const;
		Mat2 operator*(Mat2 _mat) const;

		// Operator *=
		void operator+=(float _scalar);
		void operator+=(Mat2 _mat);
		void operator-=(float _scalar);
		void operator-=(Mat2 _mat);
		void operator*=(float _scalar);
		void operator*=(Mat2 _mat);

		// Operator []
		Vec2 operator[](int _i) const;

		// Operator =
		void operator=(float _scalar);
		void operator=(Mat2 _mat);

		// Operator == / !=
		bool operator==(Mat2 _mat) const;
		bool operator!=(Mat2 _mat) const;

	private:
		float value[2][2] = { { 1.f, 0.f }, { 0.f, 1.f } };
	};
}