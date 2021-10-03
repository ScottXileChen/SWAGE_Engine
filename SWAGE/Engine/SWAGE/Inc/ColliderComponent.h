#pragma once

#include "Component.h"

namespace SWAGE
{
	class TransformComponent;

	class ColliderComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Collider);
		MEMPOOL_DECLARE;

		ColliderComponent() = default;

		void Initialize() override;
		void DebugUI() override;

		void SetCenter(Math::Vector3 center) { mCenter = center; }
		void SetExtend(Math::Vector3 extend) { mExtend = extend; }

		Math::Shapes::AABB GetAABB() const;

	private:
		const TransformComponent* mTransformComponent = nullptr;
		Math::Vector3 mCenter = Math::Vector3::Zero;
		Math::Vector3 mExtend = Math::Vector3::One;
	};
}
