#pragma once
#include <vector>
#include "GameObject.hpp"
#include "SystemManager.hpp"
#include "ProjectExports.hpp"
#include "GameState.hpp"
#include <type_traits>

namespace Core
{
	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE GameObject* CreateGameObject();
		ECLIPSE_ENGINE SystemManager* GetSystemManager();
		ECLIPSE_ENGINE GameObject* GetObjectByID(int _id);
		ECLIPSE_ENGINE inline GAME_STATE GetState() const { return m_state; }
		ECLIPSE_ENGINE void SetState(GAME_STATE _state);

	private:
		static const int MAX_SIZE = 100;
		int m_currentGameObjectCount = 0;
		GameObject m_gameObjects[MAX_SIZE];

		SystemManager m_systemManager{};
		GAME_STATE m_state = GAME_STATE::STOP;
	};
}