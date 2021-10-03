#pragma once

#include "Component.h"

namespace SWAGE
{
	class TransformComponent;

	class SpawnerComponent final : public Component
	{
		static int sNextId;

	public:
		SET_TYPE_ID(ComponentId::Spawner);
		MEMPOOL_DECLARE;

		SpawnerComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		void SetTemplateFileName(std::string templateFileName) { mTemplateFileName = templateFileName; }
		void SetSpawnObjectName(std::string spawnObjectName) { mSpawnObjectName = spawnObjectName; }
		void SetSpawnCount(int spawnCount) { mSpawnCount = spawnCount; }
		void SetSpawnWaitTime(float spawnWaitTime) { mSpawnWaitTime = spawnWaitTime; }
		void SetMaxCount(int maxCount) { mMaxCount = maxCount; }

	private:
		const TransformComponent* mTransformComponent = nullptr;

		std::string mTemplateFileName;
		std::string mSpawnObjectName;
		int mSpawnCount = 0;
		int mSpawnedCount = 0;
		int mMaxCount = 0;
		float mSpawnWaitTime = 0.0f;
		float mTimer = 0.0f;
	};
}