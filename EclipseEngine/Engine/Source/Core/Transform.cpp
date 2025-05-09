#include "Transform.hpp"
#include "GameObject.hpp"
#include "Logging/Logger.hpp"
#include <utility>

namespace Core
{
	meta::factory<Transform> Transform::factory = meta::reflect<Transform>(hash("Transform"))
		//.data<&Transform::SetLocalPosition, &Transform::GetLocalPosition>(hash("LocalPosition"))
		//.data<&Transform::SetLocalScale, &Transform::GetLocalScale>(hash("LocalScale"))
		//.data<&Transform::SetLocalEulerAngles, &Transform::GetLocalEulerAngles>(hash("LocalRotation"))
		.func<&Transform::UpdatePosition>(hash("UpdateLocalPosition"))
		.func<&Transform::UpdateScale>(hash("UpdateLocalScale"))
		.func<&Transform::UpdateRotation>(hash("UpdateLocalRotation"));


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
			if (!m_children[i]->IsDestroyed())
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
		if (m_destroyed)
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
	}

	void Transform::UpdateScale()
	{
		if (m_parent != nullptr)
			m_scale = m_parent->m_scale * m_localScale;
		else
			m_scale = m_localScale;
	}

	void Transform::UpdateRotation()
	{
		m_localRotation = Math::Quat::QuaternionEuler(m_localEulerAngles.x, m_localEulerAngles.y, m_localEulerAngles.z);

		if (m_parent != nullptr)
		{
			m_rotation = m_parent->m_rotation * m_localRotation;
			m_eulerAngles = m_rotation.GetEulerAnglesDegZYX();
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
	}

	void Transform::LateUpdate()
	{
		if (m_destroyed)
			return;

		m_positionChanged = false;
		m_rotationChanged = false;
		m_scaleChanged = false;

		for (int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->LateUpdate();
		}
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
		m_active = false;
		m_destroyed = true;
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
		m_rotation = Math::Quat::Normalized(_quat);

		// We cancel the rotation of the parent and update the local euler angles to match our new rotation
		m_localRotation = Math::Quat::Inverse(m_parent->m_rotation) * m_rotation;
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();

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
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = true;

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetLocalRotation(Math::Quat _quat)
	{
		m_localRotation = Math::Quat::Normalized(_quat);
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();
		m_rotation = m_parent->m_rotation * m_localRotation;
		m_eulerAngles = m_rotation.GetEulerAnglesDegZYX();
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetLocalEulerAngles(Math::Vec3 _vec)
	{
		m_localEulerAngles = _vec;
		m_localRotation = Math::Quat::QuaternionEuler(m_localEulerAngles.x, m_localEulerAngles.y, m_localEulerAngles.z);
		m_rotation = m_parent->m_rotation * m_localRotation;
		m_eulerAngles = m_rotation.GetEulerAnglesDegZYX();
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetPosition(float _x, float _y, float _z)
	{
		m_position.x = _x;
		m_position.y = _y;
		m_position.z = _z;

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

	void Transform::SetScale(float _x, float _y, float _z) 
	{
		m_scale.x = _x;
		m_scale.y = _y;
		m_scale.z = _z;

		// We cancel the scale of the parent
		m_localScale = m_scale / m_parent->m_scale;

		m_scaleChanged = true;
	}

	void Transform::SetRotation(float _w, float _x, float _y, float _z) 
	{
		m_rotation.w = _w;
		m_rotation.x = _x;
		m_rotation.y = _y;
		m_rotation.z = _z;
		m_rotation.Normalize();

		// We cancel the rotation of the parent and update the local euler angles to match our new rotation
		m_localRotation = Math::Quat::Inverse(m_parent->m_rotation) * m_rotation;
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = true;

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetEulerAngles(float _x, float _y, float _z) 
	{
		m_eulerAngles.x = _x;
		m_eulerAngles.y = _y;
		m_eulerAngles.z = _z;

		m_rotation = Math::Quat::QuaternionEuler(m_eulerAngles.x, m_eulerAngles.y, m_eulerAngles.z);

		// We cancel the rotation of the parent and update the local euler angles to match our new rotation
		m_localRotation = Math::Quat::Inverse(m_parent->m_rotation) * m_rotation;
		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		m_rotationChanged = true;

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetLocalPosition(float _x, float _y, float _z) 
	{
		m_localPosition.x = _x;
		m_localPosition.y = _y;
		m_localPosition.z = _z;

		m_positionChanged = true;
	}

	void Transform::SetLocalScale(float _x, float _y, float _z) 
	{
		m_localScale.x = _x;
		m_localScale.y = _y;
		m_localScale.z = _z;

		m_scaleChanged = true;
	}

	void Transform::SetLocalRotation(float _w, float _x, float _y, float _z) 
	{
		m_localRotation.w = _w;
		m_localRotation.x = _x;
		m_localRotation.y = _y;
		m_localRotation.z = _z;
		m_localRotation.Normalize();

		m_localEulerAngles = m_localRotation.GetEulerAnglesDegZYX();
		m_rotation = m_parent ? (m_parent->m_rotation * m_localRotation) : m_localRotation;
		m_eulerAngles = m_rotation.GetEulerAnglesDegZYX();
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::SetLocalEulerAngles(float _x, float _y, float _z) 
	{
		m_localEulerAngles.x = _x;
		m_localEulerAngles.y = _y;
		m_localEulerAngles.z = _z;

		m_localRotation = Math::Quat::QuaternionEuler(m_localEulerAngles.x, m_localEulerAngles.y, m_localEulerAngles.z);
		m_rotation = m_parent ? (m_parent->m_rotation * m_localRotation) : m_localRotation;
		m_eulerAngles = m_rotation.GetEulerAnglesDegZYX();
		m_rotationChanged = true;

		//We also update the transform's up, right and forward local vectors
		m_right = m_rotation.Rotate(Math::Vec3::right);
		m_up = m_rotation.Rotate(Math::Vec3::up);
		m_forward = m_rotation.Rotate(Math::Vec3::forward);

		// If we rotate parent, children move in space
		if (m_children.size() > 0)
			m_positionChanged = true;
	}

	void Transform::Serialize(json& _j)
	{
		Math::Vec3 localPosition = GetLocalPosition();
		Math::Vec3 localScale = GetLocalScale();
		Math::Quat localRotation = GetLocalRotation();
		Math::Vec3 localEulerAngles = GetLocalEulerAngles();

		_j = json{
			{"LocalPosition", { localPosition.x, localPosition.y, localPosition.z }},
			{"LocalScale", { localScale.x, localScale.y, localScale.z }},
			{"LocalRotation", { localRotation.w, localRotation.x, localRotation.y, localRotation.z }},
			{"LocalEulerAngles", { localEulerAngles.x, localEulerAngles.y, localEulerAngles.z }}
		};
	}

	void Transform::Deserialize(const json& _j)
	{
		float localPosition[3];
		float localScale[3];
		float localRotation[4];
		float localEulerAngles[3];

		_j.at("LocalPosition").get_to(localPosition);
		_j.at("LocalScale").get_to(localScale);
		_j.at("LocalRotation").get_to(localRotation);
		_j.at("LocalEulerAngles").get_to(localEulerAngles);
		
		SetLocalPosition(localPosition[0], localPosition[1], localPosition[2]);
		SetLocalScale(localScale[0], localScale[1], localScale[2]);
		SetLocalRotation(localRotation[0], localRotation[1], localRotation[2], localRotation[3]);
		SetLocalEulerAngles(localEulerAngles[0], localEulerAngles[1], localEulerAngles[2]);

		SetPositionChanged(true);
		SetScaleChanged(true);
		SetRotationChanged(true);
	}
}