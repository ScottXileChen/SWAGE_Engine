#pragma once

namespace SWAGE::Math
{
	struct Vector2
	{
		float x, y;

		// constexpr - constant expression
		// expression means that code clause evaluates to a single value of a single type
		constexpr Vector2() noexcept : Vector2{ 0.0f } {}
		constexpr explicit Vector2(float f) noexcept : Vector2{ f,f } {}
		constexpr Vector2(float x, float y) noexcept : x{ x }, y{ y } {}

		// Commonly used vectors
		// TODO: Add One, XAxis, YAxis
		const static Vector2 Zero;
		const static Vector2 One;
		const static Vector2 XAxis;
		const static Vector2 YAxis;

		// Const operators, they return a new vector without changing itself
		// TODO: Add operator+ vec, - vec, * float, / float
		constexpr Vector2 operator-()					const { return Vector2(-x, -y); }
		constexpr Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
		constexpr Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
		constexpr Vector2 operator*(float s)			const { return Vector2(x * s, y * s); }
		constexpr Vector2 operator/(float s)			const { return Vector2(x / s, y / s); }

		// Mutating operators, these changes itself and return itself out
		// TODO: Add operator-= vec, *= float, /= float
		//Vector3& operator+=(const Vector3& v) { ....... return *this; }
		constexpr Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
		constexpr Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		constexpr Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
		constexpr Vector2& operator/=(float s) { x /= s; y /= s; return *this; }
	};
}