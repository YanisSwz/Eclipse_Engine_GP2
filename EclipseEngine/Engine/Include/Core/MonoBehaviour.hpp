#pragma once
#include "ProjectExports.hpp"
#include "Component.hpp"

namespace Core 
{
	class MonoBehaviour : public Component
	{
	public:
		virtual void Awake() = 0;
		virtual void OnEnable() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDestroy() = 0;
	};
}