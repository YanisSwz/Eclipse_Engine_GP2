#include "Audio/AudioListener.hpp"
#include "GameObject.hpp"

namespace Core
{
	AudioListener::AudioListener(SoLoud::Soloud* _audioEngine)
	{
		m_audioEngine = _audioEngine;
	}

	void AudioListener::Update()
	{
		if (m_destroyed || !m_active)
			return;

		if (m_gameObject->transform->HasPositionChanged() && m_gameObject->transform->HasRotationChanged())
		{
			Math::Vec3 pos = m_gameObject->transform->GetPosition();
			Math::Vec3 at = m_gameObject->transform->GetForward();
			Math::Vec3 up = m_gameObject->transform->GetUp();
			m_audioEngine->set3dListenerParameters(pos.x, pos.y, pos.z, at.x, at.y, at.z, up.x, up.y, up.z);
			return;
		}
		else if(m_gameObject->transform->HasPositionChanged())
		{
			Math::Vec3 pos = m_gameObject->transform->GetPosition();
			m_audioEngine->set3dListenerPosition(pos.x, pos.y, pos.z);
			return;
		}
		else if(m_gameObject->transform->HasRotationChanged())
		{
			Math::Vec3 at = m_gameObject->transform->GetForward();
			Math::Vec3 up = m_gameObject->transform->GetUp();
			m_audioEngine->set3dListenerAt(at.x, at.y, at.z);
			m_audioEngine->set3dListenerUp(up.x, up.y, up.z);
			return;
		}
	}
}