#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

namespace
{
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color);
		void Render(const Camera& camera);

		uint32_t GetVertexCount() { return mLineVertexCount; }
		uint32_t GetMaxVertexCount() { return mMaxVertexCount; }

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;
		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFillVertices;
		uint32_t mLineVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
		uint32_t mFillVertexCount = 0;
	};

	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		mVertexShader.Initialize("../../Assets/Shaders/DoSimpleDraw.fx", VertexPC::Format);
		mPixelShader.Initialize("../../Assets/Shaders/DoSimpleDraw.fx");
		mConstantBuffer.Initialize(sizeof(Math::Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount, true);
		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFillVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVertexCount = 0;
		mMaxVertexCount = maxVertexCount;
	}

	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}

	void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
	{
		if (mLineVertexCount + 2 <= mMaxVertexCount)
		{
			mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
		}
	}

	void SimpleDrawImpl::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
	{
		if (mFillVertexCount + 3 <= mMaxVertexCount)
		{
			mFillVertices[mFillVertexCount++] = VertexPC{ v0,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v1,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v2,color };
		}
	}

	void SimpleDrawImpl::Render(const Camera& camera)
	{
		auto matView = camera.GetViewMatrix();
		auto matProj = camera.GetProjectionMatrix();
		auto transform = Math::Transpose(matView * matProj);
		mConstantBuffer.Update(&transform);
		mConstantBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixelShader.Bind();

		mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFillVertices.get(), mFillVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		mLineVertexCount = 0;
		mFillVertexCount = 0;
	}

	std::unique_ptr<SimpleDrawImpl> sInstance;
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
{
	sInstance->AddLine(v0, v1, color);
}

void SimpleDraw::AddAABB(const Math::Vector3 & center, const Math::Vector3 & extend, const Color & color)
{
	if (sInstance->GetVertexCount() + 12 > sInstance->GetMaxVertexCount())
	{
		LOG("Cannot draw AABB, because of out of VertexCount!");
		return;
	}

	// Call sInstance->AddLine 12 times here ...
	Math::Vector3 frontBL = { center.x - extend.x, center.y - extend.y, center.z - extend.z };
	Math::Vector3 frontBR = { center.x + extend.x, center.y - extend.y, center.z - extend.z };
	Math::Vector3 frontTL = { center.x - extend.x, center.y + extend.y, center.z - extend.z };
	Math::Vector3 frontTR = { center.x + extend.x, center.y + extend.y, center.z - extend.z };
	Math::Vector3 backBL =  { center.x - extend.x, center.y - extend.y, center.z + extend.z };
	Math::Vector3 backBR =  { center.x + extend.x, center.y - extend.y, center.z + extend.z };
	Math::Vector3 backTL =  { center.x - extend.x, center.y + extend.y, center.z + extend.z };
	Math::Vector3 backTR =  { center.x + extend.x, center.y + extend.y, center.z + extend.z };
	
	sInstance->AddLine(frontTL, frontTR, color);
	sInstance->AddLine(frontBL, frontBR, color);
	sInstance->AddLine(frontTL, frontBL, color);
	sInstance->AddLine(frontTR, frontBR, color);

	sInstance->AddLine(backTL, backTR, color);
	sInstance->AddLine(backBL, backBR, color);
	sInstance->AddLine(backTL, backBL, color);
	sInstance->AddLine(backTR, backBR, color);

	sInstance->AddLine(frontTL, backTL, color);
	sInstance->AddLine(frontTR, backTR, color);
	sInstance->AddLine(frontBL, backBL, color);
	sInstance->AddLine(frontBR, backBR, color);
}

void SimpleDraw::AddSphere(const Math::Vector3 & center, float radius, const Color & color, uint32_t rings, uint32_t slices)
{
	int vertexCountPrepare = (2 * rings - 3) * slices;
	if (sInstance->GetVertexCount() + vertexCountPrepare > sInstance->GetMaxVertexCount())
	{
		LOG("Cannot draw Sphere, because of out of VertexCount!");
		return;
	}

	const float ringStep = Math::Constants::Pi / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	for (uint32_t r = 0; r < rings - 1; ++r)
	{
		const float phi = r * ringStep;
		// Current ring height.
		const float y1 = -cos(phi) * radius;
		// Next ring height.
		const float y2 = -cos((r + 1) * ringStep) * radius;
		// Current ring newRadius.
		const float newRadius = sin(phi) * radius;
		// Next ring newRadius.
		const float newRadius2 = sin((r + 1) * ringStep) * radius;

		for (uint32_t s = 0; s < slices; ++s)
		{
			// Caculate current position.
			const float x1 = -sin(s * sliceStep) * newRadius;
			const float z1 = cos(s * sliceStep) * newRadius;
			// Caculate next slice position.
			const float x2 = -sin((s + 1) * sliceStep) * newRadius;
			const float z2 = cos((s + 1) * sliceStep) * newRadius;
			// Caculate next ring current position.
			const float x3 = -sin(s * sliceStep) * newRadius2;
			const float z3 = cos(s * sliceStep) * newRadius2;

			// Convert positions to vector3.
			const Math::Vector3 v0 = center + Math::Vector3(x1, y1, z1);
			const Math::Vector3 v1 = center + Math::Vector3(x2, y1, z2);
			const Math::Vector3 v2 = center + Math::Vector3(x3, y2, z3);

			// Bottom and Top only need one vertex for each.
			if (r != 0 && r != rings - 1)
			{
				// Line between current position and next slices position.
				sInstance->AddLine(v0, v1, color);
			}
			// Line between current position and next ring current position.
			sInstance->AddLine(v0, v2, color);
		}
	}
}

void SimpleDraw::AddCylinder(const Math::Vector3& center, float height, float radius, const Color & color, uint32_t rings, uint32_t slices)
{
	const float ringStep = height / (rings - 1);
	const float sliceStep = Math::Constants::TwoPi / slices;

	std::vector<Math::Vector3> positions;

	for (uint32_t r = 0; r < rings; ++r)
	{
		const float y = r * ringStep;

		// Add top ring before adding top center ring.
		if (r == rings - 1)
		{
			for (uint32_t s = 0; s <= slices; ++s)
			{
				const float x = -sin(s * sliceStep) * radius;
				const float z = cos(s * sliceStep) * radius;

				positions.push_back({ x,y,z });
			}
		}

		for (uint32_t s = 0; s <= slices; ++s)
		{
			const float x = -sin(s * sliceStep) * radius;
			const float z = cos(s * sliceStep) * radius;

			// Add top center or bottom center or normal ring.
			if (r == 0)
				positions.push_back({ 0.0f, 0.0f ,0.0f });
			else if (r == rings - 1)
				positions.push_back({ 0.0f, y, 0.0f });
			else
				positions.push_back({ x,y,z });
		}

		// Add bottom ring before adding bottom center ring.
		if (r == 0)
		{
			for (uint32_t s = 0; s <= slices; ++s)
			{
				const float x = -sin(s * sliceStep) * radius;
				const float z = cos(s * sliceStep) * radius;

				positions.push_back({ x, y, z });
			}
		}
	}

	for (size_t i = 0; i < positions.size() - 1; i++)
	{
		sInstance->AddLine(positions[i] + center, positions[i + 1] + center, color);
	}
}

void SimpleDraw::AddCone(const Math::Vector3 & base, const Math::Vector3 & direction, float radius, const Color & color, bool fill)
{
	constexpr int sectors = 8;
	auto side = Math::Normalize(Math::Cross(base, direction)) * radius;
	auto angle = 0.0f;
	auto angleStep = Math::Constants::TwoPi / sectors;

	if (fill)
	{
		for (int i = 0; i < sectors; ++i)
		{
			auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
			auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
			auto v0 = Math::TransformNormal(side, matRot0);
			auto v1 = Math::TransformNormal(side, matRot1);
			sInstance->AddFace(base + v0, base + v1, base + direction, color);
			sInstance->AddFace(base + v0, base, base + v1, color);
			angle += angleStep;
		}
	}
	else
	{
		for (int i = 0; i < sectors; ++i)
		{
			auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
			auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
			auto v0 = Math::TransformNormal(side, matRot0);
			auto v1 = Math::TransformNormal(side, matRot1);
			sInstance->AddLine(base + v0, base + direction, color);
			sInstance->AddLine(base + v0, base + v1, color);
			angle += angleStep;
		}
	}
}

void SimpleDraw::AddGroundPlane(const Math::Vector3 & center, const Color & color, uint32_t gridCount, float gridSize)
{
	float len = gridCount * gridSize;
	Math::Vector3 verticalStart = Math::Vector3(center.x - len / 2, center.y, center.z - len / 2);
	Math::Vector3 verticalEnd = Math::Vector3(center.x - len / 2, center.y, center.z + len / 2);
	Math::Vector3 horizontalStart = Math::Vector3(center.x - len / 2, center.y, center.z - len / 2);
	Math::Vector3 horizontalEnd = Math::Vector3(center.x + len / 2, center.y, center.z - len / 2);
	for (uint32_t i = 0; i <= gridCount; i++)
	{
		Math::Vector3 v0 = verticalStart;
		v0.x += i * gridSize;
		Math::Vector3 v1 = verticalEnd;
		v1.x += i * gridSize;
		AddLine(v0, v1, color);

		Math::Vector3 v2 = horizontalStart;
		v2.z += i * gridSize;
		Math::Vector3 v3 = horizontalEnd;
		v3.z += i * gridSize;
		AddLine(v2, v3, color);
	}
}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}