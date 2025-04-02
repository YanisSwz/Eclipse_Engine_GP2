#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "Maths.hpp"

namespace Vec3Test
{
	bool IsEqual(float _a, float _b)
	{
		return fabsf(_a - _b) <= Math::Tools::epsilon;
	}
	
	bool IsEqual(Math::Vec3 _vec, glm::vec3 _glmVec)
	{
		return (IsEqual(_vec.x, _glmVec.x) && IsEqual(_vec.y, _glmVec.y) && IsEqual(_vec.z, _glmVec.z));
	}
}

//####################### UNIT TEST CONSTRUCTORS #######################

TEST(Vector3, Constructor_Default)
{
	Math::Vec3 TBVec;
	glm::vec3 glmVec{ 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, Constructor_1Float)
{
	Math::Vec3 TBVec{ 1.f };
	glm::vec3 glmVec{ 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, Constructor_3Float)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	glm::vec3 glmVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, Constructor_1Vec2)
{
	Math::Vec2 TBVec2{ 1.f, 2.f };
	Math::Vec3 TBVec3{ TBVec2 };
	glm::vec3 glmVec{ 1.f, 2.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec3, glmVec));
}

TEST(Vector3, Constructor_1Vec2_1Float)
{
	Math::Vec2 TBVec2{ 1.f, 2.f };
	Math::Vec3 TBVec3{ TBVec2, 3.f };
	glm::vec3 glmVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec3, glmVec));
}

TEST(Vector3, Constructor_1Vec4)
{
	Math::Vec4 TBVec4{ 1.f, 2.f, 3.f, 4.f };
	Math::Vec3 TBVec3{ TBVec4 };
	glm::vec3 glmVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec3, glmVec));
}

TEST(Vector3, Constructor_Copy)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	Math::Vec3 ToolBoxCopy{ TBVec };
	glm::vec3 glmVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(ToolBoxCopy, glmVec));
}


//####################### UNIT TEST FUNCTIONS #######################

TEST(Vector3, Zero)
{
	Math::Vec3 TBVec;
	TBVec.SetZero();
	glm::vec3 glmVec{ 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, One)
{
	Math::Vec3 TBVec;
	TBVec.SetOne();
	glm::vec3 glmVec{ 1.f, 1.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, Opposite)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec.Opposite();
	glm::vec3 glmVec{ -1.f, -2.f, -3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, MidPoint)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec.MidPoint({ -1.f, -2.f, -3.f });
	glm::vec3 glmVec{ 0.f, 0.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmVec));
}

TEST(Vector3, Distance)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	float TBDist = TBVec.Distance({ 1.f, 1.f, 1.f });
	EXPECT_TRUE(Vec3Test::IsEqual(TBDist, 2.23606f));
}

TEST(Vector3, SquareNorm)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	float TBSquareNorm = TBVec.SquareNorm();
	EXPECT_TRUE(Vec3Test::IsEqual(TBSquareNorm, 14.f));
}

TEST(Vector3, Norm)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	float TBNorm = TBVec.Norm();
	EXPECT_TRUE(Vec3Test::IsEqual(TBNorm, 3.741657f));
}

TEST(Vector3, Normalize)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec.Normalize();
	glm::vec3 glmResultExpected{ 1.f, 2.f, 3.f };
	glmResultExpected = glm::normalize(glmResultExpected);
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, DotProduct)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	float TBDotProduct = TBVec.DotProduct({ 2.f, 3.f, 4.f });
	float glmDot = glm::dot(glm::vec3{ 1.f, 2.f, 3.f }, glm::vec3{ 2.f, 3.f, 4.f });
	EXPECT_TRUE(Vec3Test::IsEqual(TBDotProduct, glmDot));
}

TEST(Vector3, CrossProduct)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec.CrossProduct({ 2.f, 3.f, 4.f });
	glm::vec3 glmCross = glm::cross(glm::vec3{ 1.f, 2.f, 3.f }, glm::vec3{ 2.f, 3.f, 4.f });
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmCross));
}

TEST(Vector3, RotateX_Test_1)
{
	Math::Vec3 TBVec{ 0.f, 1.f, 0.f };
	TBVec.RotateX(Math::Tools::PI / 2.f);
	glm::vec3 glmResultExpected{ 0.f, 0.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, RotateX_Test_2)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 1.f };
	TBVec.RotateX(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f });
	glm::vec3 glmResultExpected{ 1.f, 1.f, 2.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, RotateY_Test_1)
{
	Math::Vec3 TBVec{ 0.f, 0.f, 1.f };
	TBVec.RotateY(Math::Tools::PI / 2.f);
	glm::vec3 glmResultExpected{ 1.f, 0.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, RotateY_Test_2)
{
	Math::Vec3 TBVec{ 1.f, 1.f, 2.f };
	TBVec.RotateY(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f });
	glm::vec3 glmResultExpected{ 2.f, 1.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, RotateZ_Test_1)
{
	Math::Vec3 TBVec{ 0.f, 1.f, 0.f };
	TBVec.RotateZ(Math::Tools::PI / 2.f);
	glm::vec3 glmResultExpected{ 1.f, 0.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, RotateZ_Test_2)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 1.f };
	TBVec.RotateZ(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f });
	glm::vec3 glmResultExpected{ 2.f, 1.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Rotate_Test_1)
{
	Math::Vec3 TBVec{ 1.f, 0.f, 0.f };
	TBVec.Rotate(Math::Tools::PI / 2.f);
	glm::vec3 glmResultExpected{ 0.f, 0.f, -1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Rotate_Test_2)
{
	Math::Vec3 TBVec{ 2.f, 1.f, 1.f };
	TBVec.Rotate(Math::Tools::PI / 2.f, { 1.f, 1.f, 1.f });
	glm::vec3 glmResultExpected{ 1.f, 1.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Rotate_Test_3)
{
	Math::Vec3 TBVec{ 1.f, 0.f, 0.f };
	TBVec.Rotate({ Math::Tools::PI / 2.f, Math::Tools::PI / 2.f, Math::Tools::PI / 2.f });
	glm::vec3 glmResultExpected{ 0.f, 0.f, -1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Rotate_Test_4)
{
	Math::Vec3 TBVec{ 2.f, 1.f, 1.f };
	TBVec.Rotate({ Math::Tools::PI / 2.f, Math::Tools::PI / 2.f, Math::Tools::PI / 2.f }, { 1.f, 1.f, 1.f });
	glm::vec3 glmResultExpected{ 1.f, 1.f, 0.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}


//####################### UNIT TEST OPERATORS #######################

TEST(Vector3, Operator_Add_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	glm::vec3 glmResultExpected{ 3.f, 4.f, 5.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec + 2.f, glmResultExpected));
}

TEST(Vector3, Operator_Add_Vec3)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	glm::vec3 glmResultExpected{ 3.f, 5.f, 7.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1 + TBVec2, glmResultExpected));
}

TEST(Vector3, Operator_Substract_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	glm::vec3 glmResultExpected{ -1.f, 0.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec - 2.f, glmResultExpected));
}

TEST(Vector3, Operator_Substract_Vec3)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	glm::vec3 glmResultExpected{ -1.f, -1.f, -1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1 - TBVec2, glmResultExpected));
}

TEST(Vector3, Operator_Multiply_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	glm::vec3 glmResultExpected{ 2.f, 4.f, 6.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec * 2.f, glmResultExpected));
}

TEST(Vector3, Operator_Multiply_Vec4)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	glm::vec3 glmResultExpected{ 2.f, 6.f, 12.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1 * TBVec2, glmResultExpected));
}

TEST(Vector3, Operator_Divide_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	glm::vec3 glmResultExpected{ 0.5f, 1.f, 1.5f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec / 2.f, glmResultExpected));
}

TEST(Vector3, Operator_Divide_Vec4)
{
	Math::Vec3 TBVec1{ 2.f, 3.f, 4.f };
	Math::Vec3 TBVec2{ 1.f, 2.f, 3.f };
	glm::vec3 glmResultExpected{ 2.f, 1.5f, 1.333333f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1 / TBVec2, glmResultExpected));
}

TEST(Vector3, Operator_Add_Equal_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec += 2.f;
	glm::vec3 glmResultExpected{ 3.f, 4.f, 5.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Operator_Add_Equal_Vec4)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	TBVec1 += TBVec2;
	glm::vec3 glmResultExpected{ 3.f, 5.f, 7.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector3, Operator_Substract_Equal_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec -= 2.f;
	glm::vec3 glmResultExpected{ -1.f, 0.f, 1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Operator_Substract_Equal_Vec4)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	TBVec1 -= TBVec2;
	glm::vec3 glmResultExpected{ -1.f, -1.f, -1.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector3, Operator_Multiply_Equal_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec *= 2.f;
	glm::vec3 glmResultExpected{ 2.f, 4.f, 6.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Operator_Multiply_Equal_Vec4)
{
	Math::Vec3 TBVec1{ 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2{ 2.f, 3.f, 4.f };
	TBVec1 *= TBVec2;
	glm::vec3 glmResultExpected{ 2.f, 6.f, 12.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector3, Operator_Divide_Equal_Scalar)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	TBVec /= 2.f;
	glm::vec3 glmResultExpected{ 0.5f, 1.f, 1.5f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResultExpected));
}

TEST(Vector3, Operator_Divide_Equal_Vec4)
{
	Math::Vec3 TBVec1{ 2.f, 3.f, 4.f };
	Math::Vec3 TBVec2{ 1.f, 2.f, 3.f };
	TBVec1 /= TBVec2;
	glm::vec3 glmResultExpected{ 2.f, 1.5f, 1.333333f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec1, glmResultExpected));
}

TEST(Vector3, Operator_Bracket_0)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec[0], 1.f));
}

TEST(Vector3, Operator_Bracket_1)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec[1], 2.f));
}

TEST(Vector3, Operator_Bracket_2)
{
	Math::Vec3 TBVec{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec[2], 3.f));
}

TEST(Vector3, Operator_Equal_Scalar)
{
	Math::Vec3 TBVec = 2.f;
	glm::vec3 glmResult{ 2.f, 2.f, 2.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResult));
}

TEST(Vector3, Operator_Equal_Vec4)
{
	Math::Vec3 TBVec = { 1.f, 2.f, 3.f };
	glm::vec3 glmResult{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(Vec3Test::IsEqual(TBVec, glmResult));
}

TEST(Vector3, Operator_Equal_Equal_Test_1)
{
	Math::Vec3 TBVec1 = { 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2 = { 1.f, 2.f, 3.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec3 glmResult{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(isEqual == Vec3Test::IsEqual(TBVec1, glmResult));
}

TEST(Vector3, Operator_Equal_Equal_Test_2)
{
	Math::Vec3 TBVec1 = { 0.f, 2.f, 3.f };
	Math::Vec3 TBVec2 = { 1.f, 2.f, 3.f };
	bool isEqual = TBVec1 == TBVec2;
	glm::vec3 glmResult{ 1.f, 2.f, 3.f };
	EXPECT_TRUE(isEqual == Vec3Test::IsEqual(TBVec1, glmResult) && Vec3Test::IsEqual(TBVec2, glmResult));
}

TEST(Vector3, Operator_Different_Test_1)
{
	Math::Vec3 TBVec1 = { 0.f, 2.f, 3.f };
	Math::Vec3 TBVec2 = { 1.f, 2.f, 3.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec3Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec3Test::IsEqual(TBVec1[1], TBVec2[1]) || !Vec3Test::IsEqual(TBVec1[2], TBVec2[2])));
}

TEST(Vector3, Operator_Different_Test_2)
{
	Math::Vec3 TBVec1 = { 1.f, 2.f, 3.f };
	Math::Vec3 TBVec2 = { 1.f, 2.f, 3.f };
	EXPECT_TRUE((TBVec1 != TBVec2) == (!Vec3Test::IsEqual(TBVec1[0], TBVec2[0]) || !Vec3Test::IsEqual(TBVec1[1], TBVec2[1]) || !Vec3Test::IsEqual(TBVec1[2], TBVec2[2])));
}