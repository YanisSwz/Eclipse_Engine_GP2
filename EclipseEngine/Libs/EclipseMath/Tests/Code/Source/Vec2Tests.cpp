#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "Maths.hpp"

namespace Vec2Test
{
	bool IsEqual(float _a, float _b)
	{
		return fabsf(_a - _b) <= Math::Tools::epsilon;
	}

	bool IsEqual(Math::Vec2 _vec, glm::vec2 _glmVec)
	{
		return (IsEqual(_vec.x, _glmVec.x) && IsEqual(_vec.y, _glmVec.y));
	}
}

//####################### UNIT TEST CONSTRUCTORS #######################

TEST(Vector2, Constructor_Default)
{
	Math::Vec2 TBVec;
	glm::vec2 glmVec{ 0.f, 0.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, Constructor_1Float)
{
	Math::Vec2 TBVec{ 1.f };
	glm::vec2 glmVec{ 1.f, 1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, Constructor_2Float)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	glm::vec2 glmVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, Constructor_1Vec3)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec2 TBVec2{ TBVec1 };
	glm::vec2 glmVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec2, glmVec));
}

TEST(Vector2, Constructor_1Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec2 TBVec2{ TBVec1 };
	glm::vec2 glmVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec2, glmVec));
}

TEST(Vector2, Constructor_Copy)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	Math::Vec2 ToolBoxCopy{ TBVec };
	glm::vec2 glmVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(ToolBoxCopy, glmVec));
}


//####################### UNIT TEST FUNCTIONS #######################

TEST(Vector2, Zero)
{
	Math::Vec2 TBVec;
	TBVec.SetZero();
	glm::vec2 glmVec{ 0.f, 0.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, One)
{
	Math::Vec2 TBVec;
	TBVec.SetOne();
	glm::vec2 glmVec{ 1.f, 1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, Opposite)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec.Opposite();
	glm::vec2 glmVec{ -1.f, -2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, MidPoint)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec.MidPoint({ -1.f, -2.f });
	glm::vec2 glmVec{ 0.f, 0.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmVec));
}

TEST(Vector2, Distance)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	float TBDist = TBVec.Distance({ 1.f, 1.f });
	EXPECT_TRUE(Vec2Test::IsEqual(TBDist, 1.f));
}

TEST(Vector2, SquareNorm)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	float TBSquareNorm = TBVec.SquareNorm();
	EXPECT_TRUE(Vec2Test::IsEqual(TBSquareNorm, 5.f));
}

TEST(Vector2, Norm)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	float TBNorm = TBVec.Norm();
	EXPECT_TRUE(Vec2Test::IsEqual(TBNorm, 2.236067f));
}

TEST(Vector2, Normalize)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec.Normalize();
	glm::vec2 glmResultExpected{ 1.f, 2.f };
	glmResultExpected = glm::normalize(glmResultExpected);
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, DotProduct)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	float TBDotProduct = TBVec.DotProduct({ 2.f, 3.f });
	float glmDot = glm::dot(glm::vec2{ 1.f, 2.f }, glm::vec2{ 2.f, 3.f });
	EXPECT_TRUE(Vec2Test::IsEqual(TBDotProduct, glmDot));
}

TEST(Vector2, CrossProduct)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	float cross = TBVec.CrossProduct({ 2.f, 3.f });
	EXPECT_TRUE(Vec2Test::IsEqual(cross, -1.f));
}

TEST(Vector2, Rotate_Test_1)
{
	Math::Vec2 TBVec{ 1.f, 0.f };
	TBVec.Rotate(Math::Tools::PI / 2.f);
	glm::vec2 glmResultExpected{ 0.f, 1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, Rotate_Test_2)
{
	Math::Vec2 TBVec{ 2.f, 1.f };
	TBVec.Rotate(Math::Tools::PI / 2.f, { 1.f, 1.f });
	glm::vec2 glmResultExpected{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

//####################### UNIT TEST OPERATORS #######################

TEST(Vector2, Operator_Add_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	glm::vec2 glmResultExpected{ 3.f, 4.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec + 2.f, glmResultExpected));
}

TEST(Vector2, Operator_Add_Vec3)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	glm::vec2 glmResultExpected{ 3.f, 5.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1 + TBVec2, glmResultExpected));
}

TEST(Vector2, Operator_Substract_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	glm::vec2 glmResultExpected{ -1.f, 0.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec - 2.f, glmResultExpected));
}

TEST(Vector2, Operator_Substract_Vec3)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	glm::vec2 glmResultExpected{ -1.f, -1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1 - TBVec2, glmResultExpected));
}

TEST(Vector2, Operator_Multiply_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	glm::vec2 glmResultExpected{ 2.f, 4.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec * 2.f, glmResultExpected));
}

TEST(Vector2, Operator_Multiply_Vec4)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	glm::vec2 glmResultExpected{ 2.f, 6.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1 * TBVec2, glmResultExpected));
}

TEST(Vector2, Operator_Divide_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	glm::vec2 glmResultExpected{ 0.5f, 1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec / 2.f, glmResultExpected));
}

TEST(Vector2, Operator_Divide_Vec4)
{
	Math::Vec2 TBVec1{ 2.f, 3.f };
	Math::Vec2 TBVec2{ 1.f, 2.f };
	glm::vec2 glmResultExpected{ 2.f, 1.5f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1 / TBVec2, glmResultExpected));
}

TEST(Vector2, Operator_Add_Equal_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec += 2.f;
	glm::vec2 glmResultExpected{ 3.f, 4.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, Operator_Add_Equal_Vec4)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	TBVec1 += TBVec2;
	glm::vec2 glmResultExpected{ 3.f, 5.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector2, Operator_Substract_Equal_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec -= 2.f;
	glm::vec2 glmResultExpected{ -1.f, 0.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, Operator_Substract_Equal_Vec4)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	TBVec1 -= TBVec2;
	glm::vec2 glmResultExpected{ -1.f, -1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector2, Operator_Multiply_Equal_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec *= 2.f;
	glm::vec2 glmResultExpected{ 2.f, 4.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, Operator_Multiply_Equal_Vec4)
{
	Math::Vec2 TBVec1{ 1.f, 2.f };
	Math::Vec2 TBVec2{ 2.f, 3.f };
	TBVec1 *= TBVec2;
	glm::vec2 glmResultExpected{ 2.f, 6.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector2, Operator_Divide_Equal_Scalar)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	TBVec /= 2.f;
	glm::vec2 glmResultExpected{ 0.5f, 1.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector2, Operator_Divide_Equal_Vec4)
{
	Math::Vec2 TBVec1{ 2.f, 3.f };
	Math::Vec2 TBVec2{ 1.f, 2.f };
	TBVec1 /= TBVec2;
	glm::vec2 glmResultExpected{ 2.f, 1.5f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector2, Operator_Bracket_0)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec[0], 1.f));
}

TEST(Vector2, Operator_Bracket_1)
{
	Math::Vec2 TBVec{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec[1], 2.f));
}

TEST(Vector2, Operator_Equal_Scalar)
{
	Math::Vec2 TBVec = 2.f;
	glm::vec2 glmResult{ 2.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResult));
}

TEST(Vector2, Operator_Equal_Vec4)
{
	Math::Vec2 TBVec = { 1.f, 2.f };
	glm::vec2 glmResult{ 1.f, 2.f };
	EXPECT_TRUE(Vec2Test::IsEqual(TBVec, glmResult));
}

TEST(Vector2, Operator_Equal_Equal_Test_1)
{
	Math::Vec2 TBVec1 = { 1.f, 2.f };
	Math::Vec2 TBVec2 = { 1.f, 2.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec2 glmResult{ 1.f, 2.f };
	EXPECT_TRUE(isEqual == Vec2Test::IsEqual(TBVec1, glmResult));
}

TEST(Vector2, Operator_Equal_Equal_Test_2)
{
	Math::Vec2 TBVec1 = { 0.f, 2.f };
	Math::Vec2 TBVec2 = { 1.f, 2.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec2 glmResult{ 1.f, 2.f };
	EXPECT_TRUE(isEqual == Vec2Test::IsEqual(TBVec1, glmResult) && Vec2Test::IsEqual(TBVec2, glmResult));
}

TEST(Vector2, Operator_Different_Test_1)
{
	Math::Vec2 TBVec1 = { 0.f, 2.f };
	Math::Vec2 TBVec2 = { 1.f, 2.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec2Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec2Test::IsEqual(TBVec1[1], TBVec2[1])));
}

TEST(Vector2, Operator_Different_Test_2)
{
	Math::Vec2 TBVec1 = { 1.f, 2.f };
	Math::Vec2 TBVec2 = { 1.f, 2.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec2Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec2Test::IsEqual(TBVec1[1], TBVec2[1])));
}