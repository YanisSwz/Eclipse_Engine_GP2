#include "SystemManager.hpp"
#include "IWindow.hpp"
#include "Scene.hpp"

namespace Core
{
	SystemManager::SystemManager()
	{
		m_audioSystem.Init();
	}

	SystemManager::~SystemManager()
	{
		m_audioSystem.Destroy();
	}

	void SystemManager::Update(Scene* _scene, Windowing::IWindow* _window, float _deltaTime, GAME_STATE _state, std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register)
	{
		switch (_state)
		{
		case GAME_STATE::PLAY:
			m_scriptingSystem.Update(_scene, _window, _deltaTime, _register);
			m_transformSystem.Update();
			m_physicsSystem.Update(_deltaTime);
			m_audioSystem.Update();
			break;
		case GAME_STATE::PAUSE:
			m_transformSystem.Update();
			m_physicsSystem.Update(0.f);
			break;
		case GAME_STATE::STOP:
			m_transformSystem.Update();
			m_audioSystem.EditorUpdate();
			break;
		}
		m_transformSystem.LateUpdate();
		m_particleSystem.Update(_deltaTime);
	}

	Transform* SystemManager::AddTransform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		return m_transformSystem.Add(_translation, _rotation, _scale, _parent);
	}

	Transform* SystemManager::GetTransformsRoot() const
	{
		return m_transformSystem.GetRoot();
	}

	void SystemManager::Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _V, Math::Mat4 _P, Math::Vec3 _viewPos)
	{
		m_renderSystem.Render(_renderInterface, _pipeline, _V, _P, _viewPos, m_particleSystem.GetRenderData());
	}

	AudioSystem* SystemManager::GetAudioSystem()
	{
		return &m_audioSystem;
	}

	CameraSystem* SystemManager::GetCameraSystem()
	{
		return &m_cameraSystem;
	}

	ScriptingSystem* SystemManager::GetScriptingSystem()
	{
		return &m_scriptingSystem;
	}

	Component* SystemManager::AddComponent(std::string _componentType)
	{
		if (_componentType == "Camera")
		{
			return m_cameraSystem.AddCamera();
		}
		else if (_componentType == "Model")
		{
			return m_renderSystem.AddModel();
		}
		else if (_componentType == "BoxCollider")
		{
			return m_physicsSystem.AddBoxCollider();
		}
		else if (_componentType == "CapsuleCollider")
		{
			return m_physicsSystem.AddCapsuleCollider();
		}
		else if (_componentType == "MeshCollider")
		{
			return m_physicsSystem.AddMeshCollider();
		}
		else if (_componentType == "DirectionalLight")
		{
			return m_renderSystem.AddDirLight();
		}
		else if (_componentType == "PointLight")
		{
			return m_renderSystem.AddPointLight();
		}
		else if (_componentType == "SpotLight")
		{
			return m_renderSystem.AddSpotLight();
		}
		else if (_componentType == "AudioSource")
		{
			return m_audioSystem.AddAudioSource();
		}
		else if (_componentType == "AudioListener")
		{
			return m_audioSystem.AddAudioListener();
		}
		else if (_componentType == "ParticleEmitter")
		{
			return m_particleSystem.AddParticleEmitter();
		}
		else if (_componentType == "ScriptComponent")
		{
			return m_scriptingSystem.AddScript();
		}

		Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "%s is not a Component type", _componentType);
		return nullptr;
	}

	void SystemManager::Reset()
	{
		m_audioSystem.Reset();
		m_scriptingSystem.Reset();
		m_physicsSystem.Reset();
		m_transformSystem.Reset();
		m_renderSystem.Reset();
		m_cameraSystem.Reset();
		m_particleSystem.Reset();
	}
}