#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include "Component.hpp"
#include "Transform.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class Scene;

	class GameObject : public Object
	{
	public:
		ECLIPSE_ENGINE GameObject() = default;
		ECLIPSE_ENGINE GameObject(std::string _name);
		ECLIPSE_ENGINE ~GameObject();

		ECLIPSE_ENGINE static void Destroy(GameObject* _obj);
		ECLIPSE_ENGINE void Destroy() override;
		ECLIPSE_ENGINE static GameObject* Instantiate(GameObject _original);

		ECLIPSE_ENGINE std::string GetName() const;
		ECLIPSE_ENGINE static std::string GetName(GameObject* _obj);

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

		template <typename T>
		void AddComponent(T* _comp)
		{
			for (int i = 0; i < m_components.size(); ++i)
			{
				if (typeid(m_components[i]) == typeid(_comp))
					return;
			}
			m_components.emplace_back(_comp);
			_comp->SetGameObject(this);
		}

		template <typename T>
		void UpdateComponentLocation(T* _compAdress)
		{
			for (int i = 0; i < m_components.size(); ++i)
			{
				T* castedComponent = dynamic_cast<T*>(m_components[i]);
				if (castedComponent != nullptr)
				{
					m_components[i] = _compAdress;
					return;
				}
			}
		}

	private:
		std::string m_name = "";
		Transform transform{};
		std::vector<Component*> m_components;
		Scene* scene{};
	};
}