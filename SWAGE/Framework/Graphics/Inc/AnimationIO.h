#pragma once

#include "AnimationClip.h"
#include "Animation.h"

namespace SWAGE::Graphics
{
	class AnimationIO
	{
	public:
		static void Write(FILE* file, const SWAGE::Graphics::AnimationClip& clip);
		static void Read(FILE* file, SWAGE::Graphics::AnimationClip& clip);
		static void WriteBinary(FILE* file, const SWAGE::Graphics::AnimationClip& clip);
		static void ReadBinary(FILE* file, SWAGE::Graphics::AnimationClip& clip);
	};
}
