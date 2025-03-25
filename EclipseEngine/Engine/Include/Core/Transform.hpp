#pragma once
#include "Maths.hpp"
#include "Component.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class Transform : Component
	{
	public:
		ECLIPSE_ENGINE Transform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f });

		Math::Vec3 position{ 0.f, 0.f, 0.f };
		Math::Vec3 scale{ 1.f, 1.f, 1.f };
		Math::Quat rotation{ 1.f, 0.f, 0.f };

	private:
		Transform* parent = nullptr;
		std::vector<Transform*> children{};
	};
}