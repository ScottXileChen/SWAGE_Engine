#pragma once

#include "Component.h"

namespace SWAGE
{
	class AnimatorComponent;
	class TransformComponent;
	class WayPointPathComponent;

	class MinionComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Minion);
		MEMPOOL_DECLARE;

		MinionComponent() = default;

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;

		void SetMoveSpeed(float moveSpeed) { mMoveSpeed = moveSpeed; }

	private:
		AnimatorComponent* mAnimatorComponent = nullptr;
		TransformComponent* mTransformComponent = nullptr;
		const WayPointPathComponent* mWayPointPathComponent = nullptr;

		float mMoveSpeed;
	};
}