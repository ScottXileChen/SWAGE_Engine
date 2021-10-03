#pragma once

#include "Model.h"

namespace SWAGE::Graphics
{
	class Animator
	{
	public:
		Animator() = default;
		~Animator();

		Animator(const Animator&) = delete;
		Animator& operator=(const Animator&) = delete;

		void Initialize(const SWAGE::Graphics::Model* model) { mModel = model; }

		void PlayAnimation(const char* clipName);
		void PlayAnimation(int clipIndex);
		void Play() { mAnimate = true; }
		void Stop() { mAnimate = false; }

		void Update(float deltaTime);

		const std::vector<SWAGE::Math::Matrix4> GetSkeletonTransform() const { return mSkeletonTransform; };
		const std::vector<SWAGE::Math::Matrix4> GetToLocalTransform() const { return mToLocalTransform; };

		void SetAnimationSpeed(float speed) { mAnimationSpeed = speed; }
		void SetLooping(bool loop) { mLooping = loop; }

	private:
		const SWAGE::Graphics::Model* mModel = nullptr;
		std::vector<SWAGE::Math::Matrix4> mSkeletonTransform;
		std::vector<SWAGE::Math::Matrix4> mToLocalTransform;
		float mAnimationTimer = 0.0f;
		float mAnimationSpeed = 1.0f;
		int mAnimClipIndex = 0;
		bool mAnimate = false;
		bool mLooping = false;
	};
}