#pragma once

namespace SWAGE::Math
{
	// Random
	int Random();
	int Random(int min, int max);
	float RandomFloat();
	float RandomFloat(float min, float max);
	double RandomDouble();
	double RandomDouble(double min, double max);
	float RandomNormal(float mean, float stdev);
	Vector2 RandomVector2();
	Vector2 RandomVector2(const Math::Vector2& min, const Math::Vector2& max);
	Vector2 RandomUnitCircle(bool normalized);
	Vector3 RandomVector3();
	Vector3 RandomVector3(const Math::Vector3& min, const Math::Vector3& max);
	Vector3 RandomUnitSphere();
}