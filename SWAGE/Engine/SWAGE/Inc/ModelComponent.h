#pragma once

#include "Component.h"

namespace SWAGE
{
	class ModelComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Model);
		MEMPOOL_DECLARE;

		ModelComponent() = default;

		void Initialize() override;
		void Terminate() override;

		const Graphics::Model* GetModel() const;

		void SetFileName(const char* fileName) { mFileName = fileName; }

	private:
		std::string mFileName;
		Graphics::ModelId mModelId = 0;
	};
}