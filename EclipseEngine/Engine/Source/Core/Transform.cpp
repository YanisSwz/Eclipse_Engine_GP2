#include "Transform.hpp"

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		position = _translation;
		rotation = Math::Quat::s_QuaternionEuler(_rotation);
		scale = _scale;
	}
}