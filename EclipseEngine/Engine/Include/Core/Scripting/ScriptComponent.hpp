#pragma once
#include "Component.hpp"
#include "Scripting/MonoBehaviour.hpp"
#include "IWindow.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace Core
{
	class ICollider;

	class ScriptComponent : public Component
	{
	public:
		ScriptComponent() = default;
		~ScriptComponent() = default;

		MonoBehaviour* Instance = nullptr;
		std::string scriptName;

		std::function<void()> InstanciateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(MonoBehaviour*)> OnStartFunction;
		std::function<void(MonoBehaviour*)> OnDestroyFunction;
		std::function<void(MonoBehaviour*, Windowing::IWindow* _window, float)> OnUpdateFunction;

		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionEnter;
		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionStay;
		std::function<void(MonoBehaviour*, ICollider*)> OnCollisionExit;

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

		template <typename T>
		void Bind(std::string _scriptName);
		ECLIPSE_ENGINE void Bind(std::string _scriptName);

		inline static std::unordered_map<std::string, std::function<MonoBehaviour*()>>& GetRegister()
		{
			return scriptRegister;
		}

		friend class ScriptingSystem;
	private:
		inline static std::unordered_map<std::string, std::function<MonoBehaviour*()>> scriptRegister{};
	};
}

#include "Scripting/ScriptComponent.inl"