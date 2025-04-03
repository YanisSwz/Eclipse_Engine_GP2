#include "TransformSystem.hpp"

namespace Core 
{
	Transform* TransformSystem::Add(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		if (m_currentCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentCount; ++i)
		{
			if (m_data[i].IsDestroyed())
			{
				m_data[i].Remove();
				m_data[i] = Transform(_translation, _rotation, _scale);
				return &m_data[i];
			}
		}

		m_data[m_currentCount] = Transform(_translation, _rotation, _scale);
		++m_currentCount;
		return &m_data[m_currentCount];
	}

	void TransformSystem::Update()
	{
		m_root->Update();
	}
}