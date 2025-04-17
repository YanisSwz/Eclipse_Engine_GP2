#pragma once

namespace Math
{
	class Vec2;
	class Vec4;
	class Mat3;

	class Vec3
	{
	public:
		// Constructor
		Vec3() = default;
		Vec3(float _scalar);
		Vec3(float _x, float _y, float _z);
		Vec3(Vec2 _vec2);
		Vec3(Vec2 _vec2, float _z);
		Vec3(Vec3 _vec1, Vec3 _vec2);
		Vec3(Vec4 _vec4);
		Vec3(const Vec3 & _copy);
		~Vec3() = default;

		// Variables
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		// Static Variables
		static const Vec3 right;
		static const Vec3 up;
		static const Vec3 forward;

		// Functions
		void SetZero();
		void SetOne();
		void Opposite();
		void MidPoint(Vec3 _vec);
		float Distance(Vec3 _vec) const;
		float SquareNorm() const;
		float Norm() const;
		void Normalize();
		float DotProduct(Vec3 _vec) const;
		void CrossProduct(Vec3 _vec);
		void RotateX(float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		void RotateY(float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		void RotateZ(float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		void Rotate(float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		void Rotate(Vec3 _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		void Print() const;

		// Static Functions
		static Vec3 Zero();
		static Vec3 One();
		static Vec3 Opposite(Vec3 _vec);
		static Vec3 MidPoint(Vec3 _vec1, Vec3 _vec2);
		static float Distance(Vec3 _vec1, Vec3 _vec2);
		static float SquareNorm(Vec3 _vec);
		static float Norm(Vec3 _vec);
		static Vec3 Normalized(Vec3 _vec);
		static float DotProduct(Vec3 _vec1, Vec3 _vec2);
		static Vec3 CrossProduct(Vec3 _vec1, Vec3 _vec2);
		static Vec3 RotateX(Vec3 _vecToRotate, float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		static Vec3 RotateY(Vec3 _vecToRotate, float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		static Vec3 RotateZ(Vec3 _vecToRotate, float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		static Vec3 Rotate(Vec3 _vecToRotate, float _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		static Vec3 Rotate(Vec3 _vecToRotate, Vec3 _theta, Vec3 _anchor = { 0.f, 0.f, 0.f });
		static void Print(Vec3 _vec);
		
		// Operator +, -, *, /
		Vec3 operator+(float _scalar) const;
		Vec3 operator+(Vec3 _vec) const;
		Vec3 operator-(float _scalar) const;
		Vec3 operator-(Vec3 _vec) const;
		Vec3 operator*(float _scalar) const;
		Vec3 operator*(Vec3 _vec) const;
		Vec3 operator/(float _scalar) const;
		Vec3 operator/(Vec3 _vec) const;

		// Operator +=, -=, *=, /=
		void operator+=(float _scalar);
		void operator+=(Vec3 _vec);
		void operator-=(float _scalar);
		void operator-=(Vec3 _vec);
		void operator*=(float _scalar);
		void operator*=(Vec3 _vec);
		void operator/=(float _scalar);
		void operator/=(Vec3 _vec);

		// Operator []
		float operator[](int i) const;

		// Operator =
		void operator=(float _scalar);
		void operator=(Vec3 _vec);

		// Operator == / !=
		bool operator==(Vec3 _vec) const;
		bool operator!=(Vec3 _vec) const;
	};
}