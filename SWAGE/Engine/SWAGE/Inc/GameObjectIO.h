#pragma once

namespace SWAGE
{
	class GameObject;

	namespace GameObjectIO
	{
		void Write(FILE* file, const GameObject& gameObject);
		void Read(FILE* file, GameObject& gameObject);
	}
}