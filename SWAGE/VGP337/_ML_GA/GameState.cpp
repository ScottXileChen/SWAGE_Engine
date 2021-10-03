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

	const std::string kTarget = "Genetic Algorithm is cooooool!";
	const int kValidGeneValue = 126 - 32; // from character '~' to ' ' in ASCII table
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Black);
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

	if (mInitialized)
	{
		auto& best = mGA.GetBestGenome();
		if (best.fitness < (int)kTarget.size())
		{
			mGA.Advance();
			std::string bestStr;

			// Print the next best genome
			for (auto& gene : mGA.GetBestGenome().chromosome)
				bestStr += (char)(gene + 32);
			mAppLog.AddLog("Generation %d: %s\n", mGA.GetGeneration(), bestStr.c_str());
		}
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

	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Run!"))
	{
		mAppLog.Clear();
		mAppLog.AddLog("Initializing new population ...\n");

		auto computeFitnessFunc = [](auto& genome) {
			float fitness = 0.0f;

			// One point permatching character
			for (size_t i = 0; i < kTarget.size(); ++i)
			{
				if (kTarget[i] == genome.chromosome[i] + 32)
					fitness += 1.0f;
			}

			return fitness;
		};

		auto crossover = [](auto& genome, auto& parent1, auto& parent2) {
			for (size_t i = 0; i < parent1.chromosome.size(); ++i)
			{
				if (RandomFloat() < 0.45f)
					genome.chromosome.push_back(parent1.chromosome[i]);
				else
					genome.chromosome.push_back(parent2.chromosome[i]);
			}
		};

		auto mutate = [](auto& genome) {
			if (RandomFloat() < 0.1f)
				genome.chromosome[Random(0, (int)genome.chromosome.size() - 1)] = Random(0, (int)kValidGeneValue);
		};

		mGA.Initialize(100, (int)kTarget.size(), kValidGeneValue, computeFitnessFunc, crossover, mutate);
		mInitialized = true;
	}

	mAppLog.Draw("Console");
	ImGui::End();
}
