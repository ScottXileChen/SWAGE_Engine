#pragma once

#include <SWAGE/Inc/SWAGE.h>

class Planet
{
public:
	void Initialize(float planetRadius, const char* texturePath, SWAGE::Math::Vector3 mPosition);
	void Terminate();
	Planet() = default;
	~Planet() = default;

	Planet(const Planet&) = delete;
	Planet& operator=(const Planet&) = delete;

	Planet(Planet&&) = delete;
	Planet& operator=(Planet&&) = delete;

	void Update(float deltaTime);
	void Render();

	void SetSelfRotationSpeed(float speed) { mSelfRotationSpeed = speed; }
	void SetRevolvingSpeed(float speed) { mRevolvingSpeed = speed; }
	void SetName(std::string name) { mName = name; }

	SWAGE::Math::Matrix4 GetMatWorld()const { return mMatWorld; }
	SWAGE::Math::Vector3 GetPosition()const { return mPosition; }
	std::string GetName()const { return mName; }

private:
	std::string mName;
	SWAGE::Graphics::Texture mTexture;
	SWAGE::Graphics::MeshBase<SWAGE::Graphics::VertexPX> mPlanetMesh;
	SWAGE::Graphics::MeshBuffer mPlanetBuffer;
	SWAGE::Math::Vector3 mPosition;
	SWAGE::Math::Matrix4 mMatWorld;
	float mSelfRotation = 0.0f;
	float mRevolvingRotation = 0.0f;
	float mSelfRotationSpeed = 0.0f;
	float mRevolvingSpeed = 0.0f;
};

using Planets = std::vector<std::unique_ptr<Planet>>;