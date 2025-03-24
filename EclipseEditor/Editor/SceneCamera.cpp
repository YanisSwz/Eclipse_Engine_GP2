#include "SceneCamera.hpp"
#include <iostream>
using namespace Core;

SceneCamera::SceneCamera(float _fov, float _near, float _far)
{
	m_fov = _fov;
	m_near = _near;
	m_far = _far;
}

void SceneCamera::Update(Windowing::IWindow* _window, float _deltaTime, Math::Vec2 _sceneWindowPos, Math::Vec2 _sceneWindowSize)
{
	m_width = _window->width;
	m_height = _window->height;
	UpdateInput(_window, _deltaTime, _sceneWindowPos, _sceneWindowSize);
}

void SceneCamera::UpdateInput(Windowing::IWindow* _window, float _deltaTime, Math::Vec2 _sceneWindowPos, Math::Vec2 _sceneWindowSize)
{
	Math::Vec2 cursorPos = _window->GetCursorPos();
	if (!_window->GetMouseButton(Windowing::MOUSE_CODE::RIGHT_BUTTON, Windowing::INPUT_ACTION::INPUT_DOWN) || cursorPos.x < _sceneWindowPos.x || cursorPos.x > _sceneWindowSize.x || cursorPos.y < _sceneWindowPos.y || cursorPos.y > _sceneWindowSize.y)
	{
		_window->SetCursorMode(Windowing::CURSOR_MODE::CURSOR_VISIBLE);
		return;
	}

	InputChangeSpeed(_window);
	InputMove(_window, _deltaTime);

	if (_window->GetMouseButton(Windowing::MOUSE_CODE::RIGHT_BUTTON, Windowing::INPUT_ACTION::INPUT_PRESS))
	{
		m_oldMouse = _window->GetCursorPos();
	}
	else if (_window->GetMouseButton(Windowing::MOUSE_CODE::RIGHT_BUTTON, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		_window->SetCursorMode(Windowing::CURSOR_MODE::CURSOR_DISABLED);
		InputRotation(_window, _deltaTime);
		_window->SetCursorPos(m_oldMouse);
	}
	else if (_window->GetMouseButton(Windowing::MOUSE_CODE::RIGHT_BUTTON, Windowing::INPUT_ACTION::INPUT_RELEASE))
	{
		_window->SetCursorPos(m_oldMouse);
		_window->SetCursorMode(Windowing::CURSOR_MODE::CURSOR_VISIBLE);
	}
}

void Core::SceneCamera::InputChangeSpeed(Windowing::IWindow* _window)
{
	if (_window->GetMouseButton(Windowing::MOUSE_CODE::RIGHT_BUTTON, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		m_speedMove += (m_increaseSpeedValue * _window->GetMouseScrollValue());
		if (m_speedMove > m_maxSpeed)
			m_speedMove = m_maxSpeed;
		else if (m_speedMove < m_minSpeed)
			m_speedMove = m_minSpeed;
	}
}

void SceneCamera::InputMove(Windowing::IWindow* _window, float _deltaTime)
{
	Math::Vec3 move;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_W, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 direction{ m_at, m_eye };
		direction.Normalize();
		move += direction * _deltaTime * m_speedMove;
	}
	if (_window->GetKey(Windowing::KEY_CODE::KEY_S, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 direction{ m_eye, m_at };
		direction.Normalize();
		move += direction * _deltaTime * m_speedMove;
	}
	if (_window->GetKey(Windowing::KEY_CODE::KEY_D, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 frwd = { m_at, m_eye };
		Math::Vec3 direction = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(frwd, m_up));
		move += direction * _deltaTime * m_speedMove;
	}
	if (_window->GetKey(Windowing::KEY_CODE::KEY_A, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 frwd = { m_at, m_eye };
		Math::Vec3 direction = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(frwd, m_up));
		move -= direction * _deltaTime * m_speedMove;
	}
	if (_window->GetKey(Windowing::KEY_CODE::KEY_E, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 frwd = Math::Vec3::s_Normalized({ m_at, m_eye });
		Math::Vec3 right = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(frwd, m_up));
		Math::Vec3 _up = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(right, frwd));

		Math::Vec3 direction = _up;
		move += direction * _deltaTime * m_speedMove;
	}
	if (_window->GetKey(Windowing::KEY_CODE::KEY_Q, Windowing::INPUT_ACTION::INPUT_DOWN))
	{
		Math::Vec3 frwd = Math::Vec3::s_Normalized({ m_at, m_eye });
		Math::Vec3 right = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(frwd, m_up));
		Math::Vec3 _up = Math::Vec3::s_Normalized(Math::Vec3::s_CrossProduct(right, frwd));

		Math::Vec3 direction = _up;
		move -= direction * _deltaTime * m_speedMove;
	}
	m_eye += move;
	m_at += move;
}

void SceneCamera::InputRotation(Windowing::IWindow* _window, float _deltaTime)
{
	Math::Vec2 newMousePos = _window->GetCursorPos();
	Math::Vec2 mouseDelta = (newMousePos - m_oldMouse) * m_mouseSensitivity * _deltaTime;

	m_rotation.x -= mouseDelta.x;
	if (m_rotation.y - mouseDelta.y < Math::Tools::PI / 2.f && m_rotation.y - mouseDelta.y > - Math::Tools::PI / 2.f)
		m_rotation.y -= mouseDelta.y;

	Math::Mat4 finalMatrix = Math::Mat4::s_RotateY(m_rotation.x) * Math::Mat4::s_RotateX(m_rotation.y);
	Math::Vec4 direction = finalMatrix * Math::Vec4{ 0.f, 0.f, 1.f, 0.f };
	m_eye.x = m_at.x - direction.x;
	m_eye.y = m_at.y - direction.y;
	m_eye.z = m_at.z - direction.z;
}

void SceneCamera::SetShaderData(RHI::IShaderProgram* _shaderProgram, int viewportSizeX, int viewportSizeY)
{
	m_width = viewportSizeX;
	m_height = viewportSizeY;

	Math::Mat4 VP = Math::Mat4::s_GetPerspectiveMatrix(m_width, m_height, m_fov, m_near, m_far);
	VP *= Math::Mat4::s_GetViewMatrix(m_eye, m_at, m_up);
	_shaderProgram->SetMat4("VP", VP, true);
}