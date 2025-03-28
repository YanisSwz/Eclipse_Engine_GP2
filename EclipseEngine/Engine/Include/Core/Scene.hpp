#pragma once
#include <vector>
#include "GameObject.hpp"
#include "MonoBehaviour.hpp"
#include "ProjectExports.hpp"

namespace Core
{

	class ComponentArray
	{
	public:
		ComponentArray() = default;
		virtual ~ComponentArray() = default;

		virtual void Sort() = 0;
		virtual void Swap(Component* _obj1, Component*) = 0;

	protected:
		int currentActiveCount = 0;
	};

	class MonoBehaviourArray : public ComponentArray
	{
	public: 
		ECLIPSE_ENGINE MonoBehaviourArray() = default;
		ECLIPSE_ENGINE ~MonoBehaviourArray() = default;

		ECLIPSE_ENGINE void Sort() override;
		ECLIPSE_ENGINE void Swap(Component* _obj1, Component*) override;

	private:
		std::vector<MonoBehaviour> data;
	};

	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;

		MonoBehaviourArray scriptsArray;

	private:
		GameObject* root = nullptr;
		

	};
}