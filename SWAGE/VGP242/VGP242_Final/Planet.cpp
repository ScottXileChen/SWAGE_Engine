#include "Planet.h"

void Planet::Initialize(float planetRadius, const char* texturePath, SWAGE::Math::Vector3 position)
{
	mPlanetMesh = SWAGE::Graphics::MeshBuilder::CreateSpherePX(50, 50, planetRadius);
	mPlanetBuffer.Initialize(mPlanetMesh);
	mTexture.Initialize(texturePath);
	mPosition = position;
}

void Planet::Terminate()
{
	mPlanetBuffer.Terminate();
	mTexture.Terminate();
}

void Planet::Update(float deltaTime)
{
	// SeftRotaing
	mRevolvingRotation += mRevolvingSpeed * deltaTime;
	mSelfRotation += mSelfRotationSpeed * deltaTime;
	if (strcmp(mName.c_str(), "Sun") == 0)
		mMatWorld = SWAGE::Math::Matrix4::RotationY(mSelfRotation);
	else
		mMatWorld = SWAGE::Math::Matrix4::RotationY(mSelfRotation) * SWAGE::Math::Matrix4::Translation(mPosition) * SWAGE::Math::Matrix4::RotationY(mRevolvingRotation);
}

void Planet::Render()
{
	mTexture.BindPS(0);
	mPlanetBuffer.Render();
}