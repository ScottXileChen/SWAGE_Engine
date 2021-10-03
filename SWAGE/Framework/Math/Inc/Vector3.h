#pragma once

namespace SWAGE::Math
{
	struct Vector3
	{
		float x, y, z;

		// constexpr - constant expression
		// expression means that code clause evaluates to a single value of a single type
		constexpr Vector3() noexcept : Vector3{ 0.0f } {}
		constexpr explicit Vector3(float f) noexcept : Vector3{ f,f,f } {}
		constexpr Vector3(float x, float y, float z) noexcept : x{ x }, y{ y }, z{ z } {}

		// Commonly used vectors
		// TODO: Add One, XAxis, YAxis, and ZAxis
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;

		// Const operators, they return a new vector without changing itself
		// TODO: Add operator+ vec, - vec, * float, / float
		constexpr Vector3 operator-()					const { return Vector3(-x, -y, -z); }
		constexpr Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
		constexpr Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
		constexpr Vector3 operator*(float s)			const { return Vector3(x * s, y * s, z * s); }
		constexpr Vector3 operator/(float s)			const { return Vector3(x / s, y / s, z / s); }

		// Mutating operators, these changes itself and return itself out
		// TODO: Add operator-= vec, *= float, /= float
		//Vector3& operator+=(const Vector3& v) { ....... return *this; }
		constexpr Vector3& operator+=(const Vector3& rhs)		{ x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		constexpr Vector3& operator-=(const Vector3& rhs)		{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		constexpr Vector3& operator*=(float s)					{ x *= s; y *= s; z *= s; return *this; }
		constexpr Vector3& operator/=(float s)					{ x /= s; y /= s; z /= s; return *this; }
	};
}