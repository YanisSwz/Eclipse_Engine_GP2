#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class BoxCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE BoxCollider(bool _isDynamic = false, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f });
		ECLIPSE_ENGINE ~BoxCollider() override;

		Math::Vec3 rotation = { 0.f, 0.f, 0.f };
		Math::Vec3 scale = { 1.f, 1.f, 1.f };

		void Delete() override;
	private:

	};
}