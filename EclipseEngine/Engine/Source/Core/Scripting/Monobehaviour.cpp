#include "Scripting/MonoBehaviour.hpp"
#include "GameObject.hpp"
#include "Core/Physics/ICollider.hpp"
#include "Windowing/IWindow.hpp"

namespace Core
{	
	void MonoBehaviour::OnStart()
	{
	}

	void MonoBehaviour::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
	{
		_window;
		_deltaTime;
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