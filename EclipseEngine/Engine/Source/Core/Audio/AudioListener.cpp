#include "Audio/AudioListener.hpp"
#include "GameObject.hpp"

namespace Core
{
	AudioListener::AudioListener(SoLoud::Soloud* _audioEngine)
	{
		m_audioEngine = _audioEngine;
	}

	void AudioListener::SetActive(bool _active)
	{
		m_active = _active;
		if (m_active)
		{
			if (IsCurrentListener())
				Start();
		}
	}

	void AudioListener::Start()
	{
		if (m_destroyed || !m_active)
			return;
		if (!m_gameObject)
			return;

		UpdateAll();
		m_audioEngine->update3dAudio();
	}

	void AudioListener::Update()
	{
		if (m_destroyed || !m_active)
			return;

		if (!m_started)
		{
			m_started = true;
			Start();
			return;
		}

		if (m_gameObject->transform->HasPositionChanged() && m_gameObject->transform->HasRotationChanged())
		{
			UpdateAll();
			return;
		}
		else if(m_gameObject->transform->HasPositionChanged())
		{
			UpdatePosition();
			return;
		}
		else if(m_gameObject->transform->HasRotationChanged())
		{
			UpdateRotation();
			return;
		}
	}

	bool AudioListener::IsCurrentListener() const
	{
		if (m_gameObject == nullptr)
			return false;

		AudioListener* currentListener = m_gameObject->GetSystemManager()->GetAudioSystem()->GetCurrentAudioListener();
		return currentListener == this;
	}

	void AudioListener::SetCurrentListener()
	{
		if (m_destroyed || !m_active)
			return;

		m_gameObject->GetSystemManager()->GetAudioSystem()->SetCurrentListener(this);
	}

	void AudioListener::UpdateAll()
	{
		Math::Vec3 pos = m_gameObject->transform->GetPosition();
		Math::Vec3 at = m_gameObject->transform->GetForward();
		Math::Vec3 up = m_gameObject->transform->GetUp();
		m_audioEngine->set3dListenerParameters(pos.x, pos.y, pos.z, at.x, at.y, at.z, up.x, up.y, up.z);
	}

	void AudioListener::UpdatePosition()
	{
		Math::Vec3 pos = m_gameObject->transform->GetPosition();
		m_audioEngine->set3dListenerPosition(pos.x, pos.y, pos.z);
	}

	void AudioListener::UpdateRotation()
	{
		Math::Vec3 at = m_gameObject->transform->GetForward();
		Math::Vec3 up = m_gameObject->transform->GetUp();
		m_audioEngine->set3dListenerAt(at.x, at.y, at.z);
		m_audioEngine->set3dListenerUp(up.x, up.y, up.z);
	}

	void AudioListener::Serialize(json& _j)
	{
		_j = json{
			{"IsActive", IsActive()}
		};
	}

	void AudioListener::Deserialize(const json& _j)
	{
		bool bIsActive;

		_j.at("IsActive").get_to(bIsActive);

		SetActive(bIsActive);
	}
}