#include "Precompiled.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

using namespace SWAGE;

MEMPOOL_DEFINE(ColliderComponent, 1000)

void ColliderComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void ColliderComponent::DebugUI()
{
	const auto aabb = GetAABB();
	Graphics::SimpleDraw::AddAABB(aabb.center, aabb.extend, Graphics::Colors::Yellow);
}

Math::Shapes::AABB ColliderComponent::GetAABB() const
{
	Math::Shapes::AABB aabb;
	aabb.center = mTransformComponent->GetPosition() + mCenter;
	aabb.extend = mExtend;
	return aabb;
}
