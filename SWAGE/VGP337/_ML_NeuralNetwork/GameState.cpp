#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;
using namespace SWAGE::ML;

namespace
{
	// Imgui for change theme.
	const char* themeItems[] = { "Classic", "Dark", "Light" };
	int themeItemIndex = 0;

	// Project
	int trainingTime = 1000;

	std::vector<size_t> topology;
	std::vector<float> inputValue1;
	std::vector<float> inputValue2;
	std::vector<float> inputValue3;
	std::vector<float> inputValue4;

	std::vector<float> targetValue1;
	std::vector<float> targetValue2;
	std::vector<float> targetValue3;
	std::vector<float> targetValue4;

	float predicted[2];
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Black);

	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(1);

	mNeuralNetwork = new NeuralNetwork(topology);

	inputValue1.push_back(0); inputValue1.push_back(0);
	inputValue2.push_back(0); inputValue2.push_back(1);
	inputValue3.push_back(1); inputValue3.push_back(0);
	inputValue4.push_back(1); inputValue4.push_back(1);

	targetValue1.push_back(0);
	targetValue2.push_back(1);
	targetValue3.push_back(1);
	targetValue4.push_back(0);
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

	ImGui::DragInt("Training time", &trainingTime, 100, 1000, 5000);

	if (ImGui::Button("Training"))
	{
		Training();
		mAppLog.AddLog("Finish training!\n");
	}

	ImGui::DragFloat2("Input", predicted, 0.1f, 0, 5);

	if (ImGui::Button("Result"))
	{
		std::vector<float> input;
		input.push_back(predicted[0]);
		input.push_back(predicted[1]);
		mNeuralNetwork->FeedFoward(input);
		
		const std::vector<float> result = mNeuralNetwork->GetResults();

		for (auto r : result)
		{
			mAppLog.AddLog("%f\n", r);
		}
	}

	mAppLog.Draw("Console");
}

void GameState::Training()
{
	for (int i = 0; i < trainingTime; ++i)
	{
		mNeuralNetwork->FeedFoward(inputValue1);
		mNeuralNetwork->BackPropagate(targetValue1);

		mNeuralNetwork->FeedFoward(inputValue2);
		mNeuralNetwork->BackPropagate(targetValue2);

		mNeuralNetwork->FeedFoward(inputValue3);
		mNeuralNetwork->BackPropagate(targetValue3);

		mNeuralNetwork->FeedFoward(inputValue4);
		mNeuralNetwork->BackPropagate(targetValue4);
	}
}
