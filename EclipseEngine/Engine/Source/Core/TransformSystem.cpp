#include "TransformSystem.hpp"

namespace Core 
{
	TransformSystem::TransformSystem()
	{
		m_data[m_currentCount].~Transform();
		new (&m_data[m_currentCount]) Transform();
		m_root = &m_data[m_currentCount];
		++m_currentCount;
	}

	Transform* TransformSystem::Add(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		if (m_currentCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentCount; ++i)
		{
			if (m_data[i].IsDestroyed())
			{
				m_data[i].Remove();
				m_data[i].~Transform();
				new (&m_data[i]) Transform(_translation, _rotation, _scale, _parent);
				if (_parent == nullptr)
				{
					m_data[i].SetParent(m_root);
				}
				return &m_data[i];
			}
		}

		m_data[m_currentCount].~Transform();
		new (&m_data[m_currentCount]) Transform(_translation, _rotation, _scale, _parent);
		if(_parent == nullptr)
		{
			m_data[m_currentCount].SetParent(m_root);
			m_root->AddChild(&m_data[m_currentCount]);
		}
		++m_currentCount;
		return &m_data[m_currentCount-1];
	}

	void TransformSystem::Update()
	{
		m_root->Update();
	}

	Transform* TransformSystem::GetRoot() const
	{
		return m_root;
	}
}