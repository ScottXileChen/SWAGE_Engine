#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;
using namespace SWAGE::ML;

namespace
{
	// For initialize.
	int samples = 100;
	float b0 = 0.1f;
	float b1 = 1.0f;
	float minX = 0.0f;
	float maxX = 100.0f;
	float noise = 10.0f;

	// Imgui for change theme.
	const char* themeItems[] = { "Classic", "Dark","Light" };
	int themeItemIndex = 0;

	int epoch = 1000;

	float alpha = 0.000001f;
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Black);

	mDataset = Datasets::MakeLinear(samples, b0, b1, minX, maxX, noise);
}

void GameState::Terminate()
{
	
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		mAppLog.AddLog("Bam!\n");
	}
}

void GameState::DebugUI()
{
	if (ImGui::Combo("UI Theme", &themeItemIndex, themeItems, IM_ARRAYSIZE(themeItems)))
	{
		if (themeItemIndex == 0)
		{
			DebugUI::SetTheme(DebugUI::Theme::Classic);
		}
		else if (themeItemIndex == 1)
		{
			DebugUI::SetTheme(DebugUI::Theme::Dark);
		}
		else
		{
			DebugUI::SetTheme(DebugUI::Theme::Light);
		}
	}

	if (ImPlot::BeginPlot("Linear Regression", "X", "y"))
	{
		float startX = minX;
		float endX = maxX;
		float startY = mLinReg.Predict(startX);
		float endY = mLinReg.Predict(endX);

		std::vector<ImVec2> line;
		line.push_back({ startX, startY });
		line.push_back({ endX, endY });
		ImPlot::PlotScatter("Dataset", mDataset.x0.data(), mDataset.y.data(), (int)mDataset.x0.size(), (int)mDataset.y.size());
		ImPlot::PlotLine("Model", line.data(), (int)line.size());
		ImPlot::EndPlot();
	}

	ImGui::Begin("Test");

	ImGui::InputInt("Epoch: ", &epoch);
	ImGui::InputFloat("Learning Rate: ", &alpha, 0.00001f, 0.01f, 10);

	ImGui::PushID("Training");
	if (ImGui::Button("Train"))
		Train();
	ImGui::PopID();

	ImGui::PushID("Reset Line");
	if (ImGui::Button("Reset"))
		mLinReg.Reset();
	ImGui::PopID();

	if (ImGui::CollapsingHeader("Reset dataset"))
	{
		ImGui::InputInt("Sample size: ", &samples);
		ImGui::InputFloat("b0: ", &b0);
		ImGui::InputFloat("b1: ", &b1);
		ImGui::InputFloat("Min X: ", &minX);
		ImGui::InputFloat("Max X: ", &maxX);
		ImGui::InputFloat("Noise: ", &noise);

		ImGui::PushID("ResetLinReg");
		if (ImGui::Button("Reset"))
			mDataset = Datasets::MakeLinear(samples, b0, b1, minX, maxX, noise);
		ImGui::PopID();
	}

	ImGui::End();

	mAppLog.Draw("Console");
}

void GameState::Train()
{
	mAppLog.Clear();
	mAppLog.AddLog("Generating data ...\n");

	//mLinReg.b0 = b0;
	//mLinReg.b1 = b1;
	mLinReg.learningRate = alpha;
	// Or you can loop until error is smaller than some threshold ...
	for (int e = 0; e < epoch; ++e)
	{
		float error = mLinReg.Fit(mDataset);
		mAppLog.AddLog("b0 = %f, b1 = %f, error = %f\n", mLinReg.b0, mLinReg.b1, error);
	}

	if (mLinReg.b0 != mLinReg.b0 || mLinReg.b1 != mLinReg.b1)
	{
		mAppLog.AddLog("Failed to train. Change your learning rate and try again!");
		mLinReg.Reset();
	}
}
