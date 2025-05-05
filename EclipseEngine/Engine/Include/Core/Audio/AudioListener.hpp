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

		ECLIPSE_ENGINE void SetActive(bool _active) override;

		ECLIPSE_ENGINE void Start();
		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE bool IsCurrentListener() const;
		ECLIPSE_ENGINE void SetCurrentListener();

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

	private:
		void UpdateAll();
		void UpdatePosition();
		void UpdateRotation();

		bool m_started = false;
		SoLoud::Soloud* m_audioEngine = nullptr;
	};
}