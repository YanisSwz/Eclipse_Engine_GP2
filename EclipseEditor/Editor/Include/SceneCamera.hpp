#pragma once
#include "Maths.hpp"
#include "RHIInterfaces/IShaderProgram.hpp"
#include "Resource/ShaderProgram.hpp"
#include "IWindow.hpp"

namespace Core
{
	class SceneCamera
	{
	public:
		SceneCamera() = default;
		SceneCamera(float _fov, float _near, float _far);
		~SceneCamera() = default;

		void Update(Windowing::IWindow* _window, float _deltaTime, Math::Vec2 _sceneWindowPos, Math::Vec2 _sceneWindowSize);
		Math::Mat4 GetView() const;
		Math::Mat4 GetProjection() const;
		Math::Mat4 GetVP() const;
		Math::Vec3 GetViewPos() const;

	private:
		void UpdateInput(Windowing::IWindow* _window, float _deltaTime, Math::Vec2 _sceneWindowPos, Math::Vec2 _sceneWindowSize);
		void InputChangeSpeed(Windowing::IWindow* _window);
		void InputMove(Windowing::IWindow* _window, float _deltaTime);
		void InputRotation(Windowing::IWindow* _window, float _deltaTime);

		Math::Vec3 m_eye = { 0.f, 0.f, 1.f };
		Math::Vec3 m_at = { 0.f, 0.f, 2.f };
		Math::Vec3 m_up = { 0.f, 1.f, 0.f };

		float m_minSpeed = 0.1f;
		float m_maxSpeed = 10.f;
		float m_increaseSpeedValue = 0.1f;

		int m_width = 0;
		int m_height = 0;
		float m_fov = 60.f;
		float m_near = 0.1f;
		float m_far = 100.f;

		float m_moveSpeed = 1.f;
		float m_mouseSensitivity = 1.f;

		Math::Vec2 m_rotation{ 0.f, 0.f };
		Math::Vec2 m_oldMouse{ 0.f, 0.f };
	};
}