#include "Precompiled.h"

#include "ArcBall.h"
#include "GraphicsSystem.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;
using namespace SWAGE::Math::Shapes;

void ArcBall::Update(const Graphics::Camera & camera)
{
	const auto& inputSystem = InputSystem::Get();
	const auto& graphicsSystem = GraphicsSystem::Get();

	if (!mDragging)
	{
		if (inputSystem->IsMousePressed(MouseButton::LBUTTON))
		{
			float distance;
			Ray ray = camera.ScreenPointToRay(
				inputSystem->GetMouseScreenX()
				, inputSystem->GetMouseScreenY()
				, graphicsSystem->GetBackBufferWidth()
				, graphicsSystem->GetBackBufferHeight());
			if (Intersect(ray, Sphere{ mPosition, mRadius }, distance))
			{
				mDragStartPosition = ray.GetPoint(distance);
				mDragging = true;
			}
		}
	}
	if (inputSystem->IsMouseDown(MouseButton::LBUTTON))
	{
		float distance;
		Ray ray = camera.ScreenPointToRay(
			inputSystem->GetMouseScreenX()
			, inputSystem->GetMouseScreenY()
			, graphicsSystem->GetBackBufferWidth()
			, graphicsSystem->GetBackBufferHeight());

		if (Intersect(ray, Sphere{ mPosition, mRadius }, distance))
		{
			const Vector3 dragPosition = ray.GetPoint(distance);
			if (DistanceSqr(dragPosition, mDragStartPosition) > 0.0f)
			{
				const Vector3 from = Normalize(mDragStartPosition - mPosition);
				const Vector3 to = Normalize(dragPosition - mPosition);
				const Quaternion rotation = Quaternion::RotationFromTo(from, to);
				mRotation = rotation * mRotation;
				mDragStartPosition = dragPosition;
			}
		}
	}
	else
	{
		mDragging = false;
	}
}
