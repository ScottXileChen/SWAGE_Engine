#include "GameState.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <ImGui//Src/imgui_internal.h>

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;
using namespace SWAGE::ML;

namespace
{
	// Imgui for change theme.
	const char* themeItems[] = { "Classic", "Dark", "Light" };
	int themeItemIndex = 0;

	// Global Variable
	const size_t MAX_CITYS_COUNT = 20;
	const float circleBoundRadius = 200.0f;
	const float cityRadius = 40.0f;
	const float cityTextFont = 10.0f;
	const int kValidGeneValue = MAX_CITYS_COUNT - 1;
	const size_t populationSize = 500;
	float crossoverRate = 0.1f;
	float mutationRate = 0.05f;

	float kBestFitness = 0;
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Gray);

	float constant = 2 * SWAGE::Math::Constants::Pi / MAX_CITYS_COUNT;
	float angle = 0;
	for (int i = 0; i < MAX_CITYS_COUNT; ++i)
	{
		angle += constant;
		mCities.push_back(Vector2(sin(angle) * circleBoundRadius, cos(angle) * circleBoundRadius));
	}

	for (int i = 0; i < MAX_CITYS_COUNT; ++i)
		kTarget.push_back(i);

	kTarget2.push_back(0);
	for (int i = MAX_CITYS_COUNT - 1; i >= 1; --i)
		kTarget2.push_back(i);

	for (size_t i = 0; i < kTarget.size() - 1; ++i)
		kBestFitness += SWAGE::Math::Distance(mCities[kTarget[i]], mCities[kTarget[i + 1]]);
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
		if (!mFounded)
		{
			mGA.Advance(8);
			std::string bestStr;

			// Print the next best genome
			mAppLog.AddLog("Generation: %d: ", mGA.GetGeneration());
			auto& newBest = mGA.GetBestGenome();
			for (auto& gene : newBest.chromosome)
				mAppLog.AddLog("%s ", std::to_string(gene).c_str());
			mAppLog.AddLog(" - %f", newBest.fitness);
			mAppLog.AddLog("\n");
		}
		if (mGA.GetBestGenome().chromosome == kTarget
			|| mGA.GetBestGenome().chromosome == kTarget2)
		{
			mFounded = true;
		}
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

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

	if (ImGui::Button("Run!"))
	{
		mFounded = false;
		mAppLog.Clear();
		mAppLog.AddLog("Initializing new population ...\n");

		auto generatePopulation = [target = kTarget](auto& population)
		{
			population.resize(populationSize);
			for (auto& genome : population)
			{
				genome.chromosome.reserve(target.size());
				std::vector<int> cities;
				for (size_t i = 1; i < target.size(); ++i)
					cities.push_back(target[i]);
				genome.chromosome.push_back(0);
				for (size_t i = 0; i < target.size() - 1; ++i)
				{
					const size_t size = cities.size();
					int randomIndex = Random(0, (int)size - 1);
					genome.chromosome.push_back(cities[randomIndex]);
					cities.erase(cities.begin() + randomIndex);
				}
			}
		};

		auto computeFitnessFunc = [cities = mCities](auto& genome)
		{
			float distanceTraveled = 0.0f;

			for (size_t i = 0; i < genome.chromosome.size() - 1; ++i)
				distanceTraveled += SWAGE::Math::Distance(cities[genome.chromosome[i]], cities[genome.chromosome[i + 1]]);

			return kBestFitness - distanceTraveled;
		};

		auto crossover = [](auto& genome, auto& parent1, auto& parent2)
		{
			//for (size_t i = 0; i < parent1.chromosome.size(); ++i)
			//	genome.chromosome.push_back(parent1.chromosome[i]);

			//for (size_t i = 1; i < parent1.chromosome.size(); ++i)
			//{
			//	if (RandomFloat() < crossoverRate)
			//	{
			//		int swapTarget = Random(1, (int)kValidGeneValue);
			//		std::swap(genome.chromosome[i], genome.chromosome[swapTarget]);
			//	}
			//}

			for (size_t i = 0; i < parent1.chromosome.size(); ++i)
				genome.chromosome.push_back(parent1.chromosome[i]);

			for (size_t i = 1; i < parent1.chromosome.size(); ++i)
			{
				if (RandomFloat() < crossoverRate)
				{
					// crossover mapping
					int swapTargetLeft = parent1.chromosome[i];
					int swapTargetRight = Random(1, (int)kValidGeneValue);
					size_t index1 = 0;
					size_t index2 = 0;
					for (size_t j = 0; j < genome.chromosome.size(); ++j)
					{
						if (genome.chromosome[j] == swapTargetLeft)
							index1 = j;
						if (genome.chromosome[j] == swapTargetRight)
							index2 = j;
					}
					std::swap(genome.chromosome[index1], genome.chromosome[index2]);
				}
			}

			for (size_t i = 1; i < parent2.chromosome.size(); ++i)
			{
				if (RandomFloat() < crossoverRate)
				{
					// crossover mapping
					int swapTargetLeft = parent2.chromosome[i];
					int swapTargetRight = Random(1, (int)kValidGeneValue);
					size_t index1 = 0;
					size_t index2 = 0;
					for (size_t j = 0; j < genome.chromosome.size(); ++j)
					{
						if (genome.chromosome[j] == swapTargetLeft)
							index1 = j;
						if (genome.chromosome[j] == swapTargetRight)
							index2 = j;
					}
					std::swap(genome.chromosome[index1], genome.chromosome[index2]);
				}
			}
		};

		auto mutate = [](auto& genome) {
			if (RandomFloat() < mutationRate)
			{
				int swapTargetLeft = Random(1, (int)kValidGeneValue);
				int value = genome.chromosome[swapTargetLeft];
				genome.chromosome.erase(genome.chromosome.begin() + swapTargetLeft);
				genome.chromosome.push_back(value);
			}
		};

		mGA.Initialize(
			populationSize,
			(int)kTarget.size(),
			kValidGeneValue,
			generatePopulation,
			computeFitnessFunc,
			crossover,
			mutate);

		mInitialized = true;
	}

	ImGui::DragFloat("Crossover Rate:", &crossoverRate, 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat("Mutation Rate:", &mutationRate, 0.05f, 0.0f, 1.0f);
	DrawCitys();

	mAppLog.Draw("Console");
	ImGui::End();
}

void GameState::DrawCitys()
{
	ImVec2 offset{ 0.0f, 20.0f };
	ImGui::SetNextWindowSize(ImVec2{ 800.0f, 400.0f } +offset);
	ImGui::Begin("Cities", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImVec2 winPos = ImGui::GetWindowPos();
	ImVec2 winPosCenter = ImGui::GetWindowPos() + ImVec2(ImGui::GetWindowWidth() * 0.5f, ImGui::GetWindowHeight() * 0.5f);
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 20; ++x)
		{
			int i = x + (y * 8);
			ImVec2 min{ x * 40.0f, y * 40.0f };
			ImVec2 max = min + ImVec2{ 40.0f, 40.0f };
			drawList->AddRectFilled(min + winPos + offset, max + winPos + offset, 0xff000000);
		}
	}

	for (int i = 0; i < MAX_CITYS_COUNT; ++i)
	{
		drawList->AddCircle(ImVec2{ mCities[i].x, mCities[i].y } + winPosCenter + offset, cityRadius, 0xffff22ff);
		drawList->AddText(ImVec2{ mCities[i].x, mCities[i].y } + winPosCenter + offset, 0xffff22ff, std::to_string(i).c_str());
	}

	ImGui::End();
}
