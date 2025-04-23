#include "Transform.hpp"
#include "GameObject.hpp"
#include <utility>

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		m_localPosition = _translation, m_position = _translation;
		m_rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z), m_localRotation = m_rotation;
		m_eulerAngles = _rotation, m_localEulerAngles = m_eulerAngles;
		m_localScale = _scale, m_scale = _scale;
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

	std::vector<Transform*> Transform::GetChildren() const
	{
		std::vector<Transform*> children;
		for(int i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i]->IsActive())
				children.push_back(m_children[i]);
		}
		return children;
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

	void Transform::Update(bool _positionChanged, bool _scaleChanged, bool _rotationChanged)
	{
		if (!IsActive() || IsDestroyed())
			return;

		_positionChanged |= m_positionChanged;
		_scaleChanged |= m_scaleChanged;
		_rotationChanged |= m_rotationChanged;

		if (!m_isSelected)
		{
			if (_positionChanged)
				UpdatePosition();
			if (_scaleChanged)
				UpdateScale();
			if (_rotationChanged)
				UpdateRotation();
		}

		for (int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->Update(_positionChanged, _scaleChanged, _rotationChanged);
		}
	}

	void Transform::UpdatePosition()
	{
		if (m_parent != nullptr)
		{
			// We apply the parent's rotation to have the correct position
			Math::Quat tempPos{ 0.f, m_localPosition.x, m_localPosition.y, m_localPosition.z };
			Math::Quat tempQ = m_parent->m_rotation * tempPos;
			tempPos = tempQ * Math::Quat::Conjugate(m_parent->m_rotation);
			m_position = m_parent->m_position + Math::Vec3{ tempPos.x, tempPos.y, tempPos.z };
		}
		else
		{
			m_position = m_localPosition;
		}

		m_positionChanged = false;
	}

	void Transform::UpdateScale()
	{
		if (m_parent != nullptr)
			m_scale = m_parent->m_scale * m_localScale;
		else
			m_scale = m_localScale;

		m_scaleChanged = false;
	}

	void Transform::UpdateRotation()
	{
		m_localRotation = Math::Quat::QuaternionEuler(m_localEulerAngles.x, m_localEulerAngles.y, m_localEulerAngles.z);

		if (m_parent != nullptr)
		{
			m_rotation = m_parent->m_rotation * m_localRotation;
			m_eulerAngles = m_rotation.GetEulerAnglesDegXYZ();
		}
		else
		{
			m_rotation = m_localRotation;
			m_eulerAngles = m_localEulerAngles;
		}

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = false;
	}

	void Transform::StartOverride()
	{
		m_isSelected = true;
	}

	void Transform::UpdateOverride()
	{
		for (int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->Update(m_positionChanged, m_scaleChanged, m_rotationChanged);
		}
	}

	void Transform::EndOverride()
	{
		m_isSelected = false;
	}

	void Transform::Destroy()
	{
		for(int i = 0; i < m_children.size(); ++i)
		{
			if (!m_children[i]->IsDestroyed())
				m_children[i]->GetGameObject()->Destroy();
		}
		active = false;
		destroyed = true;
	}

	void Transform::SetPosition(Math::Vec3 _vec)
	{
		m_position = _vec;
		// We get the position relative to the parent
		m_localPosition = m_position - m_parent->m_position;

		// We cancel the rotation of the parent to have the correct local position
		Math::Quat tempPos{ 0.f, m_localPosition.x, m_localPosition.y, m_localPosition.z };
		Math::Quat inverseQ = Math::Quat::Inverse(m_parent->m_rotation);
		Math::Quat tempQ = inverseQ * tempPos;
		tempPos = tempQ * Math::Quat::Conjugate(inverseQ);
		m_localPosition = Math::Vec3{ tempPos.x, tempPos.y, tempPos.z };

		m_positionChanged = true;
	}

	void Transform::SetScale(Math::Vec3 _vec)
	{
		m_scale = _vec;
		// We cancel the scale of the parent
		m_localScale = m_scale / m_parent->m_scale;

		m_scaleChanged = true;
	}

	void Transform::SetRotation(Math::Quat _quat)
	{
		m_rotation = _quat;

		// We cancel the rotation of the parent and update the local euler angles to match our new rotation
		m_localRotation = Math::Quat::Inverse(m_parent->m_rotation) * m_rotation;
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegXYZ();

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = true;

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetEulerAngles(Math::Vec3 _vec)
	{
		m_eulerAngles = _vec;

		m_rotation = Math::Quat::QuaternionEuler(m_eulerAngles.x, m_eulerAngles.y, m_eulerAngles.z);

		// We cancel the rotation of the parent and update the local euler angles to match our new rotation
		m_localRotation = Math::Quat::Inverse(m_parent->m_rotation) * m_rotation;
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegXYZ();

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = true;

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}


	// TODO: check if local rotation setters are correct
	void Transform::SetLocalRotation(Math::Quat _quat)
	{
		m_localRotation = _quat;
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_localRotation.Rotate(Math::Vec3::right);
		m_up = m_localRotation.Rotate(Math::Vec3::up);
		m_forward = m_localRotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}
	void Transform::SetLocalEulerAngles(Math::Vec3 _vec)
	{
		m_localEulerAngles = _vec;
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_localRotation.Rotate(Math::Vec3::right);
		m_up = m_localRotation.Rotate(Math::Vec3::up);
		m_forward = m_localRotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}
}