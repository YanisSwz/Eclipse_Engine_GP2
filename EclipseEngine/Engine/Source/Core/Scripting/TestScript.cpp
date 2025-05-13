#include "Scripting/TestScript.hpp"
#include "GameObject.hpp"
#include "Core/Physics/ICollider.hpp"
#include "IWindow.hpp"
#include "Logger.hpp"


void TestScript::OnStart()
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Start");
}

void TestScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	float speed = 5.f;
	//Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Update: %f", _deltaTime);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_W, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 0.f, 1.f, 0.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_S, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 0.f, -1.f, 0.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_A, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 1.f, 0.f, 0.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_D, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ -1.f, 0.f, 0.f } *_deltaTime * speed);
}

void TestScript::OnDestroy()
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "OnDestroy");
}

void TestScript::OnCollisionEnter(Core::ICollider* _collider)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "OnCollisionEnter");
}

void TestScript::OnCollisionStay(Core::ICollider* _collider)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "OnCollisionStay");
}

void TestScript::OnCollisionExit(Core::ICollider* _collider)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "OnCollisionExit");
}
