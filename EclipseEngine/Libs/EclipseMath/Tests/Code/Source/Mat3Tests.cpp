#include <gtest/gtest.h>
#include <glm/mat3x3.hpp>
#include "Mat3.hpp"
#include "Tools.hpp"

using namespace Math;

bool IsEqual(Mat3 _mat, glm::mat3x3 _glmMat)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (fabsf(_mat[i][j] - _glmMat[i][j]) >= Tools::epsilon)
				return false;
		}
	}
	return true;
}

/// Constructors Tests ///

TEST(Mat3, ScalarConstructor)
{
	Mat3 mat{ 0.f };
	glm::mat3x3 glmMat{ 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat3, OneVec3Constructor)
{
	Mat3 mat{ Vec3{1.f}, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	glm::mat3x3 glmMat{ 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat3, TwoVec3Constructor)
{
	Mat3 mat{ Vec3{1.f}, Vec3{1.f}, 0.f, 0.f, 0.f };
	glm::mat3x3 glmMat{ 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat3, ThreeVec3Constructor)
{
	Mat3 mat{ Vec3{1.f}, Vec3{1.f}, Vec3{1.f} };
	glm::mat3x3 glmMat{ 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat3, CopyConstructor)
{
	Mat3 mat1{ 1.f };
	Mat3 mat2{ Mat3{ 1.f } };
	EXPECT_TRUE(mat1 == mat2);
}

/// Functions Tests ///

TEST(Mat3, Diagonal)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	Vec3 vec{ 1.f, 5.f, 9.f };
	EXPECT_TRUE(mat.Diagonal() == vec);
}

TEST(Mat3, Transpose)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(IsEqual(Mat3::s_Transpose(mat), glm::transpose(glmMat)));
}

TEST(Mat3, Trace)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(mat.Trace() == 1.f + 5.f + 9.f);
}

TEST(Mat3, Opposite)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(IsEqual(Mat3::s_Opposite(mat), -glmMat));
}

TEST(Mat3, Determinant)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(mat.Det() == glm::determinant(glmMat));
}

TEST(Mat3, Inverse)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(IsEqual(Mat3::s_Inverse(mat), glm::inverse(glmMat)));
}

TEST(Mat3, RotateX)
{
	Mat3 mat = Mat3::s_RotateX(Tools::PI / 2.f);
	Vec3 vecY{ 0.f, 1.f, 0.f };
	Vec3 vecZ{ 0.f, 0.f, 1.f };
	EXPECT_TRUE(mat * vecY == vecZ);
}

TEST(Mat3, RotateY)
{
	Mat3 mat = Mat3::s_RotateY(Tools::PI / 2.f);
	Vec3 vecX{ 1.f, 0.f, 0.f };
	Vec3 vecZ{ 0.f, 0.f, 1.f };
	EXPECT_TRUE(mat * vecZ == vecX);
}

TEST(Mat3, RotateZ)
{
	Mat3 mat = Mat3::s_RotateZ(Tools::PI / 2.f);
	Vec3 vecX{ 1.f, 0.f, 0.f };
	Vec3 vecY{ 0.f, 1.f, 0.f };
	EXPECT_TRUE(mat * vecY == vecX);
}

TEST(Mat3, Translate)
{
	Mat3 mat1;
	Mat3 mat2 = Mat3::s_Translate(Vec3{ 1.f });
	Mat3 mat3 = Mat3{ 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f };
	EXPECT_TRUE(mat1 * mat2 == mat3);
}

TEST(Mat3, Scale)
{
	Mat3 mat = Mat3::s_Scale(Vec3{ 2.f });
	Vec3 vec1{ 1.f, 1.f, 1.f };
	Vec3 vec2{ 2.f, 2.f, 2.f };
	EXPECT_TRUE(mat * vec1 == vec2);
}

/// Operators Tests ///

TEST(Mat3, Add)
{
	Mat3 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	Mat3 mat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat3x3 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 + mat2, glmMat1 + glmMat2));
}

TEST(Mat3, Substract)
{
	Mat3 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	Mat3 mat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat3x3 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 - mat2, glmMat1 - glmMat2));
}

TEST(Mat3, Multiply)
{
	Mat3 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	Mat3 mat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	glm::mat3x3 glmMat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	glm::mat3x3 glmMat2{ 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 * mat2, glmMat2 * glmMat1));
}

TEST(Mat3, GetValue)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(mat[2][1] == 8.f);
}

TEST(Mat3, IsEqual)
{
	Mat3 mat{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	EXPECT_TRUE(mat == mat);
}

TEST(Mat3, IsNotEqual)
{
	Mat3 mat1{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
	Mat3 mat2{ 0.f };
	EXPECT_TRUE(mat1 != mat2);
}