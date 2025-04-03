#include "Transform.hpp"

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		position = _translation;
		rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		scale = _scale;
	}

	Transform::~Transform(){}

	void Transform::SetParent(Transform* _parent)
	{
		m_parent = _parent;
	}

	void Transform::AddChild(Transform* _child)
	{
		for (int i = 0; i < m_children.size(); ++i)
		{
			if (_child == m_children[i])
				return;
		}
		m_children.push_back(_child);
	}

	void Transform::Update()
	{
		if(m_parent != nullptr)
		{
		}
	}

	
}