#pragma once

namespace Math
{
	class Vec2;
	class Vec3;
	class Mat4;

	class Vec4
	{
	public:
		// Constructor
		Vec4() = default;
		Vec4(float _scalar);
		Vec4(float _x, float _y, float _z, float _w = 0.f);
		Vec4(Vec2 _vec, float _z, float _w = 0.f);
		Vec4(Vec2 _vec1, Vec2 _vec2);
		Vec4(Vec3 _vec, float _w = 0.f);
		Vec4(const Vec4& _copy);
		~Vec4() = default;
		
		// Variables
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;

		// Functions
		void SetZero();
		void SetOne();
		void Opposite();
		void MidPoint(Vec4 _vec);
		float Distance(Vec4 _vec) const;
		float SquareNorm() const;
		float Norm() const;
		float DotProduct(Vec4 _vec) const;
		void RotateX(float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		void RotateY(float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		void RotateZ(float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		void Rotate(float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		void Rotate(Vec4 _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		void Print() const;

		// Static Functions
		static Vec4 Zero();
		static Vec4 One();
		static Vec4 Opposite(Vec4 _vec);
		static Vec4 MidPoint(Vec4 _vec1, Vec4 _vec2);
		static float Distance(Vec4 _vec1, Vec4 _vec2);
		static float SquareNorm(Vec4 _vec);
		static float Norm(Vec4 _vec);
		static float DotProduct(Vec4 _vec1, Vec4 _vec2);
		static Vec4 RotateX(Vec4 _vecToRotate, float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		static Vec4 RotateY(Vec4 _vecToRotate, float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		static Vec4 RotateZ(Vec4 _vecToRotate, float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		static Vec4 Rotate(Vec4 _vecToRotate, float _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		static Vec4 Rotate(Vec4 _vecToRotate, Vec4 _theta, Vec4 _anchor = { 0.f, 0.f, 0.f, 0.f });
		static void Print(Vec4 _vec);

		// Operator +, -, *, /
		Vec4 operator+(float _scalar) const;
		Vec4 operator+(Vec4 _vec) const;
		Vec4 operator-(float _scalar) const;
		Vec4 operator-(Vec4 _vec) const;
		Vec4 operator*(float _scalar) const;
		Vec4 operator*(Vec4 _vec) const;
		Vec4 operator/(float _scalar) const;
		Vec4 operator/(Vec4 _vec) const;

		// Operator +=, -=, *=, /=
		void operator+=(float _scalar);
		void operator+=(Vec4 _vec);
		void operator-=(float _scalar);
		void operator-=(Vec4 _vec);
		void operator*=(float _scalar);
		void operator*=(Vec4 _vec);
		void operator/=(float _scalar);
		void operator/=(Vec4 _vec);

		// Operator []
		float operator[](int i) const;

		// Operator =
		void operator=(float _scalar);
		void operator=(Vec4 _vec);

		// Operator == / !=
		bool operator==(Vec4 _vec) const; 
		bool operator!=(Vec4 _vec) const;
	};
}