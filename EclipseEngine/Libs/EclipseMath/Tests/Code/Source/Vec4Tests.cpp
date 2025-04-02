#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "Maths.hpp"

namespace Vec4Test
{
	bool IsEqual(float _a, float _b)
	{
		return fabsf(_a - _b) <= Math::Tools::epsilon;
	}

	bool IsEqual(Math::Vec4 _vec, glm::vec4 _glmVec)
	{
		return (IsEqual(_vec.x, _glmVec.x) && IsEqual(_vec.y, _glmVec.y) && IsEqual(_vec.z, _glmVec.z) && IsEqual(_vec.w, _glmVec.w));
	}
}

//####################### UNIT TEST CONSTRUCTORS #######################

TEST(Vector4, Constructor_Default)
{
	Math::Vec4 TBVec;
	glm::vec4 glmVec{ 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, Constructor_1Float)
{
	Math::Vec4 TBVec{ 1.f };
	glm::vec4 glmVec{ 1.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, Constructor_4Float)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, Constructor_1Vec_2Float)
{
	Math::Vec2 TBVec2{ 1.f, 2.f };
	Math::Vec4 TBVec4{ TBVec2, 3.f, 4.f };
	glm::vec4 glmVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec4, glmVec));
}

TEST(Vector4, Constructor_1Vec_1Float)
{
	Math::Vec3 TBVec3{ 1.f, 2.f, 3.f };
	Math::Vec4 TBVec4{ TBVec3, 4.f };
	glm::vec4 glmVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec4, glmVec));
}

TEST(Vector4, Constructor_Copy)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 ToolBoxCopy{ TBVec };
	glm::vec4 glmVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(ToolBoxCopy, glmVec));
}


//####################### UNIT TEST FUNCTIONS #######################

TEST(Vector4, Zero)
{
	Math::Vec4 TBVec;
	TBVec.SetZero();
	glm::vec4 glmVec{ 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, One)
{
	Math::Vec4 TBVec;
	TBVec.SetOne();
	glm::vec4 glmVec{ 1.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, Opposite)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec.Opposite();
	glm::vec4 glmVec{ -1.f, -2.f, -3.f, -4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, MidPoint)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec.MidPoint({ -1.f, -2.f, -3.f, -4.f });
	glm::vec4 glmVec{ 0.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmVec));
}

TEST(Vector4, Distance)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	float TBDist = TBVec.Distance({ 1.f, 1.f, 1.f, 1.f });
	EXPECT_TRUE(Vec4Test::IsEqual(TBDist, 3.74165f));
}

TEST(Vector4, SquareNorm)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	float TBSquareNorm = TBVec.SquareNorm();
	EXPECT_TRUE(Vec4Test::IsEqual(TBSquareNorm, 30.f));
}

TEST(Vector4, Norm)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	float TBNorm = TBVec.Norm();
	EXPECT_TRUE(Vec4Test::IsEqual(TBNorm, 5.477225f));
}

TEST(Vector4, DotProduct)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	float TBDotProduct = TBVec.DotProduct({ 2.f, 3.f, 4.f, 5.f });
	float glmDot = glm::dot(glm::vec4{ 1.f, 2.f, 3.f, 4.f }, glm::vec4{ 2.f, 3.f, 4.f, 5.f });
	EXPECT_TRUE(Vec4Test::IsEqual(TBDotProduct, glmDot));
}

TEST(Vector4, RotateX_Test_1)
{
	Math::Vec4 TBVec{ 0.f, 1.f, 0.f, 0.f };
	TBVec.RotateX(Math::Tools::PI / 2.f);
	glm::vec4 glmResultExpected{ 0.f, 0.f, 1.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, RotateX_Test_2)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 1.f, 1.f };
	TBVec.RotateX(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f, 1.f });
	glm::vec4 glmResultExpected{ 1.f, 1.f, 2.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, RotateY_Test_1)
{
	Math::Vec4 TBVec{ 0.f, 0.f, 1.f, 0.f };
	TBVec.RotateY(Math::Tools::PI / 2.f);
	glm::vec4 glmResultExpected{ 1.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, RotateY_Test_2)
{
	Math::Vec4 TBVec{ 1.f, 1.f, 2.f, 1.f };
	TBVec.RotateY(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f, 1.f });
	glm::vec4 glmResultExpected{ 2.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, RotateZ_Test_1)
{
	Math::Vec4 TBVec{ 0.f, 1.f, 0.f, 0.f };
	TBVec.RotateZ(Math::Tools::PI / 2.f);
	glm::vec4 glmResultExpected{ 1.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, RotateZ_Test_2)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 1.f, 1.f };
	TBVec.RotateZ(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f, 1.f });
	glm::vec4 glmResultExpected{ 2.f, 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Rotate_Test_1)
{
	Math::Vec4 TBVec{ 1.f, 0.f, 0.f, 1.f };
	TBVec.Rotate(Math::Tools::PI / 2.f);
	glm::vec4 glmResultExpected{ 0.f, 0.f, -1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Rotate_Test_2)
{
	Math::Vec4 TBVec{ 2.f, 1.f, 1.f, 1.f };
	TBVec.Rotate(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f, 1.f });
	glm::vec4 glmResultExpected{ 1.f, 1.f, 0.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Rotate_Test_3)
{
	Math::Vec4 TBVec{ 1.f, 0.f, 0.f, 1.f };
	TBVec.Rotate({ Math::Tools::PI / 2.f, Math::Tools::PI / 2.f, Math::Tools::PI / 2.f });
	glm::vec4 glmResultExpected{ 0.f, 0.f, -1.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Rotate_Test_4)
{
	Math::Vec4 TBVec{ 2.f, 1.f, 1.f, 1.f };
	TBVec.Rotate({ Math::Tools::PI / 2.f, Math::Tools::PI / 2.f, Math::Tools::PI / 2.f }, { 1.f, 1.f, 1.f, 1.f });
	glm::vec4 glmResultExpected{ 1.f, 1.f, 0.f, 1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}


//####################### UNIT TEST OPERATORS #######################

TEST(Vector4, Operator_Add_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResultExpected{ 3.f, 4.f, 5.f, 6.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec + 2.f, glmResultExpected));
}

TEST(Vector4, Operator_Add_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	glm::vec4 glmResultExpected{ 3.f, 5.f, 7.f, 9.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1 + TBVec2, glmResultExpected));
}

TEST(Vector4, Operator_Substract_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResultExpected{ -1.f, 0.f, 1.f, 2.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec - 2.f, glmResultExpected));
}

TEST(Vector4, Operator_Substract_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	glm::vec4 glmResultExpected{ -1.f, -1.f, -1.f, -1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1 - TBVec2, glmResultExpected));
}

TEST(Vector4, Operator_Multiply_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResultExpected{ 2.f, 4.f, 6.f, 8.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec * 2.f, glmResultExpected));
}

TEST(Vector4, Operator_Multiply_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	glm::vec4 glmResultExpected{ 2.f, 6.f, 12.f, 20.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1 * TBVec2, glmResultExpected));
}

TEST(Vector4, Operator_Divide_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResultExpected{ 0.5f, 1.f, 1.5f, 2.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec / 2.f, glmResultExpected));
}

TEST(Vector4, Operator_Divide_Vec4)
{
	Math::Vec4 TBVec1{ 2.f, 3.f, 4.f, 5.f };
	Math::Vec4 TBVec2{ 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResultExpected{ 2.f, 1.5f, 1.333333f, 1.25f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1 / TBVec2, glmResultExpected));
}

TEST(Vector4, Operator_Add_Equal_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec += 2.f;
	glm::vec4 glmResultExpected{ 3.f, 4.f, 5.f, 6.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Operator_Add_Equal_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	TBVec1 += TBVec2;
	glm::vec4 glmResultExpected{ 3.f, 5.f, 7.f, 9.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector4, Operator_Substract_Equal_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec -= 2.f;
	glm::vec4 glmResultExpected{ -1.f, 0.f, 1.f, 2.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Operator_Substract_Equal_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	TBVec1 -= TBVec2;
	glm::vec4 glmResultExpected{ -1.f, -1.f, -1.f, -1.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector4, Operator_Multiply_Equal_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec *= 2.f;
	glm::vec4 glmResultExpected{ 2.f, 4.f, 6.f, 8.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Operator_Multiply_Equal_Vec4)
{
	Math::Vec4 TBVec1{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2{ 2.f, 3.f, 4.f, 5.f };
	TBVec1 *= TBVec2;
	glm::vec4 glmResultExpected{ 2.f, 6.f, 12.f, 20.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector4, Operator_Divide_Equal_Scalar)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	TBVec /= 2.f;
	glm::vec4 glmResultExpected{ 0.5f, 1.f, 1.5f, 2.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector4, Operator_Divide_Equal_Vec4)
{
	Math::Vec4 TBVec1{ 2.f, 3.f, 4.f, 5.f };
	Math::Vec4 TBVec2{ 1.f, 2.f, 3.f, 4.f };
	TBVec1 /= TBVec2;
	glm::vec4 glmResultExpected{ 2.f, 1.5f, 1.333333f, 1.25f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector4, Operator_Bracket_0)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec[0], 1.f));
}

TEST(Vector4, Operator_Bracket_1)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec[1], 2.f));
}

TEST(Vector4, Operator_Bracket_2)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec[2], 3.f));
}

TEST(Vector4, Operator_Bracket_3)
{
	Math::Vec4 TBVec{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec[3], 4.f));
}

TEST(Vector4, Operator_Equal_Scalar)
{
	Math::Vec4 TBVec = 2.f;
	glm::vec4 glmResult{ 2.f, 2.f, 2.f, 2.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResult));
}

TEST(Vector4, Operator_Equal_Vec4)
{
	Math::Vec4 TBVec = { 1.f, 2.f, 3.f, 4.f };
	glm::vec4 glmResult{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(Vec4Test::IsEqual(TBVec, glmResult));
}

TEST(Vector4, Operator_Equal_Equal_Test_1)
{
	Math::Vec4 TBVec1 = { 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2 = { 1.f, 2.f, 3.f, 4.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec4 glmResult{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(isEqual == Vec4Test::IsEqual(TBVec1, glmResult));
}

TEST(Vector4, Operator_Equal_Equal_Test_2)
{
	Math::Vec4 TBVec1 = { 0.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2 = { 1.f, 2.f, 3.f, 4.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec4 glmResult{ 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE(isEqual == Vec4Test::IsEqual(TBVec1, glmResult) && Vec4Test::IsEqual(TBVec2, glmResult));
}

TEST(Vector4, Operator_Different_Test_1)
{
	Math::Vec4 TBVec1 = { 0.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2 = { 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec4Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec4Test::IsEqual(TBVec1[1], TBVec2[1]) || !Vec4Test::IsEqual(TBVec1[2], TBVec2[2]) || !Vec4Test::IsEqual(TBVec1[3], TBVec2[3])));
}

TEST(Vector4, Operator_Different_Test_2)
{
	Math::Vec4 TBVec1 = { 1.f, 2.f, 3.f, 4.f };
	Math::Vec4 TBVec2 = { 1.f, 2.f, 3.f, 4.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec4Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec4Test::IsEqual(TBVec1[1], TBVec2[1]) || !Vec4Test::IsEqual(TBVec1[2], TBVec2[2]) || !Vec4Test::IsEqual(TBVec1[3], TBVec2[3])));
}