#include "SystemManager.hpp"

namespace Core
{
	void SystemManager::Update(float _deltaTime)
	{
		m_transformSystem.Update();
		m_physicsSystem.Update(_deltaTime);
	}

	Transform* SystemManager::AddTransform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		return m_transformSystem.Add(_translation, _rotation, _scale, _parent);
	}

	Transform* SystemManager::GetTransformsRoot() const
	{
		return m_transformSystem.GetRoot();
	}

	std::vector<Resource::ModelData> SystemManager::GetStaticModels() const
	{
		return m_renderSystem.GetStaticModels();
	}
}