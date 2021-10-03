#pragma once

#include "MeshTypes.h"

namespace SWAGE::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC();
		static MeshPX CreateCubePX();
		static MeshPCX CreateCubePCX(Color color);

		static MeshPX CreatePlanePX(uint32_t rows, uint32_t columns, float spacing);
		static MeshPNX CreatePlanePNX(uint32_t rows, uint32_t columns, float spacing);
		static Mesh CreatePlane(uint32_t rows, uint32_t columns, float spacing);

		static MeshPX CreateCylinderPX(uint32_t rings, uint32_t slices, float height, float radius);

		static MeshPX CreateSpherePX(uint32_t rings, uint32_t slices, float radius);
		static MeshPN CreateSpherePN(uint32_t rings, uint32_t slices, float radius);
		static MeshPCX CreateSpherePCX(uint32_t rings, uint32_t slices, Color color, float radius);
		static MeshPNX CreateSpherePNX(uint32_t rings, uint32_t slices, float radius);
		static Mesh CreateSphere(uint32_t rings, uint32_t slices, float radius);

		static MeshPX CreateSkybox(float size);
		static MeshPX CreateSkybox(float size, bool isCliparts);
		static MeshPX CreateFire();
	};
}