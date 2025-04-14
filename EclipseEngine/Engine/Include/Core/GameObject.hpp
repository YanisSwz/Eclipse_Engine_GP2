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
		void AddComponent(T* _comp)
		{
			// If argument is not a component, return
			Component* component = dynamic_cast<Component*>(_comp);
			if (component == nullptr)
				return;

			// Check if component inherits from monobehaviour, if so we only check if it's not already in the components list
			MonoBehaviour* castedComponent = dynamic_cast<MonoBehaviour*>(component);
			if (castedComponent != nullptr)
			{
				for (int i = 0; i < m_components.size(); ++i)
				{
					if (component->GetID() == m_components[i]->GetID())
						return;
				}
			}
			// Else, we also check if a component of the same type is already in the list
			else
			{
				for (int i = 0; i < m_components.size(); ++i)
				{
					if (component->GetID() == m_components[i]->GetID())
						return;

					T* testComponent = dynamic_cast<T*>(m_components[i]);
					if (testComponent != nullptr)
						return;
				}
			}
			m_components.emplace_back(_comp);
			_comp->SetGameObject(this);
			return;
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