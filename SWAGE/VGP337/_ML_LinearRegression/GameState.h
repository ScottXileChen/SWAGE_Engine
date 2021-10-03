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

	void Train();

private:
	AppLog mAppLog;

	SWAGE::ML::Dataset mDataset;
	SWAGE::ML::LinearRegression mLinReg;
};