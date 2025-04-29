#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class CapsuleCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE CapsuleCollider();
		ECLIPSE_ENGINE CapsuleCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, 
			float _mass = 1.f, Math::Vec3 _scale = {1.f, 1.f, 1.f}, Math::Vec3 _pos = {0.f, 0.f, 0.f}, 
			Math::Vec3 _rot = {0.f, 0.f, 0.f}, GameObject* _myGameObject = nullptr,
			Math::Vec3 _linearVelocity = {0.f, 0.f, 0.f}, Math::Vec3 _angularVelocity = {0.f, 0.f, 0.f});
		ECLIPSE_ENGINE ~CapsuleCollider() override;

		ECLIPSE_ENGINE void SetMass(float _mass) override;
		ECLIPSE_ENGINE void Scale(float _scaleX, float _scaleY, float _scaleZ) override;
		ECLIPSE_ENGINE void Scale(Math::Vec3 _scale) override;

	private:
		
		void Recreate() override;
	};
}