#include "Precompiled.h"
#include "GameObjectIO.h"

#include "GameObject.h"

#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "MinionComponent.h"
#include "ModelComponent.h"
#include "SpawnerComponent.h"
#include "WayPointPathComponent.h"
#include "WeaponComponent.h"
#include "TransformComponent.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

using namespace rapidjson;
using namespace SWAGE;

void GameObjectIO::Write(FILE * file, const GameObject & gameObject)
{

}

void GameObjectIO::Read(FILE * file, GameObject & gameObject)
{
	char readBuffer[65536];
	FileReadStream readStream(file, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(readStream);

	document.HasMember("Components");

	auto components = document["Components"].GetObj();
	for (auto& component : components)
	{
		const char* componentName = component.name.GetString();
		if (strcmp(component.name.GetString(), "TransformComponent") == 0)
		{
			auto transform = gameObject.AddComponent<TransformComponent>();
			if (component.value.HasMember("Position"))
			{
				const auto& position = component.value["Position"].GetArray();
				float x = position[0].GetFloat();
				float y = position[1].GetFloat();
				float z = position[2].GetFloat();
				transform->SetPosition({ x, y, z });
			}
		}
		else if (strcmp(component.name.GetString(), "ColliderComponent") == 0)
		{
			auto collider = gameObject.AddComponent<ColliderComponent>();
			if (component.value.HasMember("Center"))
			{
				const auto& center = component.value["Center"].GetArray();
				float x = center[0].GetFloat();
				float y = center[1].GetFloat();
				float z = center[2].GetFloat();
				collider->SetCenter({ x, y, z });
			}
			if (component.value.HasMember("Extend"))
			{
				const auto& extend = component.value["Extend"].GetArray();
				float x = extend[0].GetFloat();
				float y = extend[1].GetFloat();
				float z = extend[2].GetFloat();
				collider->SetExtend({ x, y, z });
			}
		}
		else if (strcmp(component.name.GetString(), "ModelComponent") == 0)
		{
			auto model = gameObject.AddComponent<ModelComponent>();
			if (component.value.HasMember("File Name"))
			{
				const auto& fileName = component.value["File Name"].GetString();
				model->SetFileName(fileName);
			}
		}
		else if (strcmp(component.name.GetString(), "AnimatorComponent") == 0)
		{
			auto animator = gameObject.AddComponent<AnimatorComponent>();
		}
		else if (strcmp(component.name.GetString(), "SpawnerComponent") == 0)
		{
			auto spawner = gameObject.AddComponent<SpawnerComponent>();
			if (component.value.HasMember("Template File Name"))
			{
				const auto& templateFileName = component.value["Template File Name"].GetString();
				spawner->SetTemplateFileName(templateFileName);
			}
			if (component.value.HasMember("Spawn Object Name"))
			{
				const auto& objectName = component.value["Spawn Object Name"].GetString();
				spawner->SetSpawnObjectName(objectName);
			}
			if (component.value.HasMember("Spawn Count"))
			{
				const auto& spawnCount = component.value["Spawn Count"].GetInt();
				spawner->SetSpawnCount(spawnCount);
			}
			if (component.value.HasMember("Spawn Wait Time"))
			{
				const auto& spawnWaitTime = component.value["Spawn Wait Time"].GetFloat();
				spawner->SetSpawnWaitTime(spawnWaitTime);
			}
			if (component.value.HasMember("Max Count"))
			{
				const auto& maxCount = component.value["Max Count"].GetInt();
				spawner->SetMaxCount(maxCount);
			}
		}
		else if (strcmp(component.name.GetString(), "WayPointPathComponent") == 0)
		{
			auto wayPointPath = gameObject.AddComponent<WayPointPathComponent>();
			if (component.value.HasMember("Path"))
			{
				const auto& path = component.value["Path"].GetArray();
				std::vector<Math::Vector3> newPath;
				newPath.reserve(path.Size());
				for (Value::ConstValueIterator posItr = path.Begin(); posItr != path.end(); ++posItr)
				{
					const auto& pos = posItr->GetArray();
					Math::Vector3 newPos = Math::Vector3::Zero;
					for (Value::ConstValueIterator valItr = pos.Begin(); valItr != pos.end(); ++valItr)
					{
						newPos.x = valItr->GetFloat();
						++valItr;
						newPos.y = valItr->GetFloat();
						++valItr;
						newPos.z = valItr->GetFloat();
					}
					newPath.push_back(newPos);
				}
				wayPointPath->SetWayPointPath(newPath);
			}
		}
		else if (strcmp(component.name.GetString(), "MinionComponent") == 0)
		{
			auto minion = gameObject.AddComponent<MinionComponent>();
			if (component.value.HasMember("Move Speed"))
			{
				const auto& moveSpeed = component.value["Move Speed"].GetFloat();
				minion->SetMoveSpeed(moveSpeed);
			}
		}
		else if (strcmp(component.name.GetString(), "WeaponComponent") == 0)
		{
			auto weapon = gameObject.AddComponent<WeaponComponent>();
			if (component.value.HasMember("Move Speed"))
			{
				const auto& moveSpeed = component.value["Move Speed"].GetFloat();
				weapon->SetMoveSpeed(moveSpeed);
			}
		}
	}
}
