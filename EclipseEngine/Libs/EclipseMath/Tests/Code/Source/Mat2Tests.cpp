#include <gtest/gtest.h>
#include <glm/Mat2x2.hpp>
#include "Mat2.hpp"
#include "Vec2.hpp"
#include "Tools.hpp"

using namespace Math;

bool IsEqual(Mat2 _mat, glm::mat2x2 _glmMat)
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (fabsf(_mat[i][j] - _glmMat[i][j]) >= Tools::epsilon)
				return false;
		}
	}
	return true;
}

/// Constructors Tests ///

TEST(Mat2, ScalarConstructor)
{
	Mat2 mat{ 0.f };
	glm::mat2x2 glmMat{ 0.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat2, OneVec2Constructor)
{
	Mat2 mat{ Vec2{1.f}, 0.f, 0.f };
	glm::mat2x2 glmMat{ 1.f, 1.f, 0.f, 0.f,  };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat2, TwoVec2Constructor)
{
	Mat2 mat{ Vec2{1.f}, Vec2{1.f} };
	glm::mat2x2 glmMat{ 1.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(IsEqual(mat, glmMat));
}

TEST(Mat2, CopyConstructor)
{
	Mat2 mat1{ 1.f };
	Mat2 mat2{ Mat2{ 1.f } };
	EXPECT_TRUE(mat1 == mat2);
}

/// Functions Tests ///

TEST(Mat2, Diagonal)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	Vec2 vec{ 1.f, 4.f };
	EXPECT_TRUE(mat.Diagonal() == vec);
}

TEST(Mat2, Transpose)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(IsEqual(Mat2::s_Transpose(mat), glm::transpose(glmMat)));
}

TEST(Mat2, Trace)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(mat.Trace() == 1.f + 4.f);
}

TEST(Mat2, Opposite)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(IsEqual(Mat2::s_Opposite(mat), -glmMat));
}

TEST(Mat2, Determinant)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(mat.Det() == glm::determinant(glmMat));
}

TEST(Mat2, Inverse)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(IsEqual(Mat2::s_Inverse(mat), glm::inverse(glmMat)));
}

/// Operators Tests ///

TEST(Mat2, Add)
{
	Mat2 mat1{ 1.f, 2.f, 3.f, 4.f };
	Mat2 mat2{ 4.f, 3.f, 2.f, 1.f };
	glm::mat2x2 glmMat1{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat2{ 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 + mat2, glmMat1 + glmMat2));
}

TEST(Mat2, Substract)
{
	Mat2 mat1{ 1.f, 2.f, 3.f, 4.f };
	Mat2 mat2{ 4.f, 3.f, 2.f, 1.f };
	glm::mat2x2 glmMat1{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat2{ 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 - mat2, glmMat1 - glmMat2));
}

TEST(Mat2, Multiply)
{
	Mat2 mat1{ 1.f, 2.f, 3.f, 4.f };
	Mat2 mat2{ 4.f, 3.f, 2.f, 1.f };
	glm::mat2x2 glmMat1{ 1.f, 2.f, 3.f, 4.f };
	glm::mat2x2 glmMat2{ 4.f, 3.f, 2.f, 1.f };
	EXPECT_TRUE(IsEqual(mat1 * mat2, glmMat2 * glmMat1));
}

TEST(Mat2, GetValue)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(mat[1][0] == 3.f);
}

TEST(Mat2, IsEqual)
{
	Mat2 mat{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(mat == mat);
}

TEST(Mat2, IsNotEqual)
{
	Mat2 mat1{ 1.f, 2.f, 3.f, 4.f };
	Mat2 mat2{ 0.f };
	EXPECT_TRUE(mat1 != mat2);
}