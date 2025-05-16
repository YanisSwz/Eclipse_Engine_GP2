#pragma once
#include "Scripting/ScriptComponent.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class Scene;

	class ScriptingSystem
	{
	public:
		ScriptingSystem();
		~ScriptingSystem();

		ECLIPSE_ENGINE ScriptComponent* AddScript();
		ECLIPSE_ENGINE void Update(Scene* _scene, Windowing::IWindow* _window, float _deltaTime, std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register);
		ECLIPSE_ENGINE void Reset();

	private:
		static const int MAX_SCRIPT_COUNT = 100;
		int m_currentScriptCount = 0;
		ScriptComponent m_scripts[MAX_SCRIPT_COUNT];
	};
}