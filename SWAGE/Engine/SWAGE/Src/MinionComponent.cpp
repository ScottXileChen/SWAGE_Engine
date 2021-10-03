#include "Precompiled.h"
#include "MinionComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "WayPointPathComponent.h"

#include "EnemyService.h"

using namespace SWAGE;
using namespace SWAGE::Math;

MEMPOOL_DEFINE(MinionComponent, 1000)

void MinionComponent::Initialize()
{
	auto enemyService = GetOwner().GetWorld().GetService<EnemyService>();
	enemyService->Register(this);

	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mWayPointPathComponent = GetOwner().GetComponent<WayPointPathComponent>();
	mAnimatorComponent = GetOwner().GetComponent<AnimatorComponent>();
	mAnimatorComponent->GetAnimator().Play();
	mAnimatorComponent->GetAnimator().SetLooping(true);
}

void MinionComponent::Terminate()
{
	auto enemyService = GetOwner().GetWorld().GetService<EnemyService>();
	enemyService->Unregister(this);
}

void MinionComponent::Update(float deltaTime)
{
	Vector3 direction = Normalize(mWayPointPathComponent->GetWayPoint() - mTransformComponent->GetPosition());
	Vector3 newPos = mTransformComponent->GetPosition() + direction * mMoveSpeed * deltaTime;
	mTransformComponent->SetPosition(newPos);
	mTransformComponent->SetRotation(Quaternion::RotationLook(-direction));
}
