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

		virtual void Sync() = 0;
		virtual void Sort() = 0;
		virtual void Swap(Component* _obj1, Component* _obj2) = 0;

	protected:
		// First inactive index
		int currentActiveCount = 0;
		// Total components count
		int currentCount = 0;
		static const int MAX_SIZE = 100;
	};

	class MonoBehaviourArray : public ComponentArray
	{
	public: 
		ECLIPSE_ENGINE MonoBehaviourArray() = default;
		ECLIPSE_ENGINE ~MonoBehaviourArray() = default;

		/// <summary>
		/// Function that updates destroyed components pointers
		/// </summary>
		/// <returns></returns>
		ECLIPSE_ENGINE void Sync() override;
		/// <summary>
		/// Function that sorts active and inactive components and updates components pointers
		/// </summary>
		/// <returns></returns>
		ECLIPSE_ENGINE void Sort() override;
		ECLIPSE_ENGINE void Swap(Component* _obj1, Component* _obj2) override;
		ECLIPSE_ENGINE void Add(Component* _comp);
		ECLIPSE_ENGINE void Update();

	private:
		MonoBehaviour data[MAX_SIZE];
	};

	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;

		MonoBehaviourArray scriptsArray;

	private:
		GameObject* m_root = nullptr;
		GameObject* m_currentGameObject = nullptr;

	};
}