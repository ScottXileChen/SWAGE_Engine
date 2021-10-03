#pragma once

#include "Common.h"

// APP headers
#include "App.h"
#include "AppState.h"

// Components headers
#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "MinionComponent.h"
#include "ModelComponent.h"
#include "SpawnerComponent.h"
#include "WeaponComponent.h"
#include "TransformComponent.h"

// Service headers
#include "EnemyService.h"
#include "RenderService.h"

// Utils headers
#include "GUIUtil.h"

// World headers
#include "Component.h"
#include "GameObject.h"
#include "GameObjectHandle.h"
#include "GameObjectIO.h"
#include "GameWorld.h"
#include "Service.h"

namespace SWAGE
{
	App& MainApp();
}