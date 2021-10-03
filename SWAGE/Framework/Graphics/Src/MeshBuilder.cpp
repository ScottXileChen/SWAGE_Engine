#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Math;

MeshPC MeshBuilder::CreateCubePC()
{
	MeshPC mesh;

	mesh.vertices.push_back({ Vector3{ -1.0f,  1.0f, -1.0f }, Colors::Red });
	mesh.vertices.push_back({ Vector3{  1.0f,  1.0f, -1.0f }, Colors::Red });
	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, -1.0f }, Colors::Red });
	mesh.vertices.push_back({ Vector3{  1.0f, -1.0f, -1.0f }, Colors::Red });

	mesh.vertices.push_back({ Vector3{  1.0f, -1.0f, 1.0f }, Colors::Blue });
	mesh.vertices.push_back({ Vector3{  1.0f,  1.0f, 1.0f }, Colors::Blue });
	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, 1.0f }, Colors::Blue });
	mesh.vertices.push_back({ Vector3{ -1.0f,  1.0f, 1.0f }, Colors::Blue });

	mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(2);
	mesh.indices.push_back(2); mesh.indices.push_back(1); mesh.indices.push_back(3);
	mesh.indices.push_back(1); mesh.indices.push_back(4); mesh.indices.push_back(3);
	mesh.indices.push_back(1); mesh.indices.push_back(5); mesh.indices.push_back(4);
	mesh.indices.push_back(5); mesh.indices.push_back(7); mesh.indices.push_back(6);
	mesh.indices.push_back(4); mesh.indices.push_back(5); mesh.indices.push_back(6);
	mesh.indices.push_back(6); mesh.indices.push_back(7); mesh.indices.push_back(0);
	mesh.indices.push_back(6); mesh.indices.push_back(0); mesh.indices.push_back(2);
	mesh.indices.push_back(0); mesh.indices.push_back(7); mesh.indices.push_back(5);
	mesh.indices.push_back(0); mesh.indices.push_back(5); mesh.indices.push_back(1);
	mesh.indices.push_back(2); mesh.indices.push_back(3); mesh.indices.push_back(6);
	mesh.indices.push_back(6); mesh.indices.push_back(3); mesh.indices.push_back(4);

	return mesh;
}

MeshPX MeshBuilder::CreateCubePX()
{
	MeshPX mesh;

	// Front
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f, -0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f, -0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f, -0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f, -0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(2);
	mesh.indices.push_back(0); mesh.indices.push_back(2); mesh.indices.push_back(3);

	// Left
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f,  0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f,  0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f, -0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f, -0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(4); mesh.indices.push_back(5); mesh.indices.push_back(6);
	mesh.indices.push_back(4); mesh.indices.push_back(6); mesh.indices.push_back(7);

	// Right
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f, -0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f, -0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f,  0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f,  0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(8); mesh.indices.push_back(9); mesh.indices.push_back(10);
	mesh.indices.push_back(8); mesh.indices.push_back(10); mesh.indices.push_back(11);

	// Back
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f,  0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f,  0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f,  0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f,  0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(12); mesh.indices.push_back(13); mesh.indices.push_back(14);
	mesh.indices.push_back(12); mesh.indices.push_back(14); mesh.indices.push_back(15);

	// Top
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f, -0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f,  0.5f,  0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f,  0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f,  0.5f, -0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(16); mesh.indices.push_back(17); mesh.indices.push_back(18);
	mesh.indices.push_back(16); mesh.indices.push_back(18); mesh.indices.push_back(19);

	// Bottom
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f,  0.5f }, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{ -0.5f, -0.5f, -0.5f }, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f, -0.5f }, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPX{ Vector3{  0.5f, -0.5f,  0.5f }, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(20); mesh.indices.push_back(21); mesh.indices.push_back(22);
	mesh.indices.push_back(20); mesh.indices.push_back(22); mesh.indices.push_back(23);

	return mesh;
}

MeshPCX MeshBuilder::CreateCubePCX(Color color)
{
	MeshPCX mesh;

	// Front
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f, -0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f, -0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f, -0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f, -0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(2);
	mesh.indices.push_back(0); mesh.indices.push_back(2); mesh.indices.push_back(3);

	// Left
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f,  0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f,  0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f, -0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f, -0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(4); mesh.indices.push_back(5); mesh.indices.push_back(6);
	mesh.indices.push_back(4); mesh.indices.push_back(6); mesh.indices.push_back(7);

	// Right
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f, -0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f, -0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f,  0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f,  0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(8); mesh.indices.push_back(9); mesh.indices.push_back(10);
	mesh.indices.push_back(8); mesh.indices.push_back(10); mesh.indices.push_back(11);

	// Back
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f,  0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f,  0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f,  0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f,  0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(12); mesh.indices.push_back(13); mesh.indices.push_back(14);
	mesh.indices.push_back(12); mesh.indices.push_back(14); mesh.indices.push_back(15);

	// Top
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f, -0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f,  0.5f,  0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f,  0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f,  0.5f, -0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(16); mesh.indices.push_back(17); mesh.indices.push_back(18);
	mesh.indices.push_back(16); mesh.indices.push_back(18); mesh.indices.push_back(19);

	// Bottom
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f,  0.5f }, color, Vector2{0.0f,1.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{ -0.5f, -0.5f, -0.5f }, color, Vector2{0.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f, -0.5f }, color, Vector2{1.0f,0.0f} });
	mesh.vertices.push_back(VertexPCX{ Vector3{  0.5f, -0.5f,  0.5f }, color, Vector2{1.0f,1.0f} });

	mesh.indices.push_back(20); mesh.indices.push_back(21); mesh.indices.push_back(22);
	mesh.indices.push_back(20); mesh.indices.push_back(22); mesh.indices.push_back(23);

	return mesh;
}

MeshPX MeshBuilder::CreatePlanePX(uint32_t rows, uint32_t columns, float spacing) // Facing positive Y
{
	MeshPX mesh;

	const float uPercentage = 1.0f / (columns - 1);
	const float vPercentage = 1.0f / (rows - 1);

	const float xOffset = (columns - 1) * spacing * 0.5f;
	const float zOffset = (rows - 1) * spacing * 0.5f;

	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			int index = x + z * columns;
			mesh.vertices.push_back(VertexPX{ Vector3{ x * spacing - xOffset, 0.0f, z * spacing - zOffset}, Vector2{ uPercentage * x, 1 - vPercentage * z} });

			if (z != 0 && x != 0)
			{
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index - 1); mesh.indices.push_back(index);
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index); mesh.indices.push_back(index - columns);
			}
		}
	}

	return mesh;
}

MeshPNX MeshBuilder::CreatePlanePNX(uint32_t rows, uint32_t columns, float spacing)
{
	MeshPNX mesh;

	const float uPercentage = 1.0f / (columns - 1);
	const float vPercentage = 1.0f / (rows - 1);

	const float xOffset = (columns - 1) * spacing * 0.5f;
	const float zOffset = (rows - 1) * spacing * 0.5f;

	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			int index = x + z * columns;
			mesh.vertices.push_back(VertexPNX{ Vector3{ x * spacing - xOffset, 0.0f, z * spacing - zOffset}, Math::Normalize({ x * spacing - xOffset, 0.0f, z * spacing - zOffset}), Vector2{ uPercentage * x, 1 - vPercentage * z} });

			if (z != 0 && x != 0)
			{
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index - 1); mesh.indices.push_back(index);
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index); mesh.indices.push_back(index - columns);
			}
		}
	}

	return mesh;
}

Mesh MeshBuilder::CreatePlane(uint32_t rows, uint32_t columns, float spacing)
{
	Mesh mesh;

	const float uPercentage = 1.0f / (columns - 1);
	const float vPercentage = 1.0f / (rows - 1);

	const float xOffset = (columns - 1) * spacing * 0.5f;
	const float zOffset = (rows - 1) * spacing * 0.5f;

	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			int index = x + z * columns;
			mesh.vertices.push_back(Vertex{
				Vector3{ x * spacing - xOffset, 0.0f, z * spacing - zOffset},
				Math::Normalize(Vector3{ x * spacing - xOffset, 0.0f, z * spacing - zOffset}),
				Math::Normalize({ -(z * spacing - zOffset), 0.0f, x * spacing - xOffset }),
				Vector2{ uPercentage * x, 1 - vPercentage * z},
				});

			if (z != 0 && x != 0)
			{
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index - 1); mesh.indices.push_back(index);
				mesh.indices.push_back(index - columns - 1); mesh.indices.push_back(index); mesh.indices.push_back(index - columns);
			}
		}
	}

	return mesh;
}

MeshPX MeshBuilder::CreateCylinderPX(uint32_t rings, uint32_t slices, float height, float radius)
{
	MeshPX mesh;

	const float ringStep = height / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	const float uPercentage = 1.0f / slices;
	const float vPercentage = 1.0f / (rings - 1);

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float y = r * ringStep;
		const float v = 1.0f - r * vPercentage;

		// Add top ring before adding top center ring.
		if (r == rings - 1)
		{
			for (uint32_t s = 0; s <= slices; ++s)
			{
				const float x = -sin(s * sliceStep) * radius;
				const float z = cos(s * sliceStep) * radius;
				const float u = s * uPercentage;

				mesh.vertices.push_back({ {x,y,z},{ u, v } });
			}
		}

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * radius;
			const float z = cos(s * sliceStep) * radius;
			const float u = s * uPercentage;

			// Add top center or bottom center or normal ring.
			if (r == 0)
				mesh.vertices.push_back({ {0.0f, 0.0f ,0.0f},{ u, 1.0f - (r + 1) * vPercentage } });
			else if (r == rings - 1)
				mesh.vertices.push_back({ {0.0f, y, 0.0f},{ u, v} });
			else
				mesh.vertices.push_back({ {x,y,z},{ u, v } });
		}

		// Add bottom ring before adding bottom center ring.
		if (r == 0)
		{
			for (uint32_t s = 0; s <= slices; ++s)
			{
				const float x = -sin(s * sliceStep) * radius;
				const float z = cos(s * sliceStep) * radius;
				const float u = s * uPercentage;

				mesh.vertices.push_back({ {x, y, z},{ u, v } });
			}
		}
	}

	// rings + 2 because we have top center and bottom center ring right now.
	for (uint32_t r = 0; r + 1 < rings + 2; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(uint32_t rings, uint32_t slices, float radius)
{
	MeshPX mesh;

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	const float uPercentage = 1.0f / slices;
	const float vPercentage = 1.0f / (rings - 1);

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float phi = r * ringStep;
		const float y = -cos(phi) * radius;
		const float newRadius = sin(phi) * radius;
		const float v = 1.0f - r * vPercentage;

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * newRadius;
			const float z = cos(s * sliceStep) * newRadius;
			const float u = s * uPercentage;

			mesh.vertices.push_back({ {x,y,z},{ u, v } });
		}
	}

	for (uint32_t r = 0; r + 1 < rings; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

MeshPN MeshBuilder::CreateSpherePN(uint32_t rings, uint32_t slices, float radius)
{
	MeshPN mesh;

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float phi = r * ringStep;
		const float y = -cos(phi) * radius;
		const float newRadius = sin(phi) * radius;

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * newRadius;
			const float z = cos(s * sliceStep) * newRadius;

			mesh.vertices.push_back({ {x,y,z}, Math::Normalize({x,y,z}) });
		}
	}

	for (uint32_t r = 0; r + 1 < rings; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

MeshPCX MeshBuilder::CreateSpherePCX(uint32_t rings, uint32_t slices, Color color, float radius)
{
	MeshPCX mesh;

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	const float uPercentage = 1.0f / slices;
	const float vPercentage = 1.0f / (rings - 1);

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float phi = r * ringStep;
		const float y = -cos(phi) * radius;
		const float newRadius = sin(phi) * radius;
		const float v = 1.0f - r * vPercentage;

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * newRadius;
			const float z = cos(s * sliceStep) * newRadius;
			const float u = s * uPercentage;

			mesh.vertices.push_back
			({
				{x,y,z}								// position
				, color								// Color
				, { u, v }							// uv
				});
		}
	}

	for (uint32_t r = 0; r + 1 < rings; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

MeshPNX MeshBuilder::CreateSpherePNX(uint32_t rings, uint32_t slices, float radius)
{
	MeshPNX mesh;

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	const float uPercentage = 1.0f / slices;
	const float vPercentage = 1.0f / (rings - 1);

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float phi = r * ringStep;
		const float y = -cos(phi) * radius;
		const float newRadius = sin(phi) * radius;
		const float v = 1.0f - r * vPercentage;

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * newRadius;
			const float z = cos(s * sliceStep) * newRadius;
			const float u = s * uPercentage;

			mesh.vertices.push_back
			({
				{x,y,z}								// position
				, Math::Normalize({x,y,z})			// normal
				, { u, v }							// uv
				});
		}
	}

	for (uint32_t r = 0; r + 1 < rings; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

Mesh SWAGE::Graphics::MeshBuilder::CreateSphere(uint32_t rings, uint32_t slices, float radius)
{
	Mesh mesh;

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	const float uPercentage = 1.0f / slices;
	const float vPercentage = 1.0f / (rings - 1);

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float phi = r * ringStep;
		const float y = -cos(phi) * radius;
		const float newRadius = sin(phi) * radius;
		const float v = 1.0f - r * vPercentage;

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * newRadius;
			const float z = cos(s * sliceStep) * newRadius;
			const float u = s * uPercentage;

			mesh.vertices.push_back
			({
				{x,y,z}								// position
				, Math::Normalize({x,y,z})			// normal
				, Math::Normalize({-z, 0.0f, x})	// tangent
				, { u, v }							// uv
			});
		}
	}

	for (uint32_t r = 0; r + 1 < rings; ++r)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSkybox(float size)
{
	return CreateSkybox(size, false);
}

MeshPX MeshBuilder::CreateSkybox(float size, bool isCliparts)
{
	MeshPX mesh;

	if (isCliparts)
	{
		const VertexPX vertices[] =
		{
			// -z
			{{-size, -size, -size}, {0.999f, 0.665f}},
			{{-size, +size, -size}, {0.999f, 0.334f}},
			{{+size, +size, -size}, {0.75f,  0.334f}},
			{{+size, -size, -size}, {0.75f,  0.665f}},

			// +z
			{{+size, -size, +size}, {0.5f,  0.665f}},
			{{+size, +size, +size}, {0.5f,  0.334f}},
			{{-size, +size, +size}, {0.25f, 0.334f}},
			{{-size, -size, +size}, {0.25f, 0.665f}},

			// -x
			{{-size, -size, +size}, {0.25f,  0.665f}},
			{{-size, +size, +size}, {0.25f,  0.334f}},
			{{-size, +size, -size}, {0.001f, 0.334f}},
			{{-size, -size, -size}, {0.001f, 0.665f}},

			// +x
			{{+size, -size, -size}, {0.75f, 0.665f}},
			{{+size, +size, -size}, {0.75f, 0.334f}},
			{{+size, +size, +size}, {0.5f, 0.334f}},
			{{+size, -size, +size}, {0.5f, 0.665f}},

			// -y
			{{-size, -size, +size}, {0.251f, 0.66f}},
			{{-size, -size, -size}, {0.251f, 0.999f}},
			{{+size, -size, -size}, {0.499f, 0.999f}},
			{{+size, -size, +size}, {0.499f, 0.66f}},

			// +y
			{{-size, +size, -size}, {0.251f, 0.001f}},
			{{-size, +size, +size}, {0.251f, 0.333f}},
			{{+size, +size, +size}, {0.499f, 0.333f}},
			{{+size, +size, -size}, {0.499f, 0.001f}}
		};

		constexpr uint32_t indices[] =
		{
			0,  2,  1,  0,  3,  2,
			4,  6,  5,  4,  7,  6,
			8,  10, 9,  8,  11, 10,
			12, 14, 13, 12, 15, 14,
			16, 18, 17, 16, 19, 18,
			20, 22, 21, 20, 23, 22
		};

		mesh.vertices.insert(mesh.vertices.end(), std::begin(vertices), std::end(vertices));
		mesh.indices.insert(mesh.indices.end(), std::begin(indices), std::end(indices));
	}
	else
	{
		const VertexPX vertices[] =
		{
			// -z
			{{-size, -size, -size}, {0.0f, 1.0f}},
			{{-size, +size, -size}, {0.0f, 0.0f}},
			{{+size, +size, -size}, {1.0f, 0.0f}},
			{{+size, -size, -size}, {1.0f, 1.0f}},

			// +z
			{{+size, -size, +size}, {0.0f, 1.0f}},
			{{+size, +size, +size}, {0.0f, 0.0f}},
			{{-size, +size, +size}, {1.0f, 0.0f}},
			{{-size, -size, +size}, {1.0f, 1.0f}},

			// -x
			{{-size, -size, +size}, {0.0f, 1.0f}},
			{{-size, +size, +size}, {0.0f, 0.0f}},
			{{-size, +size, -size}, {1.0f, 0.0f}},
			{{-size, -size, -size}, {1.0f, 1.0f}},

			// +x
			{{+size, -size, -size}, {0.0f, 1.0f}},
			{{+size, +size, -size}, {0.0f, 0.0f}},
			{{+size, +size, +size}, {1.0f, 0.0f}},
			{{+size, -size, +size}, {1.0f, 1.0f}},

			// -y
			{{-size, -size, +size}, {0.0f, 1.0f}},
			{{-size, -size, -size}, {0.0f, 0.0f}},
			{{+size, -size, -size}, {1.0f, 0.0f}},
			{{+size, -size, +size}, {1.0f, 1.0f}},

			// +y
			{{-size, +size, -size}, {0.0f, 1.0f}},
			{{-size, +size, +size}, {0.0f, 0.0f}},
			{{+size, +size, +size}, {1.0f, 0.0f}},
			{{+size, +size, -size}, {1.0f, 1.0f}}
		};

		constexpr uint32_t indices[] =
		{
			0,  2,  1,  0,  3,  2,
			4,  6,  5,  4,  7,  6,
			8,  10, 9,  8,  11, 10,
			12, 14, 13, 12, 15, 14,
			16, 18, 17, 16, 19, 18,
			20, 22, 21, 20, 23, 22
		};

		mesh.vertices.insert(mesh.vertices.end(), std::begin(vertices), std::end(vertices));
		mesh.indices.insert(mesh.indices.end(), std::begin(indices), std::end(indices));
	}

	ASSERT(!mesh.vertices.empty() && !mesh.indices.empty(), "Failed to create a skybox mesh!");
	return mesh;
}

MeshPX SWAGE::Graphics::MeshBuilder::CreateFire()
{
	MeshPX mesh;

	mesh.vertices.push_back({ Vector3{ -1.0f,  1.0f, 0.0f }, Vector2{ 0.0f, 0.0f } });
	mesh.vertices.push_back({ Vector3{  1.0f,  1.0f, 0.0f }, Vector2{ 1.0f, 0.0f } });
	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, 0.0f }, Vector2{ 0.0f, 1.0f } });
	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, 0.0f }, Vector2{ 0.0f, 1.0f } });
	mesh.vertices.push_back({ Vector3{  1.0f,  1.0f, 0.0f }, Vector2{ 1.0f, 0.0f } });
	mesh.vertices.push_back({ Vector3{  1.0f, -1.0f, 0.0f }, Vector2{ 1.0f, 1.0f } });

	mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(2);
	mesh.indices.push_back(3); mesh.indices.push_back(4); mesh.indices.push_back(5);

	return mesh;
}
