#include "CameraScript.hpp"
#include "GameObject.hpp"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::OnStart()
{

}

void CameraScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
}

void CameraScript::OnDestroy()
{
}

void CameraScript::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void CameraScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void CameraScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}