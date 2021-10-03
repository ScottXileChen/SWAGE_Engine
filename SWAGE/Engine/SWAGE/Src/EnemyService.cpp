#include "Precompiled.h"
#include "EnemyService.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "MinionComponent.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

void EnemyService::Initialize()
{
	
}

void EnemyService::Terminate()
{

}

void EnemyService::Update(float deltaTime)
{
	
}

void EnemyService::Render()
{
	
}

void EnemyService::DebugUI()
{
	
}

void EnemyService::Register(const MinionComponent * minionComponent)
{
	auto& gameObject = minionComponent->GetOwner();
	Entry& entry = mEnemyEntries.emplace_back();
	entry.colliderComponent = gameObject.GetComponent<ColliderComponent>();
	entry.minionComponent = minionComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
}

void EnemyService::Unregister(const MinionComponent * minionComponent)
{
	auto iter = std::find_if(mEnemyEntries.begin(), mEnemyEntries.end(), [&](const auto& entry)
	{
		return (entry.minionComponent == minionComponent);
	});
	if (iter != mEnemyEntries.end())
	{
		mEnemyEntries.erase(iter);
	}
}

const MinionComponent* EnemyService::GetCloestEnemy(const Math::Vector3 position)
{
	float distance = FLT_MAX;
	const MinionComponent* minionComponent = nullptr;
	for (auto& enemy : mEnemyEntries)
	{
		float newDistance = Distance(enemy.transformComponent->GetPosition(), position);
		if (newDistance <= distance)
		{
			minionComponent = enemy.minionComponent;
			distance = newDistance;
		}
	}
	return minionComponent;
}
