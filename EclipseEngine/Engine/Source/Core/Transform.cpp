#include "Transform.hpp"
#include <utility>

namespace Core
{
	Transform::Transform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		localPosition = _translation, position = _translation;
		rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z), localRotation = rotation;
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
		if (m_parent != nullptr)
		{
			Math::Mat4 transform = m_parent->GetTransformMatrix() * GetLocalTransformMatrix();

			// Extract new position, scale and rotation
			position = GetTranslation(transform);
			scale = GetScale(transform);
			rotation = GetRotation(transform);
		}
		else
		{
			position = localPosition;
			scale = localScale;
			rotation = localRotation;
		}
		
		for(int i = 0; i < m_children.size(); ++i)
		{
			m_children[i]->Update();
		}
	}

	Math::Vec3 Transform::GetTranslation(Math::Mat4& _mat) const
	{
		return Math::Vec3(_mat[0][3], _mat[1][3], _mat[2][3]);
	}

	Math::Vec3 Transform::GetScale(Math::Mat4& _mat) const
	{
		return Math::Vec3
		(
			Math::Vec3(_mat[0][0], _mat[1][0], _mat[2][0]).Norm(),
			Math::Vec3(_mat[0][1], _mat[1][1], _mat[2][1]).Norm(),
			Math::Vec3(_mat[0][2], _mat[1][2], _mat[2][2]).Norm()
		);
	}

	Math::Quat Transform::GetRotation(Math::Mat4& _mat) const
	{
		// Normalize Scale from Matrix4x4
		float m00 = _mat[0][0] / scale.x;
		float m01 = _mat[0][1] / scale.y;
		float m02 = _mat[0][2] / scale.z;
		float m10 = _mat[1][0] / scale.x;
		float m11 = _mat[1][1] / scale.y;
		float m12 = _mat[1][2] / scale.z;
		float m20 = _mat[2][0] / scale.x;
		float m21 = _mat[2][1] / scale.y;
		float m22 = _mat[2][2] / scale.z;

		Math::Quat q = Math::Quat::Identity();

		//FIRST METHOD
		/*q.w = sqrtf(std::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
		q.x = sqrtf(std::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
		q.y = sqrtf(std::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
		q.z = sqrtf(std::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
		q.x *= Math::Tools::Sign(q.x * (m21 - m12));
		q.y *= Math::Tools::Sign(q.y * (m02 - m20));
		q.z *= Math::Tools::Sign(q.z * (m10 - m01));*/

		//SECOND METHOD
		q.w = sqrtf(1.f + m00 + m11 + m22)/2.f;
		q.x = (m21 - m12) / (4.f * q.w);
		q.y = (m02 - m20) / (4.f * q.w);
		q.z = (m10 - m01) / (4.f * q.w);;

		return Math::Quat::Normalized(q);
	}
	
}