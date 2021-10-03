#include "Precompiled.h"
#include "MaterialIO.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void MaterialIO::Write(FILE * file, const Model::MaterialData & materialData)
{
	fprintf_s(file, "\n%f %f %f %f "
		, materialData.material.ambient.x
		, materialData.material.ambient.y
		, materialData.material.ambient.z
		, materialData.material.ambient.w);

	fprintf_s(file, "%f %f %f %f "
		, materialData.material.diffuse.x
		, materialData.material.diffuse.y
		, materialData.material.diffuse.z
		, materialData.material.diffuse.w);

	fprintf_s(file, "%f %f %f %f "
		, materialData.material.specular.x
		, materialData.material.specular.y
		, materialData.material.specular.z
		, materialData.material.specular.w);

	fprintf_s(file, "%f ", materialData.material.power);

	if (!materialData.diffuseMapName.empty())
		fprintf_s(file, "%s ", materialData.diffuseMapName.c_str());
	else
		fprintf_s(file, "none ");

	if (!materialData.specularMapName.empty())
		fprintf_s(file, "%s ", materialData.specularMapName.c_str());
	else
		fprintf_s(file, "none ");

	if (!materialData.normalMapName.empty())
		fprintf_s(file, "%s ", materialData.normalMapName.c_str());
	else
		fprintf_s(file, "none ");
}

void MaterialIO::Read(FILE * file, Model::MaterialData & materialData)
{
	fscanf_s(file, "%f %f %f %f"
		, &materialData.material.ambient.x
		, &materialData.material.ambient.y
		, &materialData.material.ambient.z
		, &materialData.material.ambient.w);

	fscanf_s(file, "%f %f %f %f"
		, &materialData.material.diffuse.x
		, &materialData.material.diffuse.y
		, &materialData.material.diffuse.z
		, &materialData.material.diffuse.w);

	fscanf_s(file, "%f %f %f %f"
		, &materialData.material.specular.x
		, &materialData.material.specular.y
		, &materialData.material.specular.z
		, &materialData.material.specular.w);

	fscanf_s(file, "%f ", &materialData.material.power);

	char strBuff[255];

	fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
	if (strcmp(strBuff, "none") == 0)
		materialData.diffuseMapName.clear();
	else
		materialData.diffuseMapName = strBuff;

	fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
	if (strcmp(strBuff, "none") == 0)
		materialData.specularMapName.clear();
	else
		materialData.specularMapName = strBuff;

	fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
	if (strcmp(strBuff, "none") == 0)
		materialData.normalMapName.clear();
	else
		materialData.normalMapName = strBuff;
}

void MaterialIO::WriteBinary(FILE * file, const Model::MaterialData& materialData)
{
	fwrite(&materialData.material, sizeof(Material), 1, file);
	size_t diffuseMapNameSize = materialData.diffuseMapName.size();
	fwrite(&diffuseMapNameSize, sizeof(size_t), 1, file);
	fwrite(materialData.diffuseMapName.c_str(), sizeof(char), diffuseMapNameSize, file);
	size_t specularMapNameSize = materialData.specularMapName.size();
	fwrite(&specularMapNameSize, sizeof(size_t), 1, file);
	fwrite(materialData.specularMapName.c_str(), sizeof(char), specularMapNameSize, file);
	size_t normalMapNameSize = materialData.normalMapName.size();
	fwrite(&normalMapNameSize, sizeof(size_t), 1, file);
	fwrite(materialData.normalMapName.c_str(), sizeof(char), normalMapNameSize, file);
}

void MaterialIO::ReadBinary(FILE * file, Model::MaterialData& materialData)
{
	size_t diffuseMapNameSize = 0;
	size_t specularMapNameSize = 0;
	size_t normalMapNameSize = 0;

	fread(&materialData.material, sizeof(Material), 1, file);
	fread(&diffuseMapNameSize, sizeof(size_t), 1, file);
	materialData.diffuseMapName.resize(diffuseMapNameSize);
	fread(materialData.diffuseMapName.data(), sizeof(char), diffuseMapNameSize, file);
	fread(&specularMapNameSize, sizeof(size_t), 1, file);
	materialData.specularMapName.resize(specularMapNameSize);
	fread(materialData.specularMapName.data(), sizeof(char), specularMapNameSize, file);
	fread(&normalMapNameSize, sizeof(size_t), 1, file);
	materialData.normalMapName.resize(normalMapNameSize);
	fread(materialData.normalMapName.data(), sizeof(char), normalMapNameSize, file);
}
