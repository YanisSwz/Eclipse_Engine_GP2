#pragma once
#include "ProjectExports.hpp"

namespace Core
{
	class Object
	{
	public:
		ECLIPSE_ENGINE Object() = default;
		ECLIPSE_ENGINE virtual ~Object() = default;

		ECLIPSE_ENGINE virtual void Destroy();
		ECLIPSE_ENGINE bool IsDestroyed() const;
		ECLIPSE_ENGINE void SetActive(bool _activate);
		ECLIPSE_ENGINE bool IsActive() const;
		ECLIPSE_ENGINE static void Destroy(Object* _obj);

	protected:
		bool active = false;
		bool destroyed = false;
	};
}