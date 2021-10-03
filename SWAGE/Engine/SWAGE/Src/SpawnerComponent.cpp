#include "Precompiled.h"
#include "SpawnerComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "TransformComponent.h"

using namespace SWAGE;

MEMPOOL_DEFINE(SpawnerComponent, 1000)

int SpawnerComponent::sNextId = 0;

void SpawnerComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void SpawnerComponent::Update(float deltaTime)
{
	if (mSpawnedCount >= mMaxCount)
		return;

	mTimer += deltaTime;
	if (mTimer >= mSpawnWaitTime)
	{
		for (int i = 0; i < mSpawnCount && mSpawnedCount <= mMaxCount; ++i)
		{
			auto newObject = GetOwner().GetWorld().CreateGameObject(mTemplateFileName, mSpawnObjectName + std::to_string(sNextId++));
			auto newTransform = newObject->GetComponent<TransformComponent>();
			newTransform->SetPosition(mTransformComponent->GetPosition());
			mSpawnedCount++;
		}

		mTimer -= mSpawnWaitTime;
	}
}
