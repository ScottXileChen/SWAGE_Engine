#pragma once

#include "MeshTypes.h"

namespace SWAGE::Graphics::MeshIO
{
	void Write(FILE* file, const SkinnedMesh& mesh);
	void Read(FILE* file, SkinnedMesh& mesh);
	void WriteBinary(FILE* file, const SkinnedMesh& mesh);
	void ReadBinary(FILE* file, SkinnedMesh& mesh);
}
