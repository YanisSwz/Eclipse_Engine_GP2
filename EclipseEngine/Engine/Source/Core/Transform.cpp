#include "Transform.hpp"
#include <utility>

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		localPosition = _translation, position = _translation;
		rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z), localRotation = rotation;
		eulerAngles = _rotation, localEulerAngles = eulerAngles;
		localScale = _scale, scale = _scale;
		if (_parent != nullptr)
		{
			m_parent = _parent;
			m_parent->AddChild(this);
		}
	}

	Transform::~Transform()
	{
		m_children.clear();
	}

	void Transform::SetParent(Transform* _parent)
	{
		if (m_parent == _parent)
			return;
		if (m_parent != nullptr)
			m_parent->RemoveChild(this);
		m_parent = _parent;
		m_parent->AddChild(this);
	}

	void Transform::AddChild(Transform* _child)
	{
		for (int i = 0; i < m_children.size(); ++i)
		{
			if (_child == m_children[i])
				return;
		}
		m_children.push_back(_child);
		_child->SetParent(this);
	}

	void Transform::RemoveChild(Transform* _child)
	{
		for (int i = 0; i < m_children.size(); ++i)
		{
			if (_child == m_children[i])
			{
				m_children.erase(m_children.begin() + i);
				return;
			}
		}

	}

	void Transform::Update()
	{
		if (!isSelected)
		{
			localRotation = Math::Quat::QuaternionEuler(localEulerAngles.x, localEulerAngles.y, localEulerAngles.z);
			if (m_parent != nullptr)
			{
				// Extract new position, scale and rotation
				Math::Quat tempPos{ 0.f, localPosition.x, localPosition.y, localPosition.z };
				Math::Quat tempQ = m_parent->rotation * tempPos;
				tempPos = tempQ * Math::Quat::Conjugate(m_parent->rotation);
				position = m_parent->position + Math::Vec3{ tempPos.x, tempPos.y, tempPos.z };

				scale = m_parent->scale * localScale;

				rotation = m_parent->rotation * localRotation;
			}
			else
			{
				position = localPosition;
				scale = localScale;
				rotation = localRotation;
			}
		}

		for (int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->Update();
		}
	}

	void Transform::StartOverride()
	{
		isSelected = true;
	}

	void Transform::EndOverride()
	{
		// We get the position relative to the parent
		localPosition = position - m_parent->position;

		// We cancel the rotation of the parent to have the right local position
		Math::Quat tempPos{ 0.f, localPosition.x, localPosition.y, localPosition.z };
		Math::Quat inverseQ = Math::Quat::Inverse(m_parent->rotation);
		Math::Quat tempQ = inverseQ * tempPos;
		tempPos = tempQ * Math::Quat::Conjugate(inverseQ);
		localPosition = Math::Vec3{tempPos.x, tempPos.y, tempPos.z};

		localScale = scale / m_parent->scale;

		for (int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->Update();
		}

		isSelected = false;
	}
}