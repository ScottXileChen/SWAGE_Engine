#pragma once

#include "Component.h"

namespace SWAGE
{
	class TransformComponent;

	class WayPointPathComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::WayPointPath);
		MEMPOOL_DECLARE;

		WayPointPathComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		void SetWayPointPath(std::vector<SWAGE::Math::Vector3> path) { mWayPointPath = path; }
		const SWAGE::Math::Vector3 GetWayPoint() const { return mWayPointPath[mTempIndex]; }

	private:
		const TransformComponent* mTransformComponent = nullptr;

		std::vector<SWAGE::Math::Vector3> mWayPointPath;

		float mLastDistance;
		int mTempIndex;
	};
}