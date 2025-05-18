#include "Scripting/ScriptComponent.hpp"
#include "Maths.hpp"
#include "Logger.hpp"
#include <fstream>
namespace Core
{
	std::filesystem::path ScriptComponent::m_defaultPathScriptHPP = "Assets/Scripts/Defaulthpp.txt";
	std::filesystem::path ScriptComponent::m_defaultPathScriptCPP = "Assets/Scripts/Defaultcpp.txt";

	ScriptComponent::~ScriptComponent()
	{
		if (Instance)
			delete Instance;
	}

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

		InstanciateFunction = [&](std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register)
			{
				auto it = _register.find(scriptName);
				if (it == _register.end())
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

	void ScriptComponent::CreateScript(std::string _className)
	{
		if (_className.empty() || !std::filesystem::exists(m_defaultPathScriptHPP) || !std::filesystem::exists(m_defaultPathScriptCPP))
			return;

		// Get DefaultHpp file content
		std::ifstream hppFile(m_defaultPathScriptHPP);
		std::string hppFileContent((std::istreambuf_iterator<char>(hppFile)), std::istreambuf_iterator<char>());

		std::vector<std::string> hppStringList = Math::Tools::Split(hppFileContent, '|');

		std::ofstream hppFileStream;
		hppFileStream.open("Assets/Scripts/" + _className + ".hpp");
		if (!hppFileStream.is_open())
			return;

		int hppStringListSize = static_cast<int>(hppStringList.size());
		for (int i = 0; i < hppStringListSize; ++i)
		{
			hppFileStream << hppStringList[i];
			if (i != hppStringListSize - 1)
				hppFileStream << _className;
		}

		hppFileStream.close();


		// Get DefaultCpp file content
		std::ifstream cppFile(m_defaultPathScriptCPP);
		std::string cppFileContent((std::istreambuf_iterator<char>(cppFile)), std::istreambuf_iterator<char>());

		std::vector<std::string> cppStringList = Math::Tools::Split(cppFileContent, '|');

		std::ofstream cppFileStream;
		cppFileStream.open("Assets/Scripts/" + _className + ".cpp");
		if (!cppFileStream.is_open())
			return;

		int cppStringListSize = static_cast<int>(cppStringList.size());
		for (int i = 0; i < cppStringListSize; ++i)
		{
			cppFileStream << cppStringList[i];
			if (i != cppStringListSize - 1)
				cppFileStream << _className;
		}

		cppFileStream.close();
	}
}