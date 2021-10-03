#include "Precompiled.h"
#include "WeaponComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

using namespace SWAGE;

MEMPOOL_DEFINE(WeaponComponent, 1000)

void WeaponComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mColliderComponent = GetOwner().GetComponent<ColliderComponent>();
}

void WeaponComponent::Update(float deltaTime)
{
	if (mTargetTransformComponent)
	{
		Math::Vector3 direction = Math::Normalize(mTargetTransformComponent->GetPosition() - mTransformComponent->GetPosition());
		Math::Vector3 newPos = mTransformComponent->GetPosition() + direction * mMoveSpeed * deltaTime;
	}

	CollidedWithTarget();
}

bool WeaponComponent::CollidedWithTarget()
{
	if (mTargetTransformComponent)
	{
		const ColliderComponent* targetColliderComponent = mTargetTransformComponent->GetOwner().GetComponent<ColliderComponent>();
		return Math::Shapes::Intersect(targetColliderComponent->GetAABB(), mColliderComponent->GetAABB());
	}
	return false;
}
