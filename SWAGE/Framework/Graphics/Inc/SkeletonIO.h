#pragma once

#include "Skeleton.h"

namespace SWAGE::Graphics::SkeletonIO
{
	void Write(FILE* file, const Skeleton& skeleton);
	void Read(FILE* file, Skeleton& skeleton);
	void WriteBinary(FILE* file, const Skeleton& skeleton);
	void ReadBinary(FILE* file, Skeleton& skeleton);
}
