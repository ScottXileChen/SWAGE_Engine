#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SWAGE::Math;

namespace MathTest
{
	TEST_CLASS(Vector3Test)
	{
	public:
		TEST_METHOD(TestConstructor1)
		{
			Vector3 v;
			Assert::AreEqual(v.x, 0.0f, 0.0001f);
			Assert::AreEqual(v.y, 0.0f, 0.0001f);
			Assert::AreEqual(v.z, 0.0f, 0.0001f);
		}

		TEST_METHOD(TestConstructor2)
		{
			Vector3 v(5);
			Assert::AreEqual(v.x, 5.0f, 0.0001f);
			Assert::AreEqual(v.y, 5.0f, 0.0001f);
			Assert::AreEqual(v.z, 5.0f, 0.0001f);
		}

		TEST_METHOD(TestConstructor3)
		{
			Vector3 v(1,2,3);
			Assert::AreEqual(v.x, 1.0f, 0.0001f);
			Assert::AreEqual(v.y, 2.0f, 0.0001f);
			Assert::AreEqual(v.z, 3.0f, 0.0001f);
		}

		// TODO: Add more test methods for Vector3 helpers in EngineMath.h
		TEST_METHOD(TestZero)
		{
			Vector3 v = Vector3::Zero;
			Assert::AreEqual(v.x, 0.0f, 0.0001f);
			Assert::AreEqual(v.y, 0.0f, 0.0001f);
			Assert::AreEqual(v.z, 0.0f, 0.0001f);
		}

		TEST_METHOD(TestOne)
		{
			Vector3 v = Vector3::One;
			Assert::AreEqual(v.x, 1.0f, 0.0001f);
			Assert::AreEqual(v.y, 1.0f, 0.0001f);
			Assert::AreEqual(v.z, 1.0f, 0.0001f);
		}

		TEST_METHOD(TestXAxis)
		{
			Vector3 v = Vector3::XAxis;
			Assert::AreEqual(v.x, 1.0f, 0.0001f);
			Assert::AreEqual(v.y, 0.0f, 0.0001f);
			Assert::AreEqual(v.z, 0.0f, 0.0001f);
		}

		TEST_METHOD(TestYAxis)
		{
			Vector3 v = Vector3::YAxis;
			Assert::AreEqual(v.x, 0.0f, 0.0001f);
			Assert::AreEqual(v.y, 1.0f, 0.0001f);
			Assert::AreEqual(v.z, 0.0f, 0.0001f);
		}

		TEST_METHOD(TestZAxis)
		{
			Vector3 v = Vector3::ZAxis;
			Assert::AreEqual(v.x, 0.0f, 0.0001f);
			Assert::AreEqual(v.y, 0.0f, 0.0001f);
			Assert::AreEqual(v.z, 1.0f, 0.0001f);
		}

		TEST_METHOD(TestOperatorNegative)
		{
			Vector3 v(1, 1, 1);
			v = -v;
			Assert::AreEqual(v.x, -1.0f, 0.0001f);
			Assert::AreEqual(v.y, -1.0f, 0.0001f);
			Assert::AreEqual(v.z, -1.0f, 0.0001f);
		}

		TEST_METHOD(TestOperatorPlus)
		{
			Vector3 v(1, 1, 1);
			Vector3 v1(2.5f, 2.3f, 1.4f);
			v = v + v1;
			Assert::AreEqual(v.x, 3.5f, 0.0001f);
			Assert::AreEqual(v.y, 3.3f, 0.0001f);
			Assert::AreEqual(v.z, 2.4f, 0.0001f);

			Vector3 result;
			result = v + v1;
			Assert::AreEqual(result.x, 6.0f, 0.0001f);
			Assert::AreEqual(result.y, 5.6f, 0.0001f);
			Assert::AreEqual(result.z, 3.8f, 0.0001f);

			result += v;
			Assert::AreEqual(result.x, 9.5f, 0.0001f);
			Assert::AreEqual(result.y, 8.9f, 0.0001f);
			Assert::AreEqual(result.z, 6.2f, 0.0001f);
		}

		TEST_METHOD(TestOperatorMinus)
		{
			Vector3 v(1, 1, 1);
			Vector3 v1(2.5f, 2.3f, 1.4f);
			v = v - v1;
			Assert::AreEqual(v.x, -1.5f, 0.0001f);
			Assert::AreEqual(v.y, -1.3f, 0.0001f);
			Assert::AreEqual(v.z, -0.4f, 0.0001f);

			Vector3 result;
			result = v - v1;
			Assert::AreEqual(result.x, -4.0f, 0.0001f);
			Assert::AreEqual(result.y, -3.6f, 0.0001f);
			Assert::AreEqual(result.z, -1.8f, 0.0001f);

			result -= v1;
			Assert::AreEqual(result.x, -6.5f, 0.0001f);
			Assert::AreEqual(result.y, -5.9f, 0.0001f);
			Assert::AreEqual(result.z, -3.2f, 0.0001f);
		}

		TEST_METHOD(TestOperatorMutiply)
		{
			float f1 = 1.0f;
			Vector3 v1(2.5f, 2.3f, 1.4f);
			v1 = v1 * f1;
			Assert::AreEqual(v1.x, 2.5f, 0.0001f);
			Assert::AreEqual(v1.y, 2.3f, 0.0001f);
			Assert::AreEqual(v1.z, 1.4f, 0.0001f);

			Vector3 result;
			float f2 = 2.0f;
			result = v1 * f2;
			Assert::AreEqual(result.x, 5.0f, 0.0001f);
			Assert::AreEqual(result.y, 4.6f, 0.0001f);
			Assert::AreEqual(result.z, 2.8f, 0.0001f);

			float f3 = 3.0f;
			result *= f3;
			Assert::AreEqual(result.x, 15.0f, 0.0001f);
			Assert::AreEqual(result.y, 13.8f, 0.0001f);
			Assert::AreEqual(result.z, 8.4f, 0.0001f);
		}

		TEST_METHOD(TestOperatorDivide)
		{
			float f1 = 1.0f;
			Vector3 v1(2.5f, 2.3f, 1.4f);
			v1 = v1 / f1;
			Assert::AreEqual(v1.x, 2.5f, 0.0001f);
			Assert::AreEqual(v1.y, 2.3f, 0.0001f);
			Assert::AreEqual(v1.z, 1.4f, 0.0001f);

			Vector3 result;
			float f2 = 2.0f;
			result = v1 / f2;
			Assert::AreEqual(result.x, 1.25f, 0.0001f);
			Assert::AreEqual(result.y, 1.15f, 0.0001f);
			Assert::AreEqual(result.z, 0.7f, 0.0001f);

			float f3 = 3.0f;
			result /= f3;
			Assert::AreEqual(result.x, 0.41666f, 0.0001f);
			Assert::AreEqual(result.y, 0.38333f, 0.0001f);
			Assert::AreEqual(result.z, 0.23333f, 0.0001f);
		}
	};

	TEST_CLASS(Matrix4Test)
	{
	public:
		TEST_METHOD(TestIdentity)
		{
			Matrix4 value = Matrix4::Identity;
			Matrix4 expected = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestRotationX)
		{
			Matrix4 value = Matrix4::RotationX(0.47f);
			Matrix4 expected = Matrix4(1, 0, 0, 0, 0, cos(0.47f), sin(0.47f), 0, 0, -sin(0.47f), cos(0.47f), 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestRotationY)
		{
			Matrix4 value = Matrix4::RotationY(0.33f);
			Matrix4 expected = Matrix4(cos(0.33f), 0, -sin(0.33f), 0, 0, 1, 0, 0, sin(0.33f), 0, cos(0.33f), 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestRotationZ)
		{
			Matrix4 value = Matrix4::RotationZ(0.26f);
			Matrix4 expected = Matrix4(cos(0.26f), sin(0.26f), 0, 0, -sin(0.26f), cos(0.26f), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestScaling)
		{
			Matrix4 value = Matrix4::Scaling(0.77f);
			Matrix4 expected = Matrix4(0.77f, 0, 0, 0, 0, 0.77f, 0, 0, 0, 0, 0.77f, 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestScaling2)
		{
			Matrix4 value = Matrix4::Scaling(Vector3(1.2f, 2.3f, 3.4f));
			Matrix4 expected = Matrix4(1.2f, 0, 0, 0, 0, 2.3f, 0, 0, 0, 0, 3.4f, 0, 0, 0, 0, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestTranslation)
		{
			Matrix4 value = Matrix4::Translation(Vector3(1.2f, 2.3f, 3.4f));
			Matrix4 expected = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1.2f, 2.3f, 3.4f, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestTranslation2)
		{
			Matrix4 value = Matrix4::Translation(Vector3(2.2f, 3.3f, 4.4f));
			Matrix4 expected = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2.2f, 3.3f, 4.4f, 1);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestTransformCoord)
		{
			Vector3 value = TransformCoord(Vector3( 0, 1, 0 ), Matrix4::RotationX(1.57f) * Matrix4::Translation(Vector3( 1, 0, 1 )));
			Vector3 expected = Vector3(1, 0, 2);
			Assert::AreEqual(value.x, expected.x, 0.001f);
			Assert::AreEqual(value.y, expected.y, 0.001f);
			Assert::AreEqual(value.z, expected.z, 0.001f);
		}

		TEST_METHOD(TestTransformNormal)
		{
			Vector3 value = SWAGE::Math::TransformNormal(Vector3(0, 1, 0), Matrix4::RotationZ(1.57f) * Matrix4::Translation(Vector3(1, 0, 1)));
			Vector3 expected = Vector3(-1.0f, 0, 0);
			Assert::AreEqual(value.x, expected.x, 0.001f);
			Assert::AreEqual(value.y, expected.y, 0.001f);
			Assert::AreEqual(value.z, expected.z, 0.001f);
		}

		TEST_METHOD(TestDeterminant)
		{
			float value = SWAGE::Math::Determinant(Matrix4(1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3));
			float expected = 23.0f;
			Assert::AreEqual(value, expected);
		}

		TEST_METHOD(TestAdjoint)
		{
			Matrix4 value = SWAGE::Math::Adjoint(Matrix4(1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3));
			Matrix4 expected = Matrix4(-41, 22, 20, -15, -15, 3, 9, -1, 22, -9, -4, 3, 5, -1, -3, 8);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestTranspose)
		{
			Matrix4 value = SWAGE::Math::Transpose(Matrix4(1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3));
			Matrix4 expected = Matrix4(1, 2, 1, 0, -1, -3, 2, 1, 2, 1, 3, 0, 1, 3, 1, 3);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

		TEST_METHOD(TestInverse)
		{
			Matrix4 value = SWAGE::Math::Inverse(Matrix4(0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 2, -5, 8, 1));
			Matrix4 expected = Matrix4(0, -1, 0, 0, 1, 0, 0, 0, 0.625f, 0.25f, -0.125f, 0.125f, 0, 0, 1, 0);
			Assert::AreEqual(value._11, expected._11);
			Assert::AreEqual(value._12, expected._12);
			Assert::AreEqual(value._13, expected._13);
			Assert::AreEqual(value._14, expected._14);
			Assert::AreEqual(value._21, expected._21);
			Assert::AreEqual(value._22, expected._22);
			Assert::AreEqual(value._23, expected._23);
			Assert::AreEqual(value._24, expected._24);
			Assert::AreEqual(value._31, expected._31);
			Assert::AreEqual(value._32, expected._32);
			Assert::AreEqual(value._33, expected._33);
			Assert::AreEqual(value._34, expected._34);
			Assert::AreEqual(value._41, expected._41);
			Assert::AreEqual(value._42, expected._42);
			Assert::AreEqual(value._43, expected._43);
			Assert::AreEqual(value._44, expected._44);
		}

	};
}