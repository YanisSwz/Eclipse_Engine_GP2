#pragma once
#include "Scripting/ScriptComponent.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class ScriptingSystem
	{
	public:
		ScriptingSystem();
		~ScriptingSystem();

		ECLIPSE_ENGINE ScriptComponent* AddScript();
		ECLIPSE_ENGINE void Update(Windowing::IWindow* _window, float _deltaTime);
		ECLIPSE_ENGINE void Reset();

	private:
		static const int MAX_SCRIPT_COUNT = 100;
		int m_currentScriptCount = 0;
		ScriptComponent m_scripts[MAX_SCRIPT_COUNT];
	};
}