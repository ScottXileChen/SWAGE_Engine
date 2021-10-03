#pragma once

#include "Component.h"

namespace SWAGE
{
	class TransformComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Transform);
		MEMPOOL_DECLARE;

		TransformComponent() = default;

		void DebugUI() override;

		void SetPosition(const Math::Vector3& position) { mPosition = position; }
		const Math::Vector3& GetPosition() const { return mPosition; }

		void SetRotation(const Math::Quaternion& rotation) { mRotation = rotation; }
		const Math::Quaternion& GetRotation() const { return mRotation; }

	private:
		Math::Vector3 mPosition;
		Math::Quaternion mRotation;
	};
}
