#pragma once

#include "Bone.h"
#include "AnimationClip.h"

namespace SWAGE::Graphics
{
	struct Skeleton
	{
		enum DrawType
		{
			line,
			cone
		};
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};

	void DrawSkeleton(const Skeleton& skeleton, const std::vector<Math::Matrix4>& boneMatrices, Skeleton::DrawType drawType);
	std::vector<SWAGE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, SWAGE::Math::Matrix4 worldMatrix);
	std::vector<SWAGE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton);
	std::vector<SWAGE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, SWAGE::Math::Matrix4 worldMatrix, const AnimationClip& animationClip, float animationTime);
	std::vector<SWAGE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, const AnimationClip& animationClip, float animationTime);
	std::vector<SWAGE::Math::Matrix4> CalculateSkinningMatrices(const Skeleton& skeleton);
	std::vector<SWAGE::Math::Matrix4> CalculateSkinningMatrices(const Skeleton& skeleton, const AnimationClip& animationClip, float animationTime);
	// [a b c 0] (a b c) = right vector (X axis)
	// [d e f 0] (d e f) = up vector (Y axis)
	// [g h i 0] (g h i) = look vector (Z axis)
	// [x y z 0] (x y z) = position
}