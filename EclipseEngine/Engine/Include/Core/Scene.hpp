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
		ECLIPSE_ENGINE inline int GetCount() { return m_currentGameObjectCount; }
		ECLIPSE_ENGINE inline GameObject* GetGameObject(int _index) { return (_index < MAX_SIZE) ? &m_gameObjects[_index] : nullptr; }
		/// <summary>
		/// Returns the index of _gameObject if it exists in the Scene, -1 otherwise
		/// </summary>
		/// <param name="_gameObject"></param>
		/// <returns></returns>
		ECLIPSE_ENGINE int GetGameObjectIndex(GameObject* _gameObject);
		/// <summary>
		/// Returns given gameObject's parent index (through its index) if it exists in the Scene, -1 otherwise
		/// </summary>
		/// <param name="_index"> : index of the given GameObject</param>
		/// <returns></returns>
		ECLIPSE_ENGINE int GetGameObjectParentIndex(int _index);
		
		ECLIPSE_ENGINE inline GAME_STATE GetState() const { return m_state; }
		ECLIPSE_ENGINE void SetState(GAME_STATE _state);

		ECLIPSE_ENGINE void Reset();

	private:
		static const int MAX_SIZE = 100;
		int m_currentGameObjectCount = 0;
		GameObject m_gameObjects[MAX_SIZE];

		SystemManager m_systemManager{};
		GAME_STATE m_state = GAME_STATE::STOP;
	};
}