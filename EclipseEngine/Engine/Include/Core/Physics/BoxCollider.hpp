#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class BoxCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE BoxCollider();
		ECLIPSE_ENGINE BoxCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, float _mass = 1.f, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f }, GameObject* _myGameObject = nullptr);
		ECLIPSE_ENGINE ~BoxCollider() override;
		
		ECLIPSE_ENGINE void SetMass(float _mass) override;
		ECLIPSE_ENGINE void SetScale(float _scaleX, float _scaleY, float _scaleZ);
		ECLIPSE_ENGINE void SetScale(Math::Vec3 _scale);
		ECLIPSE_ENGINE void SetPosRotScale(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _scaleX, float _scaleY, float _scaleZ);
		ECLIPSE_ENGINE void SetPosRotScale(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale);
		
		ECLIPSE_ENGINE Math::Vec3 GetScale() const;

	private:
		Math::Vec3 m_scale = { 1.f, 1.f, 1.f };

		void UpdateData();
		void Recreate() override;
	};
}