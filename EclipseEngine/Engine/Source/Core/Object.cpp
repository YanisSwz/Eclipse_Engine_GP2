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
		destroyed = true;
	}

	bool Object::IsDestroyed() const
	{
		return destroyed;
	}

	void Object::SetActive(bool _activate)
	{
		active = _activate;
	}

	bool Object::IsActive() const
	{
		return active;
	}

	void Object::Destroy(Object* _obj)
	{
		_obj->Destroy();
	}
}