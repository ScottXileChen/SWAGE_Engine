#include "Precompiled.h"
#include "ModelLoader.h"
#include "MeshIO.h"
#include "MaterialIO.h"
#include "SkeletonIO.h"
#include "AnimationIO.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

void ModelLoader::LoadObj(const std::filesystem::path fileName, float scale, MeshPX& mesh)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector2> uvs;
	std::vector<uint32_t> positionIndices, uvIndices;

	while (true)
	{
		char buffer[256];
		int result = fscanf_s(file, "%s", buffer, (int)std::size(buffer));

		// If we reached the end of the file, we are done
		if (result == EOF)
			break;

		if (strcmp(buffer, "v") == 0)
		{
			Math::Vector3 position;
			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position * scale);
		}
		else if (strcmp(buffer, "vt") == 0)
		{
			Math::Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back({ uv.x, 1.0f - uv.y });
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[3], t[3], n[3];
			fgets(buffer, (int)std::size(buffer), file);

			if (sscanf_s(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v[0], &t[0], &n[0],
				&v[1], &t[1], &n[1],
				&v[2], &t[2], &n[2]) == 9)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);
				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);
			}
		}
	}

	fclose(file);

	// Reconstruct vertices
	std::vector<VertexPX> vertices;
	vertices.reserve(positionIndices.size());
	for (size_t i = 0; i < positionIndices.size(); ++i)
	{
		VertexPX vertex;
		vertex.position = positions[positionIndices[i] - 1];
		vertex.uv = uvs[uvIndices[i] - 1];
		vertices.push_back(vertex);
	}

	// Generate indices
	std::vector<uint32_t> indices;
	indices.resize(vertices.size());
	std::iota(indices.begin(), indices.end(), 0);

	// Initialize mesh
	mesh.vertices = std::move(vertices);
	mesh.indices = std::move(indices);
}

void ModelLoader::LoadObj(const std::filesystem::path fileName, float scale, Mesh& mesh)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector3> normals;
	//std::vector<Math::Vector3> tangents;
	std::vector<Math::Vector2> uvs;
	std::vector<uint32_t> positionIndices, uvIndices, normalIndices;

	while (true)
	{
		char buffer[256];
		int result = fscanf_s(file, "%s", buffer, (int)std::size(buffer));

		// If we reached the end of the file, we are done
		if (result == EOF)
			break;

		if (strcmp(buffer, "v") == 0)
		{
			Math::Vector3 position;
			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position * scale);
		}
		else if (strcmp(buffer, "vn") == 0)
		{
			Math::Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal * scale);
		}
		else if (strcmp(buffer, "vt") == 0)
		{
			Math::Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back({ uv.x, 1.0f - uv.y });
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[3], t[3], n[3];
			fgets(buffer, (int)std::size(buffer), file);

			if (sscanf_s(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v[0], &t[0], &n[0],
				&v[1], &t[1], &n[1],
				&v[2], &t[2], &n[2]) == 9)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);
				normalIndices.push_back(n[0]);
				normalIndices.push_back(n[1]);
				normalIndices.push_back(n[2]);
				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);
			}
		}
	}

	fclose(file);

	// Reconstruct vertices
	std::vector<Vertex> vertices;
	vertices.reserve(positionIndices.size());
	for (size_t i = 0; i < positionIndices.size(); ++i)
	{
		Vertex vertex;
		vertex.position = positions[positionIndices[i] - 1];
		vertex.normal = normals[normalIndices[i] - 1];
		//vertex.tangent;
		vertex.uv = uvs[uvIndices[i] - 1];
		vertices.push_back(vertex);
	}

	// Generate indices
	std::vector<uint32_t> indices;
	indices.resize(vertices.size());
	std::iota(indices.begin(), indices.end(), 0);

	// Initialize mesh
	mesh.vertices = std::move(vertices);
	mesh.indices = std::move(indices);
}

void ModelLoader::LoadModel(const std::filesystem::path fileName, Model& model, bool loadBinary)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), loadBinary ? "rb" : "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	if (loadBinary)
	{
		uint32_t meshCount;
		fread(&meshCount, sizeof(uint32_t), 1, file);

		model.meshData.reserve(meshCount);

		for (uint32_t i = 0; i < meshCount; ++i)
		{
			auto& meshData = model.meshData.emplace_back(std::make_unique<Model::MeshData>());
			fread(&meshData->materialIndex, sizeof(uint32_t), 1, file);
			MeshIO::ReadBinary(file, meshData->mesh);
		}
	}
	else
	{
		char strBuff[255];
		int meshCount = 0;
		int materialIndex = 0;
		fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
		fscanf_s(file, "%d", &meshCount);

		model.meshData.reserve(meshCount);

		for (int i = 0; i < meshCount; ++i)
		{
			auto& meshData = model.meshData.emplace_back(std::make_unique<Model::MeshData>());
			fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
			fscanf_s(file, "%d", &materialIndex);
			meshData->materialIndex = materialIndex;
			MeshIO::Read(file, meshData->mesh);
		}
	}

	fclose(file);
}

void ModelLoader::LoadMaterial(std::filesystem::path fileName, Model & model, bool loadBinary)
{
	fileName.replace_extension("material");

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), loadBinary ? "rb" : "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	int materialCount = 0;

	if (loadBinary)
	{
		fread(&materialCount, sizeof(int), 1, file);

		model.materialData.resize(materialCount);

		for (int i = 0; i < materialCount; ++i)
			MaterialIO::ReadBinary(file, model.materialData[i]);
	}
	else
	{
		char strBuff[255];
		
		fscanf_s(file, "%s", strBuff, (int)std::size(strBuff));
		fscanf_s(file, "%d", &materialCount);

		model.materialData.resize(materialCount);

		for (int i = 0; i < materialCount; ++i)
			MaterialIO::Read(file, model.materialData[i]);
	}

	fclose(file);
}

bool ModelLoader::LoadSkeleton(std::filesystem::path fileName, Model & model, bool loadBinary)
{
	fileName.replace_extension("skeleton");

	if (!std::filesystem::exists(fileName))
		return false;

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), loadBinary ? "rb" : "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	model.skeleton = std::make_unique<Skeleton>();

	if (loadBinary)
		SkeletonIO::ReadBinary(file, *(model.skeleton));
	else
		SkeletonIO::Read(file, *(model.skeleton));

	fclose(file);

	return true;
}

bool ModelLoader::LoadAnimation(std::filesystem::path fileName, Model & model, bool loadBinary)
{
	fileName.replace_extension("anim");

	if (!std::filesystem::exists(fileName))
		return false;

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), loadBinary ? "rb" : "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	if (loadBinary)
	{
		size_t animationCount = 0;
		fread(&animationCount, sizeof(size_t), 1, file);
		for (size_t i = 0; i < animationCount; i++)
		{
			auto& animationClip = model.animSet.emplace_back(std::make_unique<AnimationClip>());
			AnimationIO::ReadBinary(file, *animationClip);
		}
	}
	else
	{
		uint32_t animationCount = 0;
		fscanf_s(file, "%d ", &animationCount);
		for (size_t i = 0; i < animationCount; i++)
		{
			auto& animationClip = model.animSet.emplace_back(std::make_unique<AnimationClip>());
			AnimationIO::Read(file, *animationClip);
		}
	}

	fclose(file);

	return true;
}
