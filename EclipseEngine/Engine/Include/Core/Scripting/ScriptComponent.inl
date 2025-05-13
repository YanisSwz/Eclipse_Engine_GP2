#pragma once
#include "Scripting/ScriptComponent.hpp"

namespace Core
{
	template <typename T>
	void ScriptComponent::Bind(std::string _scriptName)
	{
		scriptName = _scriptName;
		Instance = nullptr;

		InstanciateFunction = [&]() { Instance = new T; };
		DestroyInstanceFunction = [&]()
			{
				if (Instance)
					delete Instance;
				Instance = nullptr;
			};

		OnStartFunction = [](MonoBehaviour* instance) { ((T*)instance)->OnStart(); };
		OnDestroyFunction = [](MonoBehaviour* instance) { ((T*)instance)->OnDestroy(); };
		OnUpdateFunction = [](MonoBehaviour* instance, Windowing::IWindow* _window, float _deltaTime) { ((T*)instance)->OnUpdate(_window, _deltaTime); };

		OnCollisionEnter = [](MonoBehaviour* instance, ICollider* _collider) { ((T*)instance)->OnCollisionEnter(_collider); };
		OnCollisionStay = [](MonoBehaviour* instance, ICollider* _collider) { ((T*)instance)->OnCollisionStay(_collider); };
		OnCollisionExit = [](MonoBehaviour* instance, ICollider* _collider) { ((T*)instance)->OnCollisionExit(_collider); };

		//scriptRegister[name] = []() {
		//	return std::make_unique<MonoBehaviour>();
		//	};

		//auto it = scriptRegister.find(name);
		//if (it != scriptRegister.end())
		//{
		//	std::unique_ptr<MonoBehaviour> newInstance = it->second();
		//	Instance = newInstance.get();
		//}
	}
}