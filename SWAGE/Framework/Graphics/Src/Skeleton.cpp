#include "Precompiled.h"
#include "Skeleton.h"

#include "SimpleDraw.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

namespace
{
	void DrawSkeletonConeShapes(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices)
	{
		auto treeDepth = [](const Bone* bone) -> float
		{
			auto treeDepthRecursive = [](auto func, const Bone* bone) -> float
			{
				float maxDepth = 0.0f;
				for (auto child : bone->children)
				{
					float childDepth = func(func, child);
					if (childDepth > maxDepth)
						maxDepth = childDepth;
				}
				return maxDepth + 1.0f;
			};
			return treeDepthRecursive(treeDepthRecursive, bone);
		};

		const float maxDepth = treeDepth(skeleton.root);
		auto drawBone = [&boneMatrices, maxDepth](const Bone* bone) -> void
		{
			auto drawBoneRecursive = [&boneMatrices](auto func, const Bone* bone, float depth, float maxDepth) -> void
			{
				if (bone->parent)
				{
					auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
					auto to = Math::GetTranslation(boneMatrices[bone->index]);
					auto p = (depth / maxDepth);
					Color color{ 1.0f - p, 0.5f * p, p ,1.0f };
					SimpleDraw::AddCone(from, to - from, 0.025f, color, true);
				}

				for (auto child : bone->children)
					func(func, child, depth + 1.0f, maxDepth);
			};
			drawBoneRecursive(drawBoneRecursive, bone, 1.0f, maxDepth);
		};

		drawBone(skeleton.root);
	}

	void DrawBone(const Skeleton& skeleton, Bone* bone, const std::vector<Math::Matrix4>& boneMatrices)
	{
		if (bone->parent)
		{
			auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
			auto to = Math::GetTranslation(boneMatrices[bone->index]);
			SimpleDraw::AddLine(from, to, Colors::Blue);
		}
		for (const auto& child : bone->children)
			DrawBone(skeleton, child, boneMatrices);
	}

	void ApplyBoneMatrices(Bone * bone, std::vector<SWAGE::Math::Matrix4>& boneMatrices)
	{
		if (bone->parent)
			boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];
		else
			boneMatrices[bone->index] = bone->toParentTransform;

		for (const auto& child : bone->children)
			ApplyBoneMatrices(child, boneMatrices);
	}

	void ApplyBoneMatrices(Bone * bone, const AnimationClip& clip, std::vector<SWAGE::Math::Matrix4>& boneMatrices, float animationTime)
	{
		if (bone->parent)
		{
			auto& boneAnim = clip.boneAnimations[bone->index];
			if (boneAnim)
			{
				Math::Vector3 scale = boneAnim->IsScaleKeyEmpty() ? Math::Vector3::One : boneAnim->GetScale(animationTime);
				Math::Quaternion rot = boneAnim->IsRotationKeyEmpty() ? Math::Quaternion::Identity : boneAnim->GetRotation(animationTime);
				Math::Vector3 pos = boneAnim->IsPositionKeyEmpty() ? Math::Vector3::Zero : boneAnim->GetPosition(animationTime);
				auto boneTransform = Math::Matrix4::Scaling(scale) * Math::Matrix4::RotationQuaternion(rot) * Math::Matrix4::Translation(pos);
				boneMatrices[bone->index] = boneTransform * boneMatrices[bone->parentIndex];
			}
			else
			{
				boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];
			}
		}
		else
		{
			boneMatrices[bone->index] = bone->toParentTransform;
		}

		for (const auto& child : bone->children)
			ApplyBoneMatrices(child, clip, boneMatrices, animationTime);
	}
}

void SWAGE::Graphics::DrawSkeleton(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices, Skeleton::DrawType drawType)
{
	if (drawType == Skeleton::DrawType::line)
		DrawBone(skeleton, skeleton.root, boneMatrices);
	else if (drawType == Skeleton::DrawType::cone)
		DrawSkeletonConeShapes(skeleton, boneMatrices);
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix)
{
	std::vector<SWAGE::Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, boneMatrices);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;

	return boneMatrices;
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton)
{
	std::vector<SWAGE::Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, boneMatrices);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform);

	return boneMatrices;
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, SWAGE::Math::Matrix4 worldMatrix, const AnimationClip & animationClip, float animationTime)
{
	std::vector<SWAGE::Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, boneMatrices, animationTime);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;

	return boneMatrices;
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, const AnimationClip & animationClip, float animationTime)
{
	std::vector<SWAGE::Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, boneMatrices, animationTime);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform);

	return boneMatrices;
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateSkinningMatrices(const Skeleton & skeleton)
{
	std::vector<SWAGE::Math::Matrix4> skinningMatrices;
	skinningMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, skinningMatrices);

	return skinningMatrices;
}

std::vector<SWAGE::Math::Matrix4> SWAGE::Graphics::CalculateSkinningMatrices(const Skeleton & skeleton, const AnimationClip & animationClip, float animationTime)
{
	std::vector<SWAGE::Math::Matrix4> skinningMatrices;
	skinningMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, skinningMatrices, animationTime);

	return skinningMatrices;
}
