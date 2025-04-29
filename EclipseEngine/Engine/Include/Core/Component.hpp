#pragma once
#include "ProjectExports.hpp"
#include "Object.hpp"

namespace Core
{
	class GameObject;

	class Component : public Object
	{
	public:
		ECLIPSE_ENGINE Component() = default;
		ECLIPSE_ENGINE virtual ~Component() = default;

		ECLIPSE_ENGINE void SetGameObject(GameObject* _obj);
		ECLIPSE_ENGINE GameObject* GetGameObject() const { return m_gameObject; };
		ECLIPSE_ENGINE void Remove();
		ECLIPSE_ENGINE virtual void SetActive(bool _activate) override;

	protected:
		GameObject* m_gameObject = nullptr;
	};
}