#include "Object.hpp"

namespace Core
{
	int Object::idCount = 0;

	Object::Object()
	{
		m_id = idCount;
		++idCount;
	}

	int Object::GetID() const
	{
		return m_id;
	}

	void Object::Destroy()
	{
		m_active = false;
		m_destroyed = true;
	}

	bool Object::IsDestroyed() const
	{
		return m_destroyed;
	}

	void Object::SetActive(bool _activate)
	{
		m_active = _activate;
	}

	bool Object::IsActive() const
	{
		return m_active;
	}

	bool& Object::GetActiveRef()
	{
		return m_active;
	}

	void Object::Destroy(Object* _obj)
	{
		_obj->Destroy();
	}
}