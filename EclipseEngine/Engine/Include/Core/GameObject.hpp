#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include "Component.hpp"
#include "Transform.hpp"
#include "MonoBehaviour.hpp"
#include "SystemManager.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class GameObject : public Object
	{
	public:
		ECLIPSE_ENGINE GameObject() = default;
		ECLIPSE_ENGINE GameObject(SystemManager* _manager, Transform* _t = nullptr, std::string _name = "default");
		ECLIPSE_ENGINE ~GameObject();

		std::string name = "";
		Transform* transform = nullptr;

		ECLIPSE_ENGINE static void Destroy(GameObject* _obj);
		ECLIPSE_ENGINE void Destroy() override;

		ECLIPSE_ENGINE std::string GetName() const;
		ECLIPSE_ENGINE static std::string GetName(GameObject* _obj);
		
		template <typename T>
		T* AddComponent()
		{
			m_components.push_back(m_systemManager->AddComponent<T>());
			m_components[m_components.size() - 1]->SetGameObject(this);
			return dynamic_cast<T*>(m_components[m_components.size() - 1]);
		}

		/// <summary>
		/// Returns pointer to first component of specified type, nullptr otherwise
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T> 
		T* GetComponent()
		{
			//TODO OPTIMIZATION: check if T is a component
			for(int i = 0; i < m_components.size(); ++i)
			{
				T* castedComponent = dynamic_cast<T*>(m_components[i]);
				if (castedComponent != nullptr)
					return castedComponent;
			}
			return nullptr;
		}

		template <typename T>
		void RemoveComponent(T* _compAdress)
		{
			// If argument is not a component, return
			Component* component = dynamic_cast<Component*>(_compAdress);
			if (component == nullptr)
				return;

			for (int i = 0; i < m_components.size(); ++i)
			{
				if (m_components[i] == _compAdress)
				{
					// Mark to be destroyed and remove it from components list
					if(!m_components[i]->IsDestroyed())
						m_components[i]->Destroy();
					m_components.erase(m_components.begin() + i);
					return;
				}
			}
		}

	private:
		std::vector<Component*> m_components{};
		SystemManager* m_systemManager = nullptr;
	};
}