#include "Scene.hpp"

namespace Core
{
	Transform* Scene::AddTransform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		return transformSystem.Add(_translation, _rotation, _scale);
	}
}