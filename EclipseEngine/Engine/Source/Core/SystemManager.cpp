#include "SystemManager.hpp"

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

	void SystemManager::Update(float _deltaTime, GAME_STATE _state)
	{
		m_transformSystem.Update();
		switch (_state)
		{
		case GAME_STATE::PLAY:
			m_physicsSystem.Update(_deltaTime);
			m_audioSystem.Update();
			break;
		case GAME_STATE::PAUSE:
			m_physicsSystem.Update(0.f);
			break;
		case GAME_STATE::STOP:
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

	void SystemManager::Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _VP, Math::Vec3 _viewPos)
	{
		m_renderSystem.Render(_renderInterface, _pipeline, _VP, _viewPos, m_particleSystem.GetRenderData());
	}

	AudioSystem* SystemManager::GetAudioSystem()
	{
		return &m_audioSystem;
	}

	CameraSystem* SystemManager::GetCameraSystem()
	{
		return &m_cameraSystem;
	}
}