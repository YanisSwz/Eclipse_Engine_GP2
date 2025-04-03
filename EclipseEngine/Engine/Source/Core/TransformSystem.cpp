#include "TransformSystem.hpp"

namespace Core 
{
	Transform* TransformSystem::Add(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		if (currentCount >= MAX_SIZE)
			return nullptr;

		data[currentCount] = Transform(_translation, _rotation, _scale);
		++currentCount;
		return &data[currentCount];
	}
}