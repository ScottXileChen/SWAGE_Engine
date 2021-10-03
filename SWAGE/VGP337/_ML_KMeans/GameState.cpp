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

	// For Game
	bool drawClusterResultUI = false;
	bool spacePressed = false;

	int centroidSize = 3;

	struct ClusterResult
	{
		std::vector<Vector3> centroids;
		std::vector<int> assignment;
		std::vector<std::vector<Vector3>> centroidsHistory;
	};

	ClusterResult result;

	bool CompareTwoVector3(const std::vector<Vector3>& lhs, const std::vector<Vector3>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i].x != rhs[i].x
				|| lhs[i].y != rhs[i].y
				|| lhs[i].z != rhs[i].z)
			{
				return false;
			}
		}

		return true;
	}

	ClusterResult KMeansCluster(const std::vector<Vector3>& data, size_t k, size_t maxIteration)
	{
		ASSERT(k <= data.size(), "Not enough data for %zu clusters!", k);

		ClusterResult clusterResult;

		// Use existing data points as starting cluster centroids
		clusterResult.centroids.resize(k);
		clusterResult.centroidsHistory.resize(maxIteration);
		for (size_t i = 0; i < k; ++i)
			clusterResult.centroids[i] = data[i];

		for (size_t iteration = 0; iteration < maxIteration; ++iteration)
		{
			std::vector<Vector3> newCentroids;
			std::vector<size_t> clusterEntryCount;
			newCentroids.resize(k);
			clusterEntryCount.resize(k);

			// Assign cluster membership
			clusterResult.assignment.clear();
			clusterResult.assignment.reserve(data.size());

			for (const auto& sample : data)
			{
				size_t closestClusterIndex = 0;
				float closestDistanceSqr = DistanceSqr(sample, clusterResult.centroids[0]);
				for (size_t i = 1; i < clusterResult.centroids.size(); ++i)
				{
					const float distanceSqr = DistanceSqr(sample, clusterResult.centroids[i]);
					if (distanceSqr < closestDistanceSqr)
					{
						closestClusterIndex = i;
						closestDistanceSqr = distanceSqr;
					}
				}
				clusterResult.assignment.push_back((int)closestClusterIndex);
				newCentroids[closestClusterIndex] += sample;
				clusterEntryCount[closestClusterIndex]++;
			}

			// Compute new centroids
			for (size_t i = 0; i < clusterResult.centroids.size(); ++i)
				newCentroids[i] /= static_cast<float>(clusterEntryCount[i]);

			// Check if we are done
			if (CompareTwoVector3(newCentroids, clusterResult.centroids))
				break;

			for (size_t i = 0; i < clusterResult.centroids.size(); ++i)
				clusterResult.centroidsHistory[i].push_back(clusterResult.centroids[i]);

			// Update centroid positions and repeat
			clusterResult.centroids = std::move(newCentroids);
		}

		return clusterResult;
	}
}

void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Black);

	mUnitTexture.Initialize(L"../../Assets/Images/scv_01.png");

	for (size_t i = 0; i < 50; ++i)
	{
		float px = RandomFloat(0.0f, 800.0f);
		float py = RandomFloat(0.0f, 800.0f);
		float vx = RandomFloat(-100.0f, 100.0f);
		float vy = RandomFloat(-100.0f, 100.0f);
		mUnits.emplace_back(Unit{ {px, py}, { vx, vy } });
	}
}

void GameState::Terminate()
{
	mUnitTexture.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	if (inputSystem->IsKeyPressed((KeyCode::SPACE)))
	{
		drawClusterResultUI = !drawClusterResultUI;
		spacePressed = true;
	}

	if (!drawClusterResultUI)
	{
		for (auto& unit : mUnits)
		{
			unit.position += unit.velocity * deltaTime;
				if (unit.position.x < 0.0f)
					unit.position.x += 800.0f;
			if (unit.position.x > 800.0f)
				unit.position.x -= 800.0f;
			if (unit.position.y < 0.0f)
				unit.position.y += 600.0f;
			if (unit.position.y > 600.0f)
				unit.position.y -= 600.0f;
		}
	}
}

void GameState::DebugUI()
{
	ImGui::SetNextWindowSize({ 800.0f, 600.0f });
	ImGui::Begin("game", nullptr, ImGuiWindowFlags_NoResize);

	ImVec2 unitSize = ImVec2(32.0f, 32.0f);
	for (auto& unit : mUnits)
	{
		ImGui::SetCursorPos(unit.position - (unitSize * 0.5f));
		ImGui::Image(mUnitTexture.GetRawData(), unitSize);
	}

	ImVec2 winPos = ImGui::GetWindowPos();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	//drawList->AddCircle(winPos + mUnits[0].position, 50.0f, 0xff0000ff);

	// Run KMeans
	std::vector<Vector3> positions;
	if (spacePressed)
	{
		for (auto& unit : mUnits)
		{
			positions.emplace_back(Vector3{ unit.position.x, unit.position.y, 0.0f });
		}
		result = KMeansCluster(positions, centroidSize, 300);
		spacePressed = false;
	}
	if (drawClusterResultUI)
	{
		const ImU32 clusterColors[] = { 0xffff8800, 0xff66ff44, 0xffff22ff };
		for (size_t i = 0; i < result.centroids.size(); ++i)
		{
			ImVec2 center{ result.centroids[i].x, result.centroids[i].y };
			drawList->AddCircleFilled(winPos + center, 10.0f, clusterColors[i] | 0xff808080);
		}

		for (size_t i = 0; i < result.assignment.size(); ++i)
		{
			size_t clusterIndex = result.assignment[i];
			Vector3 centroid = result.centroids[clusterIndex];
			ImVec2 center{ centroid.x, centroid.y };
			drawList->AddLine(winPos + center, winPos + mUnits[i].position, clusterColors[clusterIndex] | 0xff808080);
		}

		for (size_t i = 0; i < result.centroidsHistory.size(); ++i)
		{
			float radius = 2.0f;
			for (size_t j = 0; j < result.centroidsHistory[i].size(); ++j)
			{
				auto& history = result.centroidsHistory[i][j];
				drawList->AddCircleFilled(winPos + ImVec2{ history.x, history.y }, radius, clusterColors[i]);
				if (radius < 10.0f)
					radius += 1.0f;
				if (j > 0)
				{
					auto& lastHistory = result.centroidsHistory[i][j - 1];
					drawList->AddLine(winPos + ImVec2{ history.x, history.y }, winPos + ImVec2{ lastHistory.x,lastHistory.y }, 0xffffffff);
				}
			}
		}
	}

	ImGui::End();

	ImGui::Begin("Test");

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

	ImGui::SliderInt("Centroid size:", &centroidSize, 3, 8);
	ImGui::End();

}
