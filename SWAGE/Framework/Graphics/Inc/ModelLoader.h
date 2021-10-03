#pragma once

#include "MeshTypes.h"
#include "Model.h"

namespace SWAGE::Graphics
{
	class ModelLoader
	{
	public:
		static void LoadObj(const std::filesystem::path fileName, float scale, MeshPX& mesh);
		static void LoadObj(const std::filesystem::path fileName, float scale, Mesh& mesh);
		static void LoadModel(const std::filesystem::path fileName, Model& model, bool loadBinary = false);
		static void LoadMaterial(std::filesystem::path fileName, Model& model, bool loadBinary = false);
		static bool LoadSkeleton(std::filesystem::path fileName, Model& model, bool loadBinary = false);
		static bool LoadAnimation(std::filesystem::path fileName, Model& model, bool loadBinary = false);
	};
}