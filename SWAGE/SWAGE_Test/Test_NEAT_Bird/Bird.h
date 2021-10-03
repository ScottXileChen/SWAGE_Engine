#pragma once

#include <SWAGE/Inc/SWAGE.h>

class PipeManager;

class Bird
{
public:
	void Load();

	void Update(float deltaTime, const PipeManager& pm);
	void Render();

	void Flap();

	void Spawn(const SWAGE::Math::Vector2& pos);
	void Kill();

	SWAGE::Math::Shapes::Circle GetBound() const { return { mPosition, mRadius }; }
	bool IsAlive() const { return mAlive; }

	std::unique_ptr<SWAGE::ML::NEAT::NeuralNet> brain;
	float fitness = 0.0f;

private:
	std::array<SWAGE::Graphics::TextureId, 5> mTextureIds;
	SWAGE::Math::Vector2 mPosition;
	SWAGE::Math::Vector2 mVelocity;
	float mRadius = 30.0f;
	float mAnimationFrame = 0.0f;
	bool mAlive = false;
};