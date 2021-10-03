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
	float b2 = 1.0f;
	float minX = 0.0f;
	float maxX = 100.0f;
	float noise = 10.0f;

	// Imgui for change theme.
	const char* themeItems[] = { "Classic", "Dark", "Light" };
	int themeItemIndex = 0;

	int epoch = 1000;

	float alpha = 0.00001f;//0.0001f;
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Black);

	mDataset = Datasets::MakeLogistic(samples, b0, b1, b2, minX, maxX, noise);
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

	if (ImPlot::BeginPlot("Logistic Regression", "x0", "x1"))
	{
		std::vector<ImVec2> modelLine;
		int count = static_cast<int>(std::size(mDataset.x0));
		float m = mLogReg.b1 / -mLogReg.b2;
		float b = mLogReg.b0 / -mLogReg.b2;
		modelLine.push_back({ minX, minX * m + b });
		modelLine.push_back({ maxX, maxX * m + b});
		ImPlot::PlotLine("Model", modelLine.data(), (int)modelLine.size());

		std::vector<float> ax, ay, bx, by;
		for (int i = 0; i < count; ++i)
		{
			float p = b0 + b1 * mDataset.x0[i] + b2 * mDataset.x1[i];
			if (p >= 0)
			{
				ax.push_back(mDataset.x0[i]);
				ay.push_back(mDataset.x1[i]);
			}
			else
			{
				bx.push_back(mDataset.x0[i]);
				by.push_back(mDataset.x1[i]);
			}
		}
		if (!bx.empty())
			ImPlot::PlotScatter("Zeros", bx.data(), by.data(), (int)bx.size());
		if (!ax.empty())
			ImPlot::PlotScatter("Ones", ax.data(), ay.data(), (int)ax.size());
		ImPlot::EndPlot();
	}

	ImGui::Begin("Test");

	ImGui::InputInt("Epoch: ", &epoch);
	ImGui::InputFloat("Learning Rate: ", &alpha, 0.00001f, 0.01f, 10);

	ImGui::PushID("Training");
	if (ImGui::Button("Train"))
		Train();
	ImGui::PopID();

	ImGui::PushID("Reset line");
	if (ImGui::Button("Reset"))
		mLogReg.Reset();
	ImGui::PopID();

	if (ImGui::CollapsingHeader("Reset dataset"))
	{
		ImGui::InputInt("Sample size: ", &samples);
		ImGui::InputFloat("b0: ", &b0);
		ImGui::InputFloat("b1: ", &b1);
		ImGui::InputFloat("b2: ", &b2);
		ImGui::InputFloat("Min X: ", &minX);
		ImGui::InputFloat("Max X: ", &maxX);
		ImGui::InputFloat("Noise: ", &noise);

		ImGui::PushID("ResetLinReg");
		if (ImGui::Button("Reset"))
			mDataset = Datasets::MakeLogistic(samples, b0, b1, b2, minX, maxX, noise);
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
	mLogReg.learningRate = alpha;
	// Or you can loop until error is smaller than some threshold ...
	for (int e = 0; e < epoch; ++e)
	{
		float error = mLogReg.Fit(mDataset);
		mAppLog.AddLog("b0 = %f, b1 = %f, b2 = %f, error = %f\n", mLogReg.b0, mLogReg.b1, mLogReg.b2, error);
	}

	if (mLogReg.b0 != mLogReg.b0 || mLogReg.b1 != mLogReg.b1)
	{
		mAppLog.AddLog("Failed to train. Change your learning rate and try again!");
		mLogReg.Reset();
	}
}
