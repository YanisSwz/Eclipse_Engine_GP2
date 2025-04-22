#include "Transform.hpp"

namespace Core
{

	// Getters 
	inline Math::Mat4 Transform::GetTransformMatrix() const { return Math::Mat4::TRS(m_position, m_rotation, m_scale); };
	inline Math::Mat4 Transform::GetLocalTransformMatrix() const { return Math::Mat4::TRS(m_localPosition, m_localRotation, m_localScale); };
	inline Transform* Transform::GetParent() const { return m_parent; };
	inline bool Transform::IsSelected() const { return m_isSelected; }
	inline bool Transform::HasPositionChanged() const { return m_positionChanged; }
	inline bool Transform::HasScaleChanged() const { return m_scaleChanged; }
	inline bool Transform::HasRotationChanged() const { return m_rotationChanged; }
	inline Math::Vec3 Transform::GetPosition() const { return m_position; }
	inline Math::Vec3 Transform::GetScale() const { return m_scale; }
	inline Math::Quat Transform::GetRotation() const { return m_rotation; }
	inline Math::Vec3 Transform::GetEulerAngles() const { return m_eulerAngles; }
	inline Math::Vec3 Transform::GetLocalPosition() const { return m_localPosition; }
	inline Math::Vec3 Transform::GetLocalScale() const { return m_localScale; }
	inline Math::Quat Transform::GetLocalRotation() const { return m_localRotation; }
	inline Math::Vec3 Transform::GetLocalEulerAngles() const { return m_localEulerAngles; }
	inline Math::Vec3 Transform::GetRight() const { return m_right; }
	inline Math::Vec3 Transform::GetUp() const { return m_up; }
	inline Math::Vec3 Transform::GetForward() const { return m_forward; }
	inline Math::Vec3& Transform::GetLocalPositionRef() { return m_localPosition; }
	inline Math::Vec3& Transform::GetLocalScaleRef() { return m_localScale; }
	inline Math::Vec3& Transform::GetLocalEulerAnglesRef() { return m_localEulerAngles; }

	// Setters
	inline void Transform::SetLocalPosition(Math::Vec3 _vec) 
	{ 
		m_localPosition = _vec; 
		m_positionChanged = true; 
	}

	inline void Transform::SetLocalScale(Math::Vec3 _vec) 
	{ 
		m_localScale = _vec; 
		m_scaleChanged = true;
	}

	/// <summary>
	/// Notifies the transform that its position changed
	/// </summary>
	inline void Transform::SetPositionChanged() { m_positionChanged = true; }

	/// <summary>
	/// Notifies the transform that its scale changed
	/// </summary>
	inline void Transform::SetScaleChanged() { m_scaleChanged = true; }

	/// <summary>
	/// Notifies the transform that its rotation changed
	/// </summary>
	inline void Transform::SetRotationChanged() 
	{ 
		m_rotationChanged = true; 
		if (m_children.size() > 0)
			m_positionChanged = true;
	}
}