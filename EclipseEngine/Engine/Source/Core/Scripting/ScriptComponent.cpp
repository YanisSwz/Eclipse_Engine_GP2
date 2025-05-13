#include "Scripting/ScriptComponent.hpp"
#include "Core/Scripting/TestScript.hpp"

namespace Core
{
	void ScriptComponent::Serialize(json& _j)
	{
		_j["ScriptComponent"] = json{
			{"IsActive", IsActive()},
			{"scriptName", scriptName}
		};
	}

	void ScriptComponent::Deserialize(const json& _j)
	{
		bool bIsActive;
		_j.at("IsActive").get_to(bIsActive);
		_j.at("scriptName").get_to(scriptName);
		SetActive(bIsActive);
		Bind(scriptName);
	}

	void ScriptComponent::Bind(std::string _scriptName)
	{
		scriptName = _scriptName;
		Instance = nullptr;

		InstanciateFunction = [&]() 
			{ 
				auto it = scriptRegister.find(scriptName);
				if (it == scriptRegister.end())
					return;
				Instance = it->second();
			};

		DestroyInstanceFunction = [&]()
			{
				if (Instance)
					delete Instance;
				Instance = nullptr;
			};

		OnStartFunction = [](MonoBehaviour* instance) { if (instance) instance->OnStart(); };
		OnDestroyFunction = [](MonoBehaviour* instance) { if (instance) instance->OnDestroy(); };
		OnUpdateFunction = [](MonoBehaviour* instance, Windowing::IWindow* _window, float _deltaTime) { if (instance) instance->OnUpdate(_window, _deltaTime); };

		OnCollisionEnter = [](MonoBehaviour* instance, ICollider* _collider) { if (instance) instance->OnCollisionEnter(_collider); };
		OnCollisionStay = [](MonoBehaviour* instance, ICollider* _collider) { if (instance) instance->OnCollisionStay(_collider); };
		OnCollisionExit = [](MonoBehaviour* instance, ICollider* _collider) { if (instance) instance->OnCollisionExit(_collider); };
	}
}