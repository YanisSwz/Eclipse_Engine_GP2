#pragma once
#include "ProjectExports.hpp"
#include "ISerializable.hpp"

namespace Core
{
	class Object : public ISerializable
	{
	public:
		ECLIPSE_ENGINE Object();
		ECLIPSE_ENGINE virtual ~Object() = default;

		ECLIPSE_ENGINE virtual void Destroy();
		ECLIPSE_ENGINE bool IsDestroyed() const;
		ECLIPSE_ENGINE void SetActive(bool _activate);
		ECLIPSE_ENGINE bool IsActive() const;
		ECLIPSE_ENGINE static void Destroy(Object* _obj);
		ECLIPSE_ENGINE int GetID() const;

	protected:
		static int idCount;
		int m_id = -1;
		bool m_active = false;
		bool m_destroyed = false;
	};
}