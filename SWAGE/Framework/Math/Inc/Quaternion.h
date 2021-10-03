#pragma once

namespace SWAGE::Math
{
	struct Matrix4;

	struct Quaternion
	{
		float w, x, y, z;

		constexpr Quaternion() noexcept : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
		constexpr Quaternion(float w, float x, float y, float z) noexcept : w(w), x(x), y(y), z(z) {}

		const static Quaternion Zero;
		const static Quaternion Identity;

		const static Quaternion RotationAxis(const Vector3& axis, float rad);
		const static Quaternion RotationMatrix(const Matrix4& m);
		const static Quaternion RotationLook(const Vector3& direction, const Vector3& up = Vector3::YAxis);
		const static Quaternion RotationFromTo(const Vector3& from, const Vector3& to);

		constexpr Quaternion operator-() const { return Quaternion(-w, -x, -y, -z); }
		constexpr Quaternion operator+(const Quaternion& q) const { return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z); }
		constexpr Quaternion operator-(const Quaternion& q) const { return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z); }
		constexpr Quaternion operator*(const Quaternion& q) const
		{
			Quaternion result
			{
				(q.w * w) + (-q.x * x) + (-q.y * y) + (-q.z * z),
				(q.w * x) + (q.x * w) + (-q.y * z) + (q.z * y),
				(q.w * y) + (q.x * z) + (q.y * w) + (-q.z * x),
				(q.w * z) + (-q.x * y) + (q.y * x) + (q.z * w),
			};
			return result;
		}
		constexpr Quaternion operator*(float s) const { return Quaternion(w * s, x * s, y * s, z * s); }
		constexpr Quaternion operator/(float s) const { return Quaternion(w / s, x / s, y / s, z / s); }
	};

	// Add to Matrix4.h:
	// static Matrix4 RotationQuaternion(const Quaternion& q);

	// Add to EngineMath.h:
	// inline float Magnitude(const Quaternion& q);
	// inline Quaternion Normalize(const Quaternion& q);
	// constexpr Quaternion Lerp(Quaternion q0, Quaternion q1, float t);
	// Quaternion Slerp(Quaternion q0, Quaternion q1, float t);
}