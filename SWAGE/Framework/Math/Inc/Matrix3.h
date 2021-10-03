#pragma once

namespace SWAGE::Math
{
	struct Matrix3
	{
		union
		{
			struct // row + column subscript
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			std::array<float, 9> v;
		};

		constexpr Matrix3()
			: _11(1.0f), _12(0.0f), _13(0.0f)
			, _21(0.0f), _22(1.0f), _23(0.0f)
			, _31(0.0f), _32(0.0f), _33(1.0f)
		{}

		constexpr Matrix3(
			float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33)
			: _11(_11), _12(_12), _13(_13)
			, _21(_21), _22(_22), _23(_23)
			, _31(_31), _32(_32), _33(_33)
		{}

		constexpr Matrix3 operator-() const
		{
			return Matrix3(
				-_11, -_12, -_13,
				-_21, -_22, -_23,
				-_31, -_32, -_33);
		}

		constexpr Matrix3 operator+(const Matrix3& rhs) const
		{
			return Matrix3(
				_11 + rhs._11, _12 + rhs._12, _13 + rhs._13,
				_21 + rhs._21, _22 + rhs._22, _23 + rhs._23,
				_31 + rhs._31, _32 + rhs._32, _33 + rhs._33);
		}

		constexpr Matrix3 operator-(const Matrix3& rhs) const
		{
			return Matrix3(
				_11 - rhs._11, _12 - rhs._12, _13 - rhs._13,
				_21 - rhs._21, _22 - rhs._22, _23 - rhs._23,
				_31 - rhs._31, _32 - rhs._32, _33 - rhs._33);
		}

		constexpr Matrix3 operator*(const Matrix3& rhs) const
		{
			return Matrix3(
				(_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31),
				(_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32),
				(_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33),

				(_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31),
				(_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32),
				(_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33),

				(_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31),
				(_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32),
				(_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33));
		}

		constexpr Matrix3 operator*(float s) const
		{
			return Matrix3(
				_11 * s, _12 * s, _13 * s,
				_21 * s, _22 * s, _23 * s,
				_31 * s, _32 * s, _33 * s);
		}

		constexpr Matrix3 operator/(float s) const
		{
			return Matrix3(
				_11 / s, _12 / s, _13 / s,
				_21 / s, _22 / s, _23 / s,
				_31 / s, _32 / s, _33 / s);
		}

		constexpr Matrix3 operator+=(const Matrix3& rhs)
		{
			_11 += rhs._11; _12 += rhs._12; _13 += rhs._13;
			_21 += rhs._21; _22 += rhs._22; _23 += rhs._23;
			_31 += rhs._31; _32 += rhs._32; _33 += rhs._33;
			return *this;
		}

		const static Matrix3 Zero;
		const static Matrix3 Identity;
		const static Matrix3 Translation(float x, float y);
		const static Matrix3 Translation(const Vector2& v);
		const static Matrix3 Rotation(float rad);
		const static Matrix3 Scaling(float s);
		const static Matrix3 Scaling(float sx, float sy);
		const static Matrix3 Scaling(const Vector2& s);
	};
}