#include <gtest/gtest.h>
#include <glm/ext/quaternion_float.hpp>
#include  <glm/gtc/quaternion.hpp>
#include "Quat.hpp"
#include "Tools.hpp"



using namespace Math;

bool IsEqual(Quat _quat, glm::quat _glmQuat)
{
	return fabsf(_quat.w - _glmQuat.w) <= Tools::epsilon && fabsf(_quat.x - _glmQuat.x) <= Tools::epsilon && fabsf(_quat.y - _glmQuat.y) <= Tools::epsilon && fabsf(_quat.z - _glmQuat.z) <= Tools::epsilon;
}

bool IsEqual(Vec3 _vec, glm::vec3 _glmVec)
{
	return fabsf(_vec.x - _glmVec.x) <= Tools::epsilon && fabsf(_vec.y - _glmVec.y) <= Tools::epsilon && fabsf(_vec.z - _glmVec.z) <= Tools::epsilon;
}

bool IsEqual(Vec3 _vec, Vec3 _testVec)
{
	return fabsf(_vec.x - _testVec.x) <= Tools::epsilon && fabsf(_vec.y - _testVec.y) <= Tools::epsilon && fabsf(_vec.z - _testVec.z) <= Tools::epsilon;
}

namespace QuatTest 
{
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
}


/// Constructors Tests ///

TEST(Quat, ScalarConstructor)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	glm::quat glmQuat{ 1.f, theta, theta, theta };
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, VectorConstructor)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, Vec3{theta, theta, theta} };
	glm::quat glmQuat{ 1.f, glm::vec3{theta, theta, theta} };
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, EulerConstructor)
{
	Quat quat = Quat::s_QuaternionEuler(50.f, 195.f, -34.f);
	
	glm::quat expectedQuat{ 0.0093766f, -0.3154642f, 0.8431636f, 0.4352809f }; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_TRUE(IsEqual(quat, expectedQuat));
}

/// Functions Tests ///

TEST(Quat, Identity)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat.Identity();
	glm::quat glmQuat{ 1.f, 0.f, 0.f, 0.f };
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, GetEulerAnglesRadZYX)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta / 4.f, -2.f * theta, theta };
	Vec3 v = quat.GetEulerAnglesRadZYX();

	Vec3 testVec{ -2.195963f, -0.5909724f, 3.0813772f }; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_TRUE(IsEqual(v, testVec));
}

TEST(Quat, GetEulerAnglesDegZYX)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta / 4.f, -2.f * theta, theta };
	Vec3 v = quat.GetEulerAnglesDegZYX();

	Vec3 testVec{ -125.8194108f, -33.8602254f, 176.5499104f }; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_NEAR(v.x, testVec.x, 0.001f);
	EXPECT_NEAR(v.y, testVec.y, 0.001f);
	EXPECT_NEAR(v.z, testVec.z, 0.001f);
}

TEST(Quat, GetEulerAnglesRadXYZ)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta / 4.f, -2.f * theta, theta };
	Vec3 v = quat.GetEulerAnglesRadXYZ();

	Vec3 testVec{ 2.1224166f, -0.3836195f, 2.6766869f }; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_TRUE(IsEqual(v, testVec));
}

TEST(Quat, GetEulerAnglesDegXYZ)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta / 4.f, -2.f * theta, theta };
	Vec3 v = quat.GetEulerAnglesDegXYZ();
	Vec3 testVec{ 121.605516f, -21.9797811f, 153.3628652f }; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_NEAR(v.x, testVec.x, 0.001f);
	EXPECT_NEAR(v.y, testVec.y, 0.001f);
	EXPECT_NEAR(v.z, testVec.z, 0.001f);
}

TEST(Quat, Norm)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	float norm = quat.Norm();

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	float glmNorm = sqrt(glmQuat.w * glmQuat.w + glmQuat.x * glmQuat.x + glmQuat.y * glmQuat.y + glmQuat.z * glmQuat.z);
	EXPECT_NEAR(norm, glmNorm, Tools::epsilon);
}

TEST(Quat, Normalize)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat.Normalize();

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = glm::normalize(glmQuat);
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, DotProduct)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta/2.f, theta, -theta };
	float dot = quat.DotProduct(quat2);

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2 { 1.f, theta / 2.f, theta, -theta };
	float glmDot = glm::dot(glmQuat, glmQuat2);
	EXPECT_NEAR(dot, glmDot, Tools::epsilon);
}

TEST(Quat, Inverse)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat.Inverse();
	
	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = glm::inverse(glmQuat);
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, Conjugate)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat.Conjugate();

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = glm::conjugate(glmQuat);
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, HamiltonProduct)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta/2.f, theta, -theta };
	quat.HamiltonProduct(quat2);

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat = glmQuat * glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

// X axis
TEST(Quat, RotateX)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, 0.f, 0.f };
	Vec3 v { 1.f, 0.f, 2.f };
	v = quat.Rotate(v);

	glm::quat glmQuat{ 1.f, theta, 0.f, 0.f };
	glmQuat = glm::normalize(glmQuat);
	glm::vec3 glmV{ 1.f, 0.f, 2.f };
	glm::quat rotatedV{ 0.f, glmV };
	rotatedV = glmQuat * rotatedV * glm::conjugate(glmQuat);
	glmV = { rotatedV.x, rotatedV.y, rotatedV.z };

	EXPECT_TRUE(IsEqual(v, glmV));
}

// Y axis
TEST(Quat, RotateY)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, 0.f, theta, 0.f };
	Vec3 v{ 1.f, 0.f, 2.f };
	v = quat.Rotate(v);

	glm::quat glmQuat{ 1.f, 0.f, theta, 0.f };
	glmQuat = glm::normalize(glmQuat);
	glm::vec3 glmV{ 1.f, 0.f, 2.f };
	glm::quat rotatedV{ 0.f, glmV };
	rotatedV = glmQuat * rotatedV * glm::conjugate(glmQuat);
	glmV = { rotatedV.x, rotatedV.y, rotatedV.z };

	EXPECT_TRUE(IsEqual(v, glmV));
}

// Z axis
TEST(Quat, RotateZ)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, 0.f, 0.f, theta };
	Vec3 v{ 1.f, 0.f, 2.f };
	v = quat.Rotate(v);

	glm::quat glmQuat{ 1.f, 0.f, 0.f, theta };
	glmQuat = glm::normalize(glmQuat);
	glm::vec3 glmV{ 1.f, 0.f, 2.f };
	glm::quat rotatedV{ 0.f, glmV };
	rotatedV = glmQuat * rotatedV * glm::conjugate(glmQuat);
	glmV = { rotatedV.x, rotatedV.y, rotatedV.z };

	EXPECT_TRUE(IsEqual(v, glmV));
}

// All axes
TEST(Quat, Rotate)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta/2.f, -2.f * theta };
	Vec3 v{ 1.f, 0.f, 2.f };
	v = quat.Rotate(v);

	glm::quat glmQuat{ 1.f, theta, theta / 2.f, -2.f * theta };
	glmQuat = glm::normalize(glmQuat);
	glm::vec3 glmV{ 1.f, 0.f, 2.f };
	glm::quat rotatedV{ 0.f, glmV };
	rotatedV = glmQuat * rotatedV * glm::conjugate(glmQuat);
	glmV = { rotatedV.x, rotatedV.y, rotatedV.z };

	EXPECT_TRUE(IsEqual(v, glmV));
}

TEST(Quat, MatrixConversion)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Mat4 mat = quat.GetTransformMatrix(Vec3{0.f, 0.f, 0.f});

	glm::mat4 expectedMatrix
	{ 
		-0.174645f, 0.213421f, 0.961223f, 0.f,
		0.961223f, -0.174645f, 0.213421f, 0.f,
		0.213421f, 0.961223f, -0.174645f, 0.f, 
		0.f, 0.f, 0.f, 1.f
	}; // Results from https://www.andre-gaschler.com/rotationconverter/
	EXPECT_TRUE(QuatTest::IsEqual(mat, expectedMatrix));
}

TEST(Quat, Slerp)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta/2.f, theta, -theta };
	quat.Slerp(quat2, 0.2f);

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat = glm::slerp(glmQuat, glmQuat2, 0.2f);
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

/// Operators Tests ///

TEST(Quat, Addition)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat = quat + quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat = glmQuat + glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, AdditionEqual)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat += quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat += glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, Substraction)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat = quat - quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat = glmQuat - glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, SubstractionEqual)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat -= quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat -= glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, Opposite)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat = -quat;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = -glmQuat;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, MultiplicationQuat)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat = quat * quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat = glmQuat * glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, MultiplicationScalar)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat = quat * 4.5f;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = glmQuat * 4.5f;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, DivisionScalar)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat = quat / 4.5f;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat = glmQuat / 4.5f;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, MultiplicationEqualQuat)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	Quat quat2{ 1.f, theta / 2.f, theta, -theta };
	quat *= quat2;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glm::quat glmQuat2{ 1.f, theta / 2.f, theta, -theta };
	glmQuat *= glmQuat2;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, MultiplicationEqualScalar)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat *= 4.5f;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat *= 4.5f;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}

TEST(Quat, DivisionEqualScalar)
{
	float theta = Tools::PI / 2.f;
	Quat quat{ 1.f, theta, theta, theta };
	quat /= 4.5f;

	glm::quat glmQuat{ 1.f, theta, theta, theta };
	glmQuat /= 4.5f;
	EXPECT_TRUE(IsEqual(quat, glmQuat));
}
