#pragma once
#include "Component.hpp"
#include "Scripting/MonoBehaviour.hpp"
#include "IWindow.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <filesystem>

namespace Core
{
	class ICollider;

	class ScriptComponent : public Component
	{
	public:
		ScriptComponent() = default;
		ECLIPSE_ENGINE ~ScriptComponent();

		MonoBehaviour* Instance = nullptr;
		std::string scriptName;

		std::function<void(std::unordered_map<std::string, std::function<MonoBehaviour* ()>>&)> InstanciateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(MonoBehaviour*)> OnStartFunction;
		std::function<void(MonoBehaviour*)> OnDestroyFunction;
		std::function<void(MonoBehaviour*, Windowing::IWindow* _window, float)> OnUpdateFunction;

		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionEnter;
		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionStay;
		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionExit;

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

		ECLIPSE_ENGINE void Bind(std::string _scriptName);
		ECLIPSE_ENGINE static void CreateScript(std::string _className);

		inline static std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& GetScriptRegister()
		{
			static std::unordered_map<std::string, std::function<MonoBehaviour* ()>> scriptRegister;
			return scriptRegister;
		}
		inline void SetScriptRegister(std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register)
		{
			GetScriptRegister() = _register;
		}

		friend class ScriptingSystem;

	private:
		static std::filesystem::path m_defaultPathScriptHPP;
		static std::filesystem::path m_defaultPathScriptCPP;
	};
}