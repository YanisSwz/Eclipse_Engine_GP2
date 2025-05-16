#include "Scripting/ScriptingSystem.hpp"
#include "Scene.hpp"
#include "GameObject.hpp"
#include "Logger.hpp"

namespace Core
{
	ScriptingSystem::ScriptingSystem()
	{
	}

	ScriptingSystem::~ScriptingSystem()
	{
	}

	ScriptComponent* ScriptingSystem::AddScript()
	{
		if (m_currentScriptCount >= MAX_SCRIPT_COUNT)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of ScriptComponent reached!");
			return nullptr;
		}

		for (int i = 0; i < m_currentScriptCount; ++i)
		{
			if (m_scripts[i].IsDestroyed())
			{
				m_scripts[i].Remove();
				m_scripts[i].~ScriptComponent();
				new (&m_scripts[i]) ScriptComponent();
				m_scripts[i].SetActive(true);
				return &m_scripts[i];
			}
		}

		m_scripts[m_currentScriptCount].~ScriptComponent();
		new (&m_scripts[m_currentScriptCount]) ScriptComponent();
		m_scripts[m_currentScriptCount].SetActive(true);

		++m_currentScriptCount;

		return &m_scripts[m_currentScriptCount - 1];
	}

	void ScriptingSystem::Update(Scene* _scene, Windowing::IWindow* _window, float _deltaTime, std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register)
	{
		for (int i = 0; i < m_currentScriptCount; ++i)
		{
			ScriptComponent* script = &m_scripts[i];
			if (script->IsActive() && !script->IsDestroyed())
			{
				if (!script->Instance)
				{
					if (script->InstanciateFunction)
						script->InstanciateFunction(_register);
					if (script->Instance)
					{
						script->Instance->m_gameObject = script->m_gameObject;
						script->Instance->m_scene = _scene;
					}
					if (script->OnStartFunction)
						script->OnStartFunction(script->Instance);
				}

				if (script->OnUpdateFunction)
					script->OnUpdateFunction(script->Instance, _window, _deltaTime);
			}
		}
	}

	void ScriptingSystem::Reset()
	{
		for (int i = 0; i < m_currentScriptCount; ++i)
		{
			ScriptComponent* script = &m_scripts[i];
			if (script && script->Instance)
			{
				if (script->OnDestroyFunction)
					script->OnDestroyFunction(script->Instance);
				if (script->DestroyInstanceFunction)
					script->DestroyInstanceFunction();
			}
		}
		m_currentScriptCount = 0;
	}
}