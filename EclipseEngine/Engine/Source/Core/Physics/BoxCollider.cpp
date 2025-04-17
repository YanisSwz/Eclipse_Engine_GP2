#include "Physics/BoxCollider.hpp"

namespace Core
{
	BoxCollider::BoxCollider(bool _isDynamic, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot)
	{
		b_isDynamic = _isDynamic;
		position = _pos;
		scale = _size;
		rotation = _rot;
	}

	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::Delete()
	{

	}
}