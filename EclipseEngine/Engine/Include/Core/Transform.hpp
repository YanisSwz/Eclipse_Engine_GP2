#pragma once
#include "Maths.hpp"
#include "Component.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class Transform : public Component
	{
	public:
		ECLIPSE_ENGINE Transform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f });
		ECLIPSE_ENGINE ~Transform();
		ECLIPSE_ENGINE void SetParent(Transform* _parent);
		ECLIPSE_ENGINE inline Transform* GetParent() const { return m_parent; };
		ECLIPSE_ENGINE void AddChild(Transform* _child);
		ECLIPSE_ENGINE inline std::vector<Transform*> GetChildren() const { return m_children; };
		ECLIPSE_ENGINE void Update();

		// Global position
		Math::Vec3 position{ 0.f, 0.f, 0.f };
		// Global scale
		Math::Vec3 scale{ 1.f, 1.f, 1.f };
		// Global rotation
		Math::Quat rotation{ 1.f, 0.f, 0.f, 0.f };

		Math::Vec3 localPosition{ 0.f, 0.f, 0.f };
		Math::Vec3 localScale{ 1.f, 1.f, 1.f };
		Math::Quat localRotation{ 1.f, 0.f, 0.f, 0.f };

	private:
		Transform* m_parent = nullptr;
		std::vector<Transform*> m_children{};
	};
}