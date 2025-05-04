#pragma once
#include "Core/Component.hpp"
#include "soloud.h"
#include "ProjectExports.hpp"

namespace Core
{
	class AudioListener : public Component 
	{
	public:
		ECLIPSE_ENGINE AudioListener() = default;
		ECLIPSE_ENGINE AudioListener(SoLoud::Soloud* _audioEngine);
		ECLIPSE_ENGINE ~AudioListener() = default;

		ECLIPSE_ENGINE void Update();

	private:
		SoLoud::Soloud* m_audioEngine = nullptr;
	};
}