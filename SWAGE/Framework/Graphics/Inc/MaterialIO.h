#pragma once

#include "Model.h"

namespace SWAGE::Graphics::MaterialIO
{
	void Write(FILE* file, const Model::MaterialData& materialData);
	void Read(FILE* file, Model::MaterialData& materialData);
	void WriteBinary(FILE* file, const Model::MaterialData& materialData);
	void ReadBinary(FILE* file, Model::MaterialData& materialData);
}
