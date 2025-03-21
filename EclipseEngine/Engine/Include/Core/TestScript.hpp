#pragma once
#include "MonoBehaviour.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class TestScript : public MonoBehaviour
	{
	public:
		ECLIPSE_ENGINE TestScript() = default;
		ECLIPSE_ENGINE ~TestScript();

		ECLIPSE_ENGINE void Awake() override;
		ECLIPSE_ENGINE void OnEnable() override;
		ECLIPSE_ENGINE void Start() override;
		ECLIPSE_ENGINE void Update() override;
		ECLIPSE_ENGINE void OnDisable() override;
		ECLIPSE_ENGINE void OnDestroy() override;
	};
}
