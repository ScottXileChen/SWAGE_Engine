#include "Precompiled.h"
#include "AnimationIO.h"
#include "AnimationBuilder.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void AnimationIO::Write(FILE * file, const SWAGE::Graphics::AnimationClip& clip)
{
	fprintf_s(file, "%s ", clip.name.c_str());
	fprintf_s(file, "%f ", clip.duration);
	fprintf_s(file, "%f ", clip.ticksPerSecond);
	fprintf_s(file, "%d \n", static_cast<int>(clip.boneAnimations.size()));
	for (int i = 0; i < clip.boneAnimations.size(); ++i)
	{
		if (clip.boneAnimations[i])
		{
			fprintf_s(file, "\n%d ", i);
			fprintf_s(file, "%d \n", static_cast<int>(clip.boneAnimations[i].get()->mPositionKeys.size()));
			for (const auto & key : clip.boneAnimations[i].get()->mPositionKeys)
			{
				fprintf_s(file, "%f ", key.key.x);
				fprintf_s(file, "%f ", key.key.y);
				fprintf_s(file, "%f ", key.key.z);
				fprintf_s(file, "%f \n", key.time);
			}
			fprintf_s(file, "%d \n", static_cast<int>(clip.boneAnimations[i].get()->mRotationKeys.size()));
			for (const auto & key : clip.boneAnimations[i].get()->mRotationKeys)
			{
				fprintf_s(file, "%f ", key.key.w);
				fprintf_s(file, "%f ", key.key.x);
				fprintf_s(file, "%f ", key.key.y);
				fprintf_s(file, "%f ", key.key.z);
				fprintf_s(file, "%f \n", key.time);
			}
			fprintf_s(file, "%d \n", static_cast<int>(clip.boneAnimations[i].get()->mScaleKeys.size()));
			for (const auto & key : clip.boneAnimations[i].get()->mScaleKeys)
			{
				fprintf_s(file, "%f ", key.key.x);
				fprintf_s(file, "%f ", key.key.y);
				fprintf_s(file, "%f ", key.key.z);
				fprintf_s(file, "%f \n", key.time);
			}
		}
	}
}

void AnimationIO::Read(FILE * file, SWAGE::Graphics::AnimationClip& clip)
{
	char strBuff[255];
	fscanf_s(file, "%s ", &strBuff, (int)std::size(strBuff));
	clip.name = strBuff;
	fscanf_s(file, "%f ", &clip.duration);
	fscanf_s(file, "%f ", &clip.ticksPerSecond);
	int boneAnimationSize = 0;
	fscanf_s(file, "%d \n", &boneAnimationSize);
	for (int i = 0; i < boneAnimationSize; i++)
	{
		int index;
		fscanf_s(file, "\n%d ", &index);
		if (i != index)
		{
			// If the data is not for the slot we are currently on, add nullptrs
			// until we reach the correct slot.
			while (i < index)
			{
				clip.boneAnimations.emplace_back(nullptr);
				++i;
			}
		}

		auto& boneAnimation = clip.boneAnimations.emplace_back(std::make_unique<Animation>());

		AnimationBuilder builder;

		int positionKeyCount = 0;
		fscanf_s(file, "%d \n", &positionKeyCount);
		for (int j = 0; j < positionKeyCount; j++)
		{
			float x, y, z, time;
			fscanf_s(file, "%f ", &x);
			fscanf_s(file, "%f ", &y);
			fscanf_s(file, "%f ", &z);
			fscanf_s(file, "%f \n", &time);
			time /= clip.ticksPerSecond;
			builder.AddPositionKey({ x,y,z }, time);
		}
		int rotationKeyCount = 0;
		fscanf_s(file, "%d \n", &rotationKeyCount);
		for (int j = 0; j < rotationKeyCount; j++)
		{
			float w, x, y, z, time;
			fscanf_s(file, "%f ", &w);
			fscanf_s(file, "%f ", &x);
			fscanf_s(file, "%f ", &y);
			fscanf_s(file, "%f ", &z);
			fscanf_s(file, "%f \n", &time);
			time /= clip.ticksPerSecond;
			builder.AddRotationKey({ w, x, y, z }, time);
		}
		int scaleKeyCount = 0;
		fscanf_s(file, "%d \n", &scaleKeyCount);
		for (int j = 0; j < scaleKeyCount; j++)
		{
			float x, y, z, time;
			fscanf_s(file, "%f ", &x);
			fscanf_s(file, "%f ", &y);
			fscanf_s(file, "%f ", &z);
			fscanf_s(file, "%f \n", &time);
			time /= clip.ticksPerSecond;
			builder.AddScaleKey({ x,y,z }, time);
		}
		*boneAnimation = builder.Get();
	}
}

void AnimationIO::WriteBinary(FILE * file, const SWAGE::Graphics::AnimationClip& clip)
{
	size_t nameSize = clip.name.size();
	fwrite(&nameSize, sizeof(size_t), 1, file);
	fwrite(clip.name.c_str(), sizeof(char), nameSize, file);
	fwrite(&clip.duration, sizeof(float), 1, file);
	fwrite(&clip.ticksPerSecond, sizeof(float), 1, file);
	size_t boneAnimationCount = clip.boneAnimations.size();
	fwrite(&boneAnimationCount, sizeof(size_t), 1, file);

	for (size_t i = 0; i < boneAnimationCount; ++i)
	{
		if (clip.boneAnimations[i])
		{
			fwrite(&i, sizeof(size_t), 1, file);
			size_t positionKeyCount = clip.boneAnimations[i].get()->mPositionKeys.size();
			fwrite(&positionKeyCount, sizeof(size_t), 1, file);
			for (const auto & key : clip.boneAnimations[i].get()->mPositionKeys)
			{
				fwrite(&key.key, sizeof(SWAGE::Math::Vector3), 1, file);
				fwrite(&key.time, sizeof(float), 1, file);
			}
			size_t rotationKeyCount = clip.boneAnimations[i].get()->mRotationKeys.size();
			fwrite(&rotationKeyCount, sizeof(size_t), 1, file);
			for (const auto & key : clip.boneAnimations[i].get()->mRotationKeys)
			{
				fwrite(&key.key, sizeof(SWAGE::Math::Quaternion), 1, file);
				fwrite(&key.time, sizeof(float), 1, file);
			}
			size_t scaleKeyCount = clip.boneAnimations[i].get()->mScaleKeys.size();
			fwrite(&scaleKeyCount, sizeof(size_t), 1, file);
			for (const auto & key : clip.boneAnimations[i].get()->mScaleKeys)
			{
				fwrite(&key.key, sizeof(SWAGE::Math::Vector3), 1, file);
				fwrite(&key.time, sizeof(float), 1, file);
			}
		}
	}
}

void AnimationIO::ReadBinary(FILE * file, SWAGE::Graphics::AnimationClip& clip)
{
	size_t nameSize = 0;
	fread(&nameSize, sizeof(size_t), 1, file);
	clip.name.resize(nameSize);
	fread(clip.name.data(), sizeof(char), nameSize, file);
	fread(&clip.duration, sizeof(float), 1, file);
	fread(&clip.ticksPerSecond, sizeof(float), 1, file);
	size_t boneAnimationCount = 0;
	fread(&boneAnimationCount, sizeof(size_t), 1, file);

	for (size_t i = 0; i < boneAnimationCount; ++i)
	{
		size_t index = 0;
		fread(&index, sizeof(size_t), 1, file);

		if (i != index)
		{
			// If the data is not for the slot we are currently on, add nullptrs
			// until we reach the correct slot.
			while (i < index)
			{
				clip.boneAnimations.emplace_back(nullptr);
				++i;
			}
		}

		AnimationBuilder builder;
		auto& boneAnimation = clip.boneAnimations.emplace_back(std::make_unique<Animation>());

		size_t positionKeyCount = 0;
		fread(&positionKeyCount, sizeof(size_t), 1, file);
		boneAnimation->mPositionKeys.resize(positionKeyCount);
		for (auto & key : boneAnimation->mPositionKeys)
		{
			SWAGE::Math::Vector3 position = SWAGE::Math::Vector3::Zero;
			float time = 0;
			fread(&position, sizeof(SWAGE::Math::Vector3), 1, file);
			fread(&time, sizeof(float), 1, file);
			time /= clip.ticksPerSecond;
			builder.AddPositionKey(position, time);
		}
		size_t rotationKeyCount = 0;
		fread(&rotationKeyCount, sizeof(size_t), 1, file);
		boneAnimation->mRotationKeys.resize(rotationKeyCount);
		for (auto & key : boneAnimation->mRotationKeys)
		{
			SWAGE::Math::Quaternion rotation = SWAGE::Math::Quaternion::Identity;
			float time = 0;
			fread(&rotation, sizeof(SWAGE::Math::Quaternion), 1, file);
			fread(&time, sizeof(float), 1, file);
			time /= clip.ticksPerSecond;
			builder.AddRotationKey(rotation, time);
		}
		size_t scaleKeyCount = 0;
		fread(&scaleKeyCount, sizeof(size_t), 1, file);
		boneAnimation->mScaleKeys.resize(scaleKeyCount);
		for (auto & key : boneAnimation->mScaleKeys)
		{
			SWAGE::Math::Vector3 scale = SWAGE::Math::Vector3::Zero;
			float time = 0;
			fread(&scale, sizeof(SWAGE::Math::Vector3), 1, file);
			fread(&time, sizeof(float), 1, file);
			time /= clip.ticksPerSecond;
			builder.AddScaleKey(scale, time);
		}
		*boneAnimation = builder.Get();
	}
}
