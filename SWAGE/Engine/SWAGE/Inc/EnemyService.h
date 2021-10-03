#pragma once

#include "Service.h"

namespace SWAGE
{
	class MinionComponent;
	class ColliderComponent;
	class TransformComponent;

	class EnemyService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Enemy);

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void Register(const MinionComponent* modelComponent);
		void Unregister(const MinionComponent* modelComponent);

		const MinionComponent* GetCloestEnemy(const Math::Vector3 position);
	private:
		struct Entry
		{
			const MinionComponent* minionComponent = nullptr;
			const ColliderComponent* colliderComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
		};

		std::vector<Entry> mEnemyEntries;
	};
}
