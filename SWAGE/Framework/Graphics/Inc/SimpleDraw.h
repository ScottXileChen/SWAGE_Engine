#pragma once

#include "Colors.h"

namespace SWAGE::Graphics
{
	class Camera;
}

namespace SWAGE::Graphics::SimpleDraw
{
	void StaticInitialize(uint32_t maxVertexCount = 10000);
	void StaticTerminate();

	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);

	void AddAABB(const Math::Vector3& center, const Math::Vector3& extend, const Color& color);
	void AddSphere(const Math::Vector3& center, float radius, const Color& color, uint32_t rings = 8, uint32_t slices = 8);
	void AddCylinder(const Math::Vector3& center, float height, float radius, const Color& color, uint32_t rings = 8, uint32_t slices = 8);
	void AddCone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color, bool fill);
	void AddGroundPlane(const Math::Vector3& center, const Color& color, uint32_t gridCount, float gridSize = 1);

	void Render(const Camera& camera);
}