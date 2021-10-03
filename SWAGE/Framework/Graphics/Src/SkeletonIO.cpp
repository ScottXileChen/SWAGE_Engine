#include "Precompiled.h"
#include "SkeletonIO.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void SkeletonIO::Write(FILE * file, const Skeleton & skeleton)
{
	const auto& bones = skeleton.bones;
	const int boneCount = static_cast<int>(bones.size());
	fprintf_s(file, "%d\n", boneCount);

	const int rootIndex = skeleton.root->index;
	fprintf_s(file, "%d\n", rootIndex);

	for (size_t i = 0; i < bones.size(); ++i)
	{
		fprintf_s(file, "%s ", bones[i]->name.c_str());
		fprintf_s(file, "%d ", bones[i]->index);
		fprintf_s(file, "%d ", bones[i]->parentIndex);

		const auto& childIndices = bones[i]->childIndices;
		const int childIndicesCount = static_cast<int>(childIndices.size());
		fprintf_s(file, "%d ", childIndicesCount);
		for (const auto& index : childIndices)
			fprintf_s(file, "%d ", index);

		fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f "
			, bones[i]->toParentTransform._11, bones[i]->toParentTransform._12, bones[i]->toParentTransform._13, bones[i]->toParentTransform._14
			, bones[i]->toParentTransform._21, bones[i]->toParentTransform._22, bones[i]->toParentTransform._23, bones[i]->toParentTransform._24
			, bones[i]->toParentTransform._31, bones[i]->toParentTransform._32, bones[i]->toParentTransform._33, bones[i]->toParentTransform._34
			, bones[i]->toParentTransform._41, bones[i]->toParentTransform._42, bones[i]->toParentTransform._43, bones[i]->toParentTransform._44);

		fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, bones[i]->offsetTransform._11, bones[i]->offsetTransform._12, bones[i]->offsetTransform._13, bones[i]->offsetTransform._14
			, bones[i]->offsetTransform._21, bones[i]->offsetTransform._22, bones[i]->offsetTransform._23, bones[i]->offsetTransform._24
			, bones[i]->offsetTransform._31, bones[i]->offsetTransform._32, bones[i]->offsetTransform._33, bones[i]->offsetTransform._34
			, bones[i]->offsetTransform._41, bones[i]->offsetTransform._42, bones[i]->offsetTransform._43, bones[i]->offsetTransform._44);
	}
}

void SkeletonIO::Read(FILE * file, Skeleton & skeleton)
{
	int boneCount = 0;
	fscanf_s(file, "%d ", &boneCount);

	int rootIndex = 0;
	fscanf_s(file, "%d ", &rootIndex);

	char strBuff[255];
	skeleton.bones.reserve(boneCount);

	for (int i = 0; i < boneCount; ++i)
	{
		auto& bone = skeleton.bones.emplace_back(std::make_unique<Bone>());
		fscanf_s(file, "%s ", &strBuff, (int)std::size(strBuff));
		bone->name = strBuff;
		fscanf_s(file, "%d ", &bone->index);
		fscanf_s(file, "%d ", &bone->parentIndex);

		int childIndicesCount = 0;
		fscanf_s(file, "%d ", &childIndicesCount);
		auto& childIndices = bone->childIndices;
		childIndices.resize(childIndicesCount);

		for (size_t j = 0; j < childIndices.size(); ++j)
			fscanf_s(file, "%d ", &childIndices[j]);

		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f "
			, &bone->toParentTransform._11, &bone->toParentTransform._12, &bone->toParentTransform._13, &bone->toParentTransform._14
			, &bone->toParentTransform._21, &bone->toParentTransform._22, &bone->toParentTransform._23, &bone->toParentTransform._24
			, &bone->toParentTransform._31, &bone->toParentTransform._32, &bone->toParentTransform._33, &bone->toParentTransform._34
			, &bone->toParentTransform._41, &bone->toParentTransform._42, &bone->toParentTransform._43, &bone->toParentTransform._44);

		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, &bone->offsetTransform._11, &bone->offsetTransform._12, &bone->offsetTransform._13, &bone->offsetTransform._14
			, &bone->offsetTransform._21, &bone->offsetTransform._22, &bone->offsetTransform._23, &bone->offsetTransform._24
			, &bone->offsetTransform._31, &bone->offsetTransform._32, &bone->offsetTransform._33, &bone->offsetTransform._34
			, &bone->offsetTransform._41, &bone->offsetTransform._42, &bone->offsetTransform._43, &bone->offsetTransform._44);
	}

	skeleton.root = skeleton.bones[rootIndex].get();
}

void SkeletonIO::WriteBinary(FILE * file, const Skeleton & skeleton)
{
	const auto& bones = skeleton.bones;
	const int boneCount = static_cast<int>(bones.size());
	fwrite(&boneCount, sizeof(int), 1, file);
	const int rootIndex = skeleton.root->index;
	fwrite(&rootIndex, sizeof(int), 1, file);
	for (int i = 0; i < boneCount; ++i)
	{
		size_t nameSize = skeleton.bones[i]->name.size();
		fwrite(&nameSize, sizeof(size_t), 1, file);
		fwrite(skeleton.bones[i]->name.c_str(), sizeof(char), nameSize, file);
		fwrite(&skeleton.bones[i]->index, sizeof(int), 1, file);
		fwrite(&skeleton.bones[i]->parentIndex, sizeof(int), 1, file);
		size_t childCount = skeleton.bones[i]->childIndices.size();
		fwrite(&childCount, sizeof(size_t), 1, file);
		for (size_t j = 0; j < childCount; j++)
			fwrite(&skeleton.bones[i]->childIndices[j], sizeof(int), 1, file);
		fwrite(&skeleton.bones[i]->toParentTransform, sizeof(SWAGE::Math::Matrix4), 1, file);
		fwrite(&skeleton.bones[i]->offsetTransform, sizeof(SWAGE::Math::Matrix4), 1, file);
	}
}

void SkeletonIO::ReadBinary(FILE * file, Skeleton & skeleton)
{
	int boneCount = 0;
	fread(&boneCount, sizeof(int), 1, file);
	int rootIndex = 0;
	fread(&rootIndex, sizeof(int), 1, file);
	for (int i = 0; i < boneCount; i++)
	{
		auto& bone = skeleton.bones.emplace_back(std::make_unique<Bone>());
		size_t nameSize = 0;
		fread(&nameSize, sizeof(size_t), 1, file);
		bone->name.resize(nameSize);
		fread(bone->name.data(), sizeof(char), nameSize, file);
		fread(&bone->index, sizeof(int), 1, file);
		fread(&bone->parentIndex, sizeof(int), 1, file);
		size_t childCount = 0;
		fread(&childCount, sizeof(size_t), 1, file);
		bone->childIndices.resize(childCount);
		for (size_t j = 0; j < childCount; j++)
			fread(&bone->childIndices[j], sizeof(int), 1, file);
		fread(&bone->toParentTransform, sizeof(SWAGE::Math::Matrix4), 1, file);
		fread(&bone->offsetTransform, sizeof(SWAGE::Math::Matrix4), 1, file);
	}

	skeleton.root = skeleton.bones[rootIndex].get();
}
