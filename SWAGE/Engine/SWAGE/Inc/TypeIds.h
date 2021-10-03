#pragma once

#include "Common.h"

namespace SWAGE
{
	enum ComponentId
	{
		Collider,
		Transform,
		Model,
		Animator,
		Spawner,
		WayPointPath,
		Minion,
		Tower,
		Weapon
	};

	enum ServiceId
	{
		Render,
		Enemy
	};

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() { return id; }\
	uint32_t GetTypeId() const override { return id; }
}