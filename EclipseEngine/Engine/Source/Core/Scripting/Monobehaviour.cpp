#include "Scripting/MonoBehaviour.hpp"

namespace Core
{	
	MonoBehaviour::~MonoBehaviour()
	{
	}

	void MonoBehaviour::OnStart()
	{
	}

	void MonoBehaviour::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
	{
	}

	void MonoBehaviour::OnDestroy()
	{
	}

	void MonoBehaviour::OnCollisionEnter(ICollider* _collider)
	{
	}

	void MonoBehaviour::OnCollisionStay(ICollider* _collider)
	{
	}

	void MonoBehaviour::OnCollisionExit(ICollider* _collider)
	{
	}
}