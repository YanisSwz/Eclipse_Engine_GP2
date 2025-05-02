#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class BoxCollider : public ICollider
	{
	public:
		static meta::factory<BoxCollider> factory;

		ECLIPSE_ENGINE BoxCollider();
		ECLIPSE_ENGINE BoxCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false,
			float _mass = 1.f, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f },
			Math::Vec3 _rot = { 0.f, 0.f, 0.f }, GameObject* _myGameObject = nullptr,
			Math::Vec3 _linearVelocity = { 0.f, 0.f, 0.f }, Math::Vec3 _angularVelocity = { 0.f, 0.f, 0.f });
		ECLIPSE_ENGINE ~BoxCollider() override;
		
		ECLIPSE_ENGINE void SetMass(float _mass) override;
		ECLIPSE_ENGINE void Scale(float _scaleX, float _scaleY, float _scaleZ) override;
		ECLIPSE_ENGINE void Scale(Math::Vec3 _scale) override;

	private:
		void UpdateData();
		void Recreate() override;
	};

	void to_json(json& _j, const BoxCollider& _boxCollider);
	void from_json(const json& _j, BoxCollider& _boxCollider);
}