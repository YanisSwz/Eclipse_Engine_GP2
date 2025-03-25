#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include "Component.hpp"
#include "Transform.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class GameObject
	{
	public:
		ECLIPSE_ENGINE GameObject() = default;
		ECLIPSE_ENGINE GameObject(std::string _name);
		ECLIPSE_ENGINE ~GameObject();

		/// <summary>
		/// Destroys game object or component. DO NOT use if object was not dynamically allocated
		/// </summary>
		/// <param name="_obj:"> a pointer to an object that was dynamically allocated.</param>
		/// <returns></returns>
		ECLIPSE_ENGINE static void Destroy(GameObject* _obj);
		ECLIPSE_ENGINE static GameObject* Instantiate(GameObject _original);

		ECLIPSE_ENGINE std::string GetName() const;
		ECLIPSE_ENGINE static std::string GetName(GameObject* _obj);
		ECLIPSE_ENGINE int GetID() const;
		ECLIPSE_ENGINE static int GetID(GameObject* _obj);

		ECLIPSE_ENGINE void AddComponent(Component* _comp);

		template <typename T> 
		T* GetComponent()
		{
			for(int i = 0; i < m_components.size(); ++i)
			{
				T* castedComponent = dynamic_cast<T*>(m_components[i]);
				if (castedComponent != nullptr)
					return castedComponent;
			}
			return nullptr;
		}

	private:
		void Destroy();
		std::string m_name = "";
		int m_id = -1;
		std::vector<Component*> m_components;
		Transform transform{};
		//TODO: scene
	};
}