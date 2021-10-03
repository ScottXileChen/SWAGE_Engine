#include "Precompiled.h"
#include "PerceptionModule.h"

using namespace SWAGE::AI::Perception;

PerceptionModule::PerceptionModule(Agent & agent, ImportanceCalculator calculator)
	:mAgent(agent),
	ComputeImportance(std::move(calculator))
{
}

void PerceptionModule::Update(float deltaTime)
{
	// Update sensors and refresh/add memory records
	for (auto& sensor : mSensors)
		sensor->Update(mAgent, mMemory, deltaTime);

	// Remove any records that are too old
	mMemory.erase(std::remove_if(mMemory.begin(), mMemory.end(), [span = mMemorySpan](const auto& record) {
		return record.lastRecordedTime + span < SWAGE::Core::TimeUtil::GetTime();
	}), mMemory.end());

	// Calculate importance on remaining records
	for (auto& record : mMemory)
		record.importance = ComputeImportance(mAgent, record);

	// Sort record by importance
	mMemory.sort([](const auto& a, const auto& b)
	{
		return a.importance > b.importance;
	});
}