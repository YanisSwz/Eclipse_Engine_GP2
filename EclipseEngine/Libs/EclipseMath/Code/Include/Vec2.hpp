#pragma once

namespace Math
{
	class Vec3;
	class Vec4;
	class Mat2;

	class Vec2
	{
	public:
		// Constructor
		Vec2() = default;
		Vec2(float _value);
		Vec2(float _x, float _y);
		Vec2(Vec3 _vec3);
		Vec2(Vec4 _vec4);
		Vec2(const Vec2& _copy);
		~Vec2() = default;

		// Variables
		float x = 0.f;
		float y = 0.f;

		// Functions
		void Zero();
		void One();
		void Opposite();
		void MidPoint(Vec2 _vec);
		float Distance(Vec2 _vec) const;
		float SquareNorm() const;
		float Norm() const;
		void Normalize();
		float DotProduct(Vec2 _vec) const;
		float CrossProduct(Vec2 _vec) const;
		void Rotate(float _theta, Vec2 _anchor = { 0.f, 0.f });
		void Print() const;

		// Static Functions
		static Vec2 s_Zero();
		static Vec2 s_One();
		static Vec2 s_Opposite(Vec2 _vec);
		static Vec2 s_MidPoint(Vec2 _vec1, Vec2 _vec2);
		static float s_Distance(Vec2 _vec1, Vec2 _vec2);
		static float s_SquareNorm(Vec2 _vec);
		static float s_Norm(Vec2 _vec);
		static float s_DotProduct(Vec2 _vec1, Vec2 _vec2);
		static float s_CrossProduct(Vec2 _vec1, Vec2 _vec2);
		static Vec2 s_Rotate(Vec2 _vec, float _theta, Vec2 _anchor = { 0.f, 0.f });
		static void s_Print(Vec2 _vec);

		// Operator +, -, *, /
		Vec2 operator+(float _scalar) const;
		Vec2 operator+(Vec2 _vec) const;
		Vec2 operator-(float _scalar) const;
		Vec2 operator-(Vec2 _vec) const;
		Vec2 operator*(float _scalar) const;
		Vec2 operator*(Vec2 _vec) const;
		Vec2 operator/(float _scalar) const;
		Vec2 operator/(Vec2 _vec) const;

		// Operator +=, -=, *=, /=
		void operator+=(float _scalar);
		void operator+=(Vec2 _vec);
		void operator-=(float _scalar);
		void operator-=(Vec2 _vec);
		void operator*=(float _scalar);
		void operator*=(Vec2 _vec);
		void operator/=(float _scalar);
		void operator/=(Vec2 _vec);

		// Operator []
		float operator[](int i) const;

		// Operator =
		void operator=(float _scalar);
		void operator=(Vec2 _vec);

		// Operator == / !=
		bool operator==(Vec2 _vec) const;
		bool operator!=(Vec2 _vec) const;
	};
}