#pragma once

#include "Common.h"

#include "Constants.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Quaternion.h"

#include "Matrix3.h"
#include "Matrix4.h"

#include "Shapes.h"

#include "Random.h"

namespace SWAGE::Math
{
	// For Vector2
	inline float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	constexpr float MagnitudeSqr(const Vector2& v)
	{
		return (v.x * v.x) + (v.y * v.y);
	}

	inline float Magnitude(const Vector2& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	inline Vector2 Normalize(const Vector2& v)
	{
		return v / Magnitude(v);
	}

	constexpr float DistanceSqr(const Vector2& a, const Vector2& b)
	{
		return MagnitudeSqr(a - b);
	}

	inline float Distance(const Vector2& v0, const Vector2& v1)
	{
		return sqrt(DistanceSqr(v0, v1));
	}

	// For Vector3
	constexpr float Dot(const Vector3& v0, const Vector3& v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	}

	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	inline float Magnitude(const Vector3& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	constexpr float DistanceSqr(const Vector3& v0, const Vector3& v1)
	{
		return MagnitudeSqr(v0 - v1);
	}

	inline float Distance(const Vector3& v0, const Vector3& v1)
	{
		return sqrt(DistanceSqr(v0, v1));
	}

	inline Vector3 Normalize(const Vector3& v)
	{
		return v / Magnitude(v);
	}

	constexpr Vector3 Cross(const Vector3& u, const Vector3& v)
	{
		return Vector3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), (u.x * v.y) - (u.y * v.x));
	}

	// For Matrix3
	inline Vector2 TransformCoord(const Vector2& v, const Matrix3& m)
	{
		return Vector2
		(
			v.x * m._11 + v.y * m._21 + m._31,
			v.x * m._12 + v.y * m._22 + m._32
		);
	}

	inline float Determinant(const Matrix3& m)
	{
		float det = 0.0f;
		det = (m._11 * (m._22 * m._33 - m._23 * m._32));
		det -= (m._12 * (m._21 * m._33 - m._23 * m._31));
		det += (m._13 * (m._21 * m._32 - m._22 * m._31));
		return det;
	}

	inline Matrix3 Adjoint(const Matrix3& m)
	{
		return Matrix3
		(
			(m._22 * m._33 - m._23 * m._32),
			-(m._12 * m._33 - m._13 * m._32),
			(m._12 * m._23 - m._13 * m._22),

			-(m._21 * m._33 - m._23 * m._31),
			(m._11 * m._33 - m._13 * m._31),
			-(m._11 * m._23 - m._13 * m._21),

			(m._21 * m._32 - m._22 * m._31),
			-(m._11 * m._32 - m._12 * m._31),
			(m._11 * m._22 - m._12 * m._21)
		);
	}

	inline Matrix3 Inverse(const Matrix3& m)
	{
		const float determinant = Determinant(m);
		const float invDet = 1.0f / determinant;
		return Adjoint(m) * invDet;
	}

	inline Vector2 TransformNormal(const Vector2& v, const Matrix3& m)
	{
		return Vector2
		(
			v.x * m._11 + v.y * m._21,
			v.x * m._12 + v.y * m._22
		);
	}

	// For Matrix4
	constexpr Vector3 GetTranslation(const Matrix4& m)
	{
		return { m._41, m._42, m._43 };
	}

	inline Vector3 TransformCoord(Vector3 v, Matrix4 m) // assume w = 1
	{
		const float invW = 1.0f / ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44));
		return Vector3
		(
			//v.X * m._11 + v.Y * m._21 + v.Z * m._31 + m._41,
			//v.X * m._12 + v.Y * m._22 + v.Z * m._32 + m._42,
			//v.X * m._13 + v.Y * m._23 + v.Z * m._33 + m._43

			(v.x * m._11 + v.y * m._21 + v.z * m._31 + (1.0f * m._41)) * invW, //+ m._41,
			(v.x * m._12 + v.y * m._22 + v.z * m._32 + (1.0f * m._42)) * invW, //+ m._42,
			(v.x * m._13 + v.y * m._23 + v.z * m._33 + (1.0f * m._43)) * invW  //+ m._43
		);
	}

	inline Vector3 TransformNormal(Vector3 v, Matrix4 m) // assume w = 0
	{
		return Vector3
		(
			v.x * m._11 + v.y * m._21 + v.z * m._31,
			v.x * m._12 + v.y * m._22 + v.z * m._32,
			v.x * m._13 + v.y * m._23 + v.z * m._33
		);
	}

	inline float Determinant(Matrix4 m)
	{
		float det = 0.0f;
		det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
		det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
		det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
		det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
		return det;
	}

	inline Matrix4 Adjoint(Matrix4 m)
	{
		return Matrix4
		(
			(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
			-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
			(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
			-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

			-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
			(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
			-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
			(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

			(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
			-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
			(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
			-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

			-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
			(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
			-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
			(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
		);
	}

	inline Matrix4 Transpose(Matrix4 m)
	{
		return Matrix4
		(
			m._11, m._21, m._31, m._41,
			m._12, m._22, m._32, m._42,
			m._13, m._23, m._33, m._43,
			m._14, m._24, m._34, m._44
		);
	}

	inline Matrix4 Inverse(Matrix4 m)
	{
		const float determinant = Determinant(m);
		const float invDet = 1.0f / determinant;
		return Adjoint(m) * invDet;
	}

	// For Quaternion
	inline float Magnitude(const Quaternion& q)
	{
		return sqrt((q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z));
	}

	inline Quaternion Normalize(const Quaternion& q)
	{
		return q / Magnitude(q);
	}

	constexpr Quaternion Lerp(Quaternion q0, Quaternion q1, float t)
	{
		return q0 * (1.0f - t) + (q1 * t);
	}

	Quaternion Slerp(Quaternion q0, Quaternion q1, float t);

	template <class T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <class T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <class T>
	constexpr T Clamp(T value, T min, T max)
	{
		return Max(min, Min(max, value));
	}

	template <class T>
	constexpr T Lerp(T a, T b, float t)
	{
		return a + (b - a) * t;
	}

	constexpr float Abs(float value)
	{
		return value >= 0.0f ? value : -value;
	}

	constexpr float Sqr(float value)
	{
		return value * value;
	}
}