#include "Core/Camera/Camera.hpp"
#include "GameObject.hpp"
#include "Maths.hpp"

namespace Core
{
	Camera::Camera(float _fov, float _near, float _far)
		: m_fov(_fov), m_near(_near), m_far(_far)
	{
	}

	void Camera::SetFOV(float _fov)
	{
		if (_fov < 0.f || _fov > 180.f)
			return;
		m_fov = _fov;
	}

	void Camera::SetNear(float _near)
	{
		if (_near < 0.1f)
		{
			m_near = 0.1f;
			return;
		}

		m_near = _near;

		if (m_near >= m_far)
			m_far = m_near + 0.01f;
	}

	void Camera::SetFar(float _far)
	{
		if (_far < m_near)
			return;

		if (_far <= 0.2f)
		{
			m_far = 0.2f;
			return;
		}

		m_far = _far;		
	}

	float Camera::GetFOV()
	{
		return m_fov;
	}

	float Camera::GetNear()
	{
		return m_near;
	}

	float Camera::GetFar()
	{
		return m_far;
	}

	Math::Mat4 Camera::GetViewMatrix() const
	{
		Math::Vec3 pos = m_gameObject->transform->GetPosition();
		Math::Vec3 dir = m_gameObject->transform->GetForward();
		Math::Vec3 up = m_gameObject->transform->GetUp();
		return Math::Mat4::ViewMatrix(pos, pos + dir, up);
	}

	Math::Mat4 Camera::GetProjectionMatrix(int _width, int _height) const
	{
		return Math::Mat4::PerspectiveMatrix(_width, _height, m_fov, m_near, m_far);
	}

	Math::Mat4 Camera::GetViewProjectionMatrix(int _width, int _height) const
	{
		return GetViewMatrix() * GetProjectionMatrix(_width, _height);
	}

	void Camera::SetCurrentCamera() 
	{
		m_gameObject->GetSystemManager()->GetCameraSystem()->SetCurrentCamera(this);
	}
}