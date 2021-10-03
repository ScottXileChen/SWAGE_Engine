#pragma once

#include "Camera.h"

namespace SWAGE::Graphics
{
	class ArcBall
	{
	public:
		void Update(const Graphics::Camera& camera);

		void SetPosition(Math::Vector3 pos) { mPosition = pos; }
		void SetRadius(float radius) { mRadius = radius; }

		const Math::Vector3& GetPosition() const { return mPosition; }
		const Math::Quaternion& GetRotation() const { return mRotation; }
		const float GetRadius() const { return mRadius; }

	private:
		Math::Vector3 mDragStartPosition = Math::Vector3::Zero;
		Math::Vector3 mPosition = Math::Vector3::Zero;
		Math::Quaternion mRotation = Math::Quaternion::Identity;
		float mRadius = 0.0f;
		bool mDragging = false;
	};
}