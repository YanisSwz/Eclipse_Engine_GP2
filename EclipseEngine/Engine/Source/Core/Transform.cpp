#include "Transform.hpp"

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		position = _translation;
		rotation = Math::Quat::s_QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		scale = _scale;
	}

	Transform::~Transform(){}

	void Transform::Destroy()
	{
	}
}