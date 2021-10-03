#pragma once

#include <SWAGE/Inc/SWAGE.h>
#include <ImGui/Inc/AppLog.h>
#include <ImGui/Inc/ImPlot.h>

class GameState : public SWAGE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void DebugUI() override;

private:
	AppLog mAppLog;

	SWAGE::ML::GeneticAlgorithm mGA;
	bool mInitialized = false;
};