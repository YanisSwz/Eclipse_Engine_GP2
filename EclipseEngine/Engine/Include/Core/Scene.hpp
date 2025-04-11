#pragma once
#include <vector>
#include "GameObject.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;

		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		//TODO: Add arguments
		ECLIPSE_ENGINE GameObject* CreateGameObject();
		ECLIPSE_ENGINE void DestroyGameObject();
		ECLIPSE_ENGINE Transform* GetTransforms() const;
		//TODO: need editor
		ECLIPSE_ENGINE void AddComponent();

	private:
		static const int MAX_SIZE = 100;
		int m_currentGameObjectCount = 0;
		GameObject m_gameObjects[MAX_SIZE];
		TransformSystem m_transformSystem{};
		RenderSystem m_renderSystem{};
		GameObject* m_currentGameObject = nullptr;
	};
}