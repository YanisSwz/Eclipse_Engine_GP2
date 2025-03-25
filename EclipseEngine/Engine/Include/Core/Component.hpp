#pragma once
#include "GameObject.hpp"

namespace Core
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = 0;

		virtual void Destroy() = 0;
		virtual void SetGameObject(GameObject* _obj);

	private:
		GameObject* m_gameObject = nullptr;
	};
}