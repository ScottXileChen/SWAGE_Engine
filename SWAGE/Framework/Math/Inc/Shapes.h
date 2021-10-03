#pragma once

namespace SWAGE::Math::Shapes
{
	struct LineSegment
	{
		Vector2 from;
		Vector2 to;

		LineSegment() : from(0.0f, 0.0f), to(0.0f, 0.0f) {}
		LineSegment(float x0, float y0, float x1, float y1) : from(x0, y0), to(x1, y1) {}
		LineSegment(const Vector2& v0, const Vector2& v1) : from(v0), to(v1) {}
	};

	struct Rect
	{
		#pragma warning(push)
		#pragma warning(disable: 4201)
		union
		{
			struct { float left, top; };
			Vector2 min;
		};
		union
		{
			struct { float right, bottom; };
			Vector2 max;
		};
		#pragma warning(pop)

		constexpr Rect() : Rect{ 0.0f, 0.0f, 1.0f, 1.0f } {}
		constexpr Rect(float left, float top, float right, float bottom) : left{ left }, top{ top }, right{ right }, bottom{ bottom } {}
	};

	struct Circle
	{
		Math::Vector2 center;
		float radius;

		Circle() : center(0.0f, 0.0f), radius(1.0f) {}
		Circle(const Math::Vector2& center, float radius) : center(center), radius(radius) {}
		Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
	};

	struct AABB
	{
		Vector3 center;
		Vector3 extend;

		AABB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f) {}
		AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}

		constexpr Vector3 Min() const { return center - extend; }
		constexpr Vector3 Max() const { return center + extend; }
	};

	//struct OBB
	//{
	//	Vector3 center;
	//	Vector3 extend;
	//	Quaternion orientation;

	//	OBB()
	//		: center(0.0f, 0.0f, 0.0f)
	//		, extend(1.0f, 1.0f, 1.0f)
	//		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	//	{}

	//	OBB(float x, float y, float z, float sx, float sy, float sz)
	//		: center(x, y, z)
	//		, extend(sx, sy, sz)
	//		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	//	{}

	//	OBB(float x, float y, float z, float sx, float sy, float sz, const Quaternion& orientation)
	//		: center(x, y, z)
	//		, extend(sx, sy, sz)
	//		, orientation(orientation)
	//	{}

	//	OBB(const Vector3& center, const Vector3& extend, const Quaternion& orientation)
	//		: center(center)
	//		, extend(extend)
	//		, orientation(orientation)
	//	{}
	//};

	struct Sphere
	{
		Vector3 center;
		float radius;

		Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f) {}
		Sphere(float x, float y, float z, float radius) : center(x, y, z), radius(radius) {}
		Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
	};

	struct Ray
	{
		Vector3 org;
		Vector3 dir;

		Ray() : org(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, 1.0f) {}
		Ray(float x, float y, float z, float dx, float dy, float dz) : org(x, y, z), dir(dx, dy, dz) {}
		Ray(const Vector3& org, const Vector3& dir) : org(org), dir(dir) {}

		Vector3 GetPoint(float distance) { return org + (dir * distance); }
	};

	bool PointInCircle(const Vector2& point, const Circle& circle);

	bool Intersect(const LineSegment& a, const LineSegment& b, Vector2* intersection = nullptr);
	bool Intersect(const Circle& c0, const Circle& c1);
	bool Intersect(const Rect& r0, const Rect& r1);
	bool Intersect(const LineSegment& l, const Circle& c);
	bool Intersect(const Circle& c, const LineSegment& l, Vector2* closestPoint = nullptr);
	bool Intersect(const Circle& c, const Rect& r);
	bool Intersect(const Rect& r, const Circle& c);
	bool Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance);
	bool Intersect(const Ray& ray, const Sphere& sphere, float& distance);
	bool Intersect(const AABB& a, const AABB& b);
}