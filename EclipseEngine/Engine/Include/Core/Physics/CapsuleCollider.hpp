#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class CapsuleCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE CapsuleCollider();
		ECLIPSE_ENGINE CapsuleCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, float _height = 1.f, float _radius = 0.5f, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f });
		ECLIPSE_ENGINE ~CapsuleCollider() override;

		ECLIPSE_ENGINE void SetRotation(float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetRotation(Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetHeight(float _height);
		ECLIPSE_ENGINE void SetRadius(float _radius);
		ECLIPSE_ENGINE void SetHeightRadius(float _height, float _radius);
		ECLIPSE_ENGINE void SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetPosRotHeightRadius(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _height, float _radius);
		ECLIPSE_ENGINE void SetPosRotHeightRadius(Math::Vec3 _position, Math::Vec3 _rotation, float _height, float _radius);
		ECLIPSE_ENGINE Math::Quat GetRotation() const;
		ECLIPSE_ENGINE float GetHeight() const;
		ECLIPSE_ENGINE float GetRadius() const;

		ECLIPSE_ENGINE void Delete() override;

	private:
		float m_height = 1.f;
		float m_radius = 0.5f;
		Math::Quat m_rotation = { 0.f, 0.f, 0.f };

		void UpdateData();
	};
}