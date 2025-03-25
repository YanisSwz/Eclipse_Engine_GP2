#pragma once
#include "ProjectExports.hpp"

namespace Core
{
	class GameObject;

	class Component
	{
	public:
		ECLIPSE_ENGINE Component() = default;
		ECLIPSE_ENGINE virtual ~Component();

		virtual void Destroy() = 0;
		ECLIPSE_ENGINE virtual void SetGameObject(GameObject* _obj);

	private:
		GameObject* m_gameObject = nullptr;
	};
}