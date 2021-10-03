#include "Precompiled.h"
#include "ModelManager.h"

#include "Model.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

namespace
{
	std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
	ASSERT(sModelManager == nullptr, "ModelManager -- Manager already initialized!");
	sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
	if (sModelManager != nullptr)
	{
		sModelManager->Terminate();
		sModelManager.reset();
	}
}

ModelManager* ModelManager::Get()
{
	ASSERT(sModelManager != nullptr, "ModelManager -- No manager registered.");
	return sModelManager.get();
}

void ModelManager::Terminate()
{
	for (auto& entry : mModels)
		entry.model->Terminate();
	mModels.clear();
}

ModelId ModelManager::LoadModel(std::filesystem::path filePath)
{
	auto iter = std::find_if(mModels.begin(), mModels.end(), [&](const auto& entry) {
		return entry.filePath == filePath;
		});
	if (iter != mModels.end())
	{
		return std::distance(mModels.begin(), iter) + 1;
	}
	auto& entry = mModels.emplace_back();
	entry.filePath = filePath;
	entry.model = std::make_unique<Model>();
	entry.model->Initialize(filePath);
	return mModels.size();
}

const Model* ModelManager::GetModel(ModelId id) const
{
	ASSERT(id > 0 && id <= mModels.size(), "ModelManager -- Invalid model id.");
	return mModels[id - 1].model.get();
}