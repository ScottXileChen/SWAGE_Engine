#include "Precompiled.h"
#include "MeshIO.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void MeshIO::Write(FILE * file, const SkinnedMesh & mesh)
{
	fprintf_s(file, "\nSizeOfVertices: %d\n", static_cast<int>(mesh.vertices.size()));
	fprintf_s(file, "SizeOfIndices: %d\n", static_cast<int>(mesh.indices.size()));

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		fprintf_s(file, "%f %f %f "
			, mesh.vertices[i].position.x
			, mesh.vertices[i].position.y
			, mesh.vertices[i].position.z);
		fprintf_s(file, "%f %f %f "
			, mesh.vertices[i].normal.x
			, mesh.vertices[i].normal.y
			, mesh.vertices[i].normal.z);
		fprintf_s(file, "%f %f %f "
			, mesh.vertices[i].tangent.x
			, mesh.vertices[i].tangent.y
			, mesh.vertices[i].tangent.z);
		fprintf_s(file, "%f %f "
			, mesh.vertices[i].uv.x
			, mesh.vertices[i].uv.y);
		fprintf_s(file, "%d %d %d %d "
			, mesh.vertices[i].boneIndices[0]
			, mesh.vertices[i].boneIndices[1]
			, mesh.vertices[i].boneIndices[2]
			, mesh.vertices[i].boneIndices[3]);
		fprintf_s(file, "%f %f %f %f\n"
			, mesh.vertices[i].boneWeights[0]
			, mesh.vertices[i].boneWeights[1]
			, mesh.vertices[i].boneWeights[2]
			, mesh.vertices[i].boneWeights[3]);
	}

	fprintf_s(file, "\n");
	for (size_t i = 0; i < mesh.indices.size(); i+=3)
	{
		fprintf_s(file, "%d %d %d\n"
		, mesh.indices[i]
		, mesh.indices[i + 1]
		, mesh.indices[i + 2]);
	}
}

void MeshIO::Read(FILE * file, SkinnedMesh & mesh)
{
	char strBuff[255];
	int intBuffer = 0;
	int verticeSize = 0;
	int indicesSize = 0;

	fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
	if (strcmp(strBuff, "SizeOfVertices:") == 0)
		fscanf_s(file, "%d", &verticeSize);
	else
		return;

	fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
	if (strcmp(strBuff, "SizeOfIndices:") == 0)
		fscanf_s(file, "%d", &indicesSize);
	else
		return;

	mesh.vertices.reserve(verticeSize);
	mesh.indices.reserve(indicesSize);

	for (int i = 0; i < verticeSize; ++i)
	{
		BoneVertex boneVertex;

		fscanf_s(file, "%f", &boneVertex.position.x);
		fscanf_s(file, "%f", &boneVertex.position.y);
		fscanf_s(file, "%f", &boneVertex.position.z);

		fscanf_s(file, "%f", &boneVertex.normal.x);
		fscanf_s(file, "%f", &boneVertex.normal.y);
		fscanf_s(file, "%f", &boneVertex.normal.z);

		fscanf_s(file, "%f", &boneVertex.tangent.x);
		fscanf_s(file, "%f", &boneVertex.tangent.y);
		fscanf_s(file, "%f", &boneVertex.tangent.z);

		fscanf_s(file, "%f", &boneVertex.uv.x);
		fscanf_s(file, "%f", &boneVertex.uv.y);

		if (boneVertex.uv.x < 0.0) boneVertex.uv.x = boneVertex.uv.x + 1;
		if (boneVertex.uv.y < 0.0) boneVertex.uv.y = boneVertex.uv.y + 1;

		fscanf_s(file, "%d", &boneVertex.boneIndices[0]);
		fscanf_s(file, "%d", &boneVertex.boneIndices[1]);
		fscanf_s(file, "%d", &boneVertex.boneIndices[2]);
		fscanf_s(file, "%d", &boneVertex.boneIndices[3]);

		fscanf_s(file, "%f", &boneVertex.boneWeights[0]);
		fscanf_s(file, "%f", &boneVertex.boneWeights[1]);
		fscanf_s(file, "%f", &boneVertex.boneWeights[2]);
		fscanf_s(file, "%f", &boneVertex.boneWeights[3]);

		mesh.vertices.push_back(boneVertex);
	}

	for (int i = 0; i < indicesSize; i += 3)
	{
		int indice1;
		int indice2;
		int indice3;
		fscanf_s(file, "%d", &indice1);
		fscanf_s(file, "%d", &indice2);
		fscanf_s(file, "%d", &indice3);
		mesh.indices.push_back(indice1);
		mesh.indices.push_back(indice2);
		mesh.indices.push_back(indice3);
	}
}

void MeshIO::WriteBinary(FILE * file, const SkinnedMesh & mesh)
{
	const uint32_t verticesCount = static_cast<uint32_t>(mesh.vertices.size());
	const uint32_t indicesCount = static_cast<uint32_t>(mesh.indices.size());

	fwrite(&verticesCount, sizeof(uint32_t), 1, file);
	fwrite(&indicesCount, sizeof(uint32_t), 1, file);

	fwrite(&mesh.vertices[0], sizeof(BoneVertex), verticesCount, file);
	fwrite(&mesh.indices[0], sizeof(uint32_t), indicesCount, file);
}

void MeshIO::ReadBinary(FILE * file, SkinnedMesh & mesh)
{
	uint32_t verticesCount;
	uint32_t indicesCount;
	fread(&verticesCount, sizeof(uint32_t), 1, file);
	fread(&indicesCount, sizeof(uint32_t), 1, file);

	mesh.vertices.resize(verticesCount);
	mesh.indices.resize(indicesCount);

	fread(&mesh.vertices[0], sizeof(BoneVertex), verticesCount, file);
	fread(&mesh.indices[0], sizeof(uint32_t), indicesCount, file);

	for (auto& data: mesh.vertices)
	{
		if (data.uv.x < 0.0) data.uv.x = data.uv.x + 1;
		if (data.uv.y < 0.0) data.uv.y = data.uv.y + 1;
	}
}
