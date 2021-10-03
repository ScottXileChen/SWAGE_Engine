#pragma once

#include "Component.h"

namespace SWAGE
{
	class TransformComponent;
	class ColliderComponent;

	class WeaponComponent final : public Component
	{
		static int sNextId;

	public:
		SET_TYPE_ID(ComponentId::Weapon);
		MEMPOOL_DECLARE;

		WeaponComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		void SetTarget(const TransformComponent* targetTransformComponent) { mTargetTransformComponent = targetTransformComponent; }
		void SetMoveSpeed(float moveSpeed) { mMoveSpeed = moveSpeed; }

	private:
		bool CollidedWithTarget();

		const TransformComponent* mTransformComponent = nullptr;
		const ColliderComponent* mColliderComponent = nullptr;

		const TransformComponent* mTargetTransformComponent = nullptr;

		float mMoveSpeed = 0;
	};
}