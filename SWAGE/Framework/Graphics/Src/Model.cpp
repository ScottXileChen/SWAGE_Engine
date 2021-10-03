#include "Precompiled.h"
#include "Model.h"
#include "ModelLoader.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void Model::Initialize(const std::filesystem::path & fileName, bool loadBinary)
{
	// This is the opposite of SaveModel in ModelImporter
	ModelLoader::LoadModel(fileName, *this, loadBinary);

	// Initialize meshBuffers
	for (const auto& mesh : meshData)
		mesh->meshBuffer.Initialize(mesh->mesh);

	// Load Textures
	ModelLoader::LoadMaterial(fileName, *this, loadBinary);

	const std::string parentPath = fileName.parent_path().generic_string();

	// Initialize Textures
	for (auto& data : materialData)
	{
		data.diffuseMap = std::make_unique<Texture>();
		if (!data.diffuseMapName.empty())
			data.diffuseMap->Initialize(parentPath + "/" + data.diffuseMapName.c_str());

		data.specularMap = std::make_unique<Texture>();
		if (!data.specularMapName.empty())
			data.specularMap->Initialize(parentPath + "/" + data.specularMapName.c_str());

		data.normalMap = std::make_unique<Texture>();
		if (!data.normalMapName.empty())
			data.normalMap->Initialize(parentPath + "/" + data.normalMapName.c_str());
	}

	// Load Skeleton
	if (ModelLoader::LoadSkeleton(fileName, *this, loadBinary))
	{
		// Relink all the bones to form the skeleton again ...
		for (auto& bone : skeleton->bones)
		{
			if (bone.get() != skeleton->root)
				bone->parent = skeleton->bones[bone->parentIndex].get();

			for (auto& childIndex : bone->childIndices)
				bone->children.push_back(skeleton->bones[childIndex].get());
		}
	}

	// Load Animation
	ModelLoader::LoadAnimation(fileName, *this, loadBinary);
}

void Model::Terminate()
{
	for (const auto& mesh : meshData)
		mesh->meshBuffer.Terminate();

	for (auto& data : materialData)
	{
		data.diffuseMap->Terminate();
		data.specularMap->Terminate();
		data.normalMap->Terminate();
	}
}

void Model::SetAnimationLooping(bool looping)
{
	ASSERT(!animSet.empty(), "Animation Set is empty!!!");
	for (auto& clip : animSet)
	{
		for (auto& anim : clip.get()->boneAnimations)
		{
			if (anim)
			{
				anim->SetLooping(looping);
			}
		}
	}
}
