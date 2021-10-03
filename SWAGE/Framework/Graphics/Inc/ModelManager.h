#pragma once

#include "Model.h"

namespace SWAGE::Graphics
{
	using ModelId = size_t;

	class ModelManager final
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static ModelManager* Get();

	public:
		void Terminate();

		ModelId LoadModel(std::filesystem::path filePath);

		const Model* GetModel(ModelId id) const;

	private:
		struct Entry
		{
			std::filesystem::path filePath;
			std::unique_ptr<Model> model;
		};

		std::vector<Entry> mModels;
	};
}