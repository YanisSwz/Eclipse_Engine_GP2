#include <gtest/gtest.h>
#include <glm/mat4x4.hpp>
#include "Mat4.hpp"
#include "Tools.hpp"

using namespace Math;

bool IsEqual(Mat4 _mat, glm::mat4x4 _glmMat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (fabsf(_mat[i][j] - _glmMat[i][j]) >= Tools::epsilon)
				return false;
		}
	}
	return true;
}

/// Constructors Tests ///

TEST(Mat4, ScalarConstructor)
{
	Mat4 mat{ 0.f };
	glm::mat4x4 glmMat{ 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat4, OneVec4Constructor)
{
	Mat4 mat{ Vec4{1.f}, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	glm::mat4x4 glmMat{ 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat4, TwoVec4Constructor)
{
	Mat4 mat{ Vec4{1.f}, Vec4{1.f}, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	glm::mat4x4 glmMat{ 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat4, ThreeVec4Constructor)
{
	Mat4 mat{ Vec4{1.f}, Vec4{1.f}, Vec4{1.f}, 0.f, 0.f, 0.f, 0.f };
	glm::mat4x4 glmMat{ 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat4, FourVec4Constructor)
{
	Mat4 mat{ Vec4{1.f}, Vec4{1.f}, Vec4{1.f}, Vec4{1.f} };
	glm::mat4x4 glmMat{ 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat4, CopyConstructor)
{
	Mat4 mat1{ 1.f };
	Mat4 mat2{ Mat4{ 1.f } };
	EXPECT_TRUE(mat1 == mat2);
}

/// Functions Tests ///

TEST(Mat4, Diagonal)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	Vec4 vec{ 1.f, 6.f, 11.f, 16.f };
	EXPECT_TRUE(mat.Diagonal() == vec);
}

TEST(Mat4, Transpose)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(IsEqual(Mat4::s_Transpose(mat), glm::transpose(glmMat)));
}

TEST(Mat4, Trace)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(mat.Trace() == 1.f + 6.f + 11.f + 16.f);
}

TEST(Mat4, Opposite)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(IsEqual(Mat4::s_Opposite(mat), -glmMat));
}

TEST(Mat4, Determinant)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(mat.Det() == glm::determinant(glmMat));
}

TEST(Mat4, Inverse)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(IsEqual(Mat4::s_Inverse(mat), glm::inverse(glmMat)));
}

TEST(Mat4, RotateX)
{
	Mat4 mat = Mat4::s_RotateX(Tools::PI / 2.f);
	Vec4 vecY{ 0.f, 1.f, 0.f, 1.f };
	Vec4 vecZ{ 0.f, 0.f, 1.f, 1.f };
	EXPECT_TRUE(mat * vecY == vecZ);
}

TEST(Mat4, RotateY)
{
	Mat4 mat = Mat4::s_RotateY(Tools::PI / 2.f);
	Vec4 vecX{ 1.f, 0.f, 0.f, 1.f };
	Vec4 vecZ{ 0.f, 0.f, 1.f, 1.f };
	EXPECT_TRUE(mat * vecZ == vecX);
}

TEST(Mat4, RotateZ)
{
	Mat4 mat = Mat4::s_RotateZ(Tools::PI / 2.f);
	Vec4 vecX{ 1.f, 0.f, 0.f, 1.f };
	Vec4 vecY{ 0.f, 1.f, 0.f, 1.f };
	EXPECT_TRUE(mat * vecY == vecX);
}

TEST(Mat4, Rotate)
{
	Mat4 mat = Mat4::s_Rotate(Vec3{ Tools::PI / 2.f });
	Vec3 vec1{ 1.f, 0.f, 0.f };
	Vec3 vec2{ 0.f, 0.f, -1.f };
	EXPECT_TRUE(mat * vec1 == vec2);
}

TEST(Mat4, Translate)
{
	Mat4 mat1;
	Mat4 mat2 = Mat4::s_Translate(Vec3{ 1.f });
	Mat4 mat3 = Mat4{ 1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f };
	EXPECT_TRUE(mat1 * mat2 == mat3);
}

TEST(Mat4, Scale)
{
	Mat4 mat = Mat4::s_Scale(Vec3{ 2.f });
	Vec3 vec1{ 1.f, 1.f, 1.f };
	Vec3 vec2{ 2.f, 2.f, 2.f };
	EXPECT_TRUE(mat * vec1 == vec2);
}

/// Operators Tests ///

TEST(Mat4, Add)
{
	Mat4 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	Mat4 mat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat4x4 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 + mat2, glmMat1 + glmMat2));
}

TEST(Mat4, Substract)
{
	Mat4 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	Mat4 mat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat4x4 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 - mat2, glmMat1 - glmMat2));
}

TEST(Mat4, Multiply)
{
	Mat4 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	Mat4 mat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat4x4 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	glm::mat4x4 glmMat2{ 16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 * mat2, glmMat2 * glmMat1));
}

TEST(Mat4, GetValue)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(mat[2][1] == 10.f);
}

TEST(Mat4, IsEqual)
{
	Mat4 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	EXPECT_TRUE(mat == mat);
}

TEST(Mat4, IsNotEqual)
{
	Mat4 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f };
	Mat4 mat2{ 0.f };
	EXPECT_TRUE(mat1 != mat2);
}