#pragma once
#include "Component.hpp"

namespace Math
{
	class Mat4;
	class Vec3;
}

namespace Core
{
	class Camera : public Component
	{
	public:
		ECLIPSE_ENGINE Camera(float _fov = 60.f, float _near = 0.1f, float _far = 1000.f);
		ECLIPSE_ENGINE ~Camera() = default;

		ECLIPSE_ENGINE void SetFOV(float _fov);
		ECLIPSE_ENGINE void SetNear(float _near);
		ECLIPSE_ENGINE void SetFar(float _far);

		ECLIPSE_ENGINE float GetFOV() const;
		ECLIPSE_ENGINE float GetNear() const;
		ECLIPSE_ENGINE float GetFar() const;
		ECLIPSE_ENGINE Math::Vec3 GetViewPos() const;

		ECLIPSE_ENGINE Math::Mat4 GetViewMatrix() const;
		ECLIPSE_ENGINE Math::Mat4 GetProjectionMatrix(int _width, int _height) const;
		ECLIPSE_ENGINE Math::Mat4 GetViewProjectionMatrix(int _width, int _height) const;

		ECLIPSE_ENGINE void SetCurrentCamera();
		ECLIPSE_ENGINE bool IsCurrentCamera() const;
		
		ECLIPSE_ENGINE void Destroy() override;

	private:
		float m_fov;
		float m_near;
		float m_far;
	};
}