#pragma once
#include "Transform.hpp"
#include "ProjectExports.hpp"

namespace Core 
{
	class TransformSystem
	{
	public:
		ECLIPSE_ENGINE TransformSystem();
		ECLIPSE_ENGINE ~TransformSystem() = default;
		ECLIPSE_ENGINE Transform* Add(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE void Update();

	private:
		static const int MAX_SIZE = 100;
		int m_currentCount = 0;
		Transform* m_root = nullptr;
		Transform m_data[MAX_SIZE];

	};
}