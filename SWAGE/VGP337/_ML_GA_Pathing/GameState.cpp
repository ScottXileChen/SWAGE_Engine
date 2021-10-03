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

	const std::string kTarget = "Genetic Algorithm is cooooool!";

	const int kValidGeneValue = 3;
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Gray);

	mStartPos = { 20, 20 };
	mCurrentPos = mStartPos;
	mEndPos = { 780, 380 };
	mPath.push_back(mCurrentPos);
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
			mGA.Advance();
			std::string bestStr;

			// Print the next best genome
			for (auto& gene : mGA.GetBestGenome().chromosome)
				bestStr += (char)(gene + 48);
			mAppLog.AddLog("Generation %d: %s\n", mGA.GetGeneration(), bestStr.c_str());
		}

	}

	//if (SWAGE::Math::Distance(mPath.back(), mCurrentPos) >= 0.0001f)
	//{
	//	mPath.push_back(mCurrentPos);
	//}
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
		mAppLog.Clear();
		mAppLog.AddLog("Initializing new population ...\n");

		auto computeFitnessFunc = [endPos = mEndPos, startPos = mStartPos](auto& genome) {
			Vector2 currentPos = startPos;
			float distanceTraveled = 0.0f;

			for (auto direction : genome.chromosome)
			{
				if (direction == 0 && currentPos.y >= 20)
				{
					currentPos.y -= 20;
					distanceTraveled += 10.0f;
				}
				else if (direction == 1 && currentPos.y < 380 - 20)
				{
					currentPos.y += 20;
					distanceTraveled += 10.0f;
				}
				else if (direction == 2 && currentPos.x >= 20)
				{
					currentPos.x -= 20;
					distanceTraveled += 10.0f;
				}
				else if (direction == 3 && currentPos.x < 780 - 20)
				{
					currentPos.x += 20;
					distanceTraveled += 10.0f;
				}
			}
			//// One point permatching character
			//for (size_t i = 0; i < kTarget.size(); ++i)
			//{
			//	if (kTarget[i] == genome.chromosome[i] + 32)
			//		fitness += 1.0f;
			//}
			float distanceToEnd = SWAGE::Math::Distance(currentPos, endPos);
			return 5000 - distanceToEnd - distanceTraveled;
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
			if (RandomFloat() < 0.35f)
				genome.chromosome[Random(0, (int)genome.chromosome.size() - 1)] = Random(0, (int)kValidGeneValue);
		};

		mGA.Initialize(100, 100, kValidGeneValue, computeFitnessFunc, crossover, mutate);
		mInitialized = true;
	}

	DrawMaze();

	mAppLog.Draw("Console");
	ImGui::End();
}

void GameState::DrawMaze()
{
	ImVec2 offset{ 0.0f, 20.0f };
	ImGui::SetNextWindowSize(ImVec2{ 800.0f, 400.0f } + offset);
	ImGui::Begin("Target", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImVec2 winPos = ImGui::GetWindowPos();
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

	drawList->AddCircle(ImVec2{ mStartPos.x, mCurrentPos.y } + winPos + offset, 10, 0xffff22ff);
	drawList->AddCircle(ImVec2{ mEndPos.x, mEndPos.y } + winPos + offset, 10, 0xff66ff44);

	if (mInitialized)
	{
		auto& best = mGA.GetBestGenome();

		if (!mFounded)
		{
			Vector2 currentPos = mStartPos;
			for (auto& path : mGA.GetBestGenome().chromosome)
			{
				if (path == 0 && currentPos.y >= 20)
					currentPos.y -= 20;
				else if (path == 1 && currentPos.y < 380 - 20)
					currentPos.y += 20;
				else if (path == 2 && currentPos.x >= 20)
					currentPos.x -= 20;
				else if (path == 3 && currentPos.x < 780 - 20)
					currentPos.x += 20;

				drawList->AddCircle(ImVec2{ currentPos.x, currentPos.y } + winPos + offset, 10, 0xff66ff44);
			}

			if (SWAGE::Math::Distance(currentPos, mEndPos) <= 0.00001f)
			{
				mFounded = true;
			}
		}
	}

	ImGui::End();
}
