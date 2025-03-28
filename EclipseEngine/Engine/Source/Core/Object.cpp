#include "Object.hpp"

namespace Core
{
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