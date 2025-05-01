#pragma once
#include "Maths.hpp"
#include "Component.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class Transform : public Component
	{
	public:
		static meta::factory<Transform> factory;

		ECLIPSE_ENGINE Transform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE ~Transform();

		// Hierarchy 
		ECLIPSE_ENGINE void SetParent(Transform* _parent);
		ECLIPSE_ENGINE void AddChild(Transform* _child);
		ECLIPSE_ENGINE void RemoveChild(Transform* _child);

		// Updates
		ECLIPSE_ENGINE void Update(bool _positionChanged = false, bool _scaleChanged = false, bool _rotationChanged = false);
		ECLIPSE_ENGINE void StartOverride();
		ECLIPSE_ENGINE void UpdateOverride();
		ECLIPSE_ENGINE void EndOverride();
		ECLIPSE_ENGINE void Destroy() override;

		// Getters
		ECLIPSE_ENGINE std::vector<Transform*> GetChildren() const;
		ECLIPSE_ENGINE Math::Mat4 GetTransformMatrix() const;
		ECLIPSE_ENGINE Transform* GetParent() const;
		ECLIPSE_ENGINE bool IsSelected() const;
		ECLIPSE_ENGINE bool HasPositionChanged() const;
		ECLIPSE_ENGINE bool HasScaleChanged() const;
		ECLIPSE_ENGINE bool HasRotationChanged() const;
		ECLIPSE_ENGINE Math::Vec3 GetPosition() const;
		ECLIPSE_ENGINE Math::Vec3 GetScale() const;
		ECLIPSE_ENGINE Math::Quat GetRotation() const;
		ECLIPSE_ENGINE Math::Vec3 GetEulerAngles() const;
		ECLIPSE_ENGINE Math::Vec3 GetLocalPosition() const;
		ECLIPSE_ENGINE Math::Vec3 GetLocalScale() const;
		ECLIPSE_ENGINE Math::Quat GetLocalRotation() const;
		ECLIPSE_ENGINE Math::Vec3 GetLocalEulerAngles() const;
		ECLIPSE_ENGINE Math::Vec3 GetRight() const;
		ECLIPSE_ENGINE Math::Vec3 GetUp() const;
		ECLIPSE_ENGINE Math::Vec3 GetForward() const;
		ECLIPSE_ENGINE Math::Vec3& GetLocalPositionRef();
		ECLIPSE_ENGINE Math::Vec3& GetLocalScaleRef();
		ECLIPSE_ENGINE Math::Vec3& GetLocalEulerAnglesRef();


		// Setters
		ECLIPSE_ENGINE void SetPosition(Math::Vec3 _vec);
		ECLIPSE_ENGINE void SetScale(Math::Vec3 _vec) ;
		ECLIPSE_ENGINE void SetRotation(Math::Quat _quat) ;
		ECLIPSE_ENGINE void SetEulerAngles(Math::Vec3 _vec) ;
		ECLIPSE_ENGINE void SetLocalPosition(Math::Vec3 _vec) ;
		ECLIPSE_ENGINE void SetLocalScale(Math::Vec3 _vec) ;
		ECLIPSE_ENGINE void SetLocalRotation(Math::Quat _quat) ;
		ECLIPSE_ENGINE void SetLocalEulerAngles(Math::Vec3 _vec) ;
		ECLIPSE_ENGINE void SetPosition(float _x , float _y, float _z);
		ECLIPSE_ENGINE void SetScale(float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetRotation(float _w, float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetEulerAngles(float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetLocalPosition(float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetLocalScale(float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetLocalRotation(float _w, float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetLocalEulerAngles(float _x, float _y, float _z) ;
		ECLIPSE_ENGINE void SetPositionChanged();
		ECLIPSE_ENGINE void SetScaleChanged();
		ECLIPSE_ENGINE void SetRotationChanged();

	private:
		Math::Mat4 GetLocalTransformMatrix() const;
		void UpdatePosition();
		void UpdateScale();
		void UpdateRotation();

		// Hierarchy
		Transform* m_parent = nullptr;
		std::vector<Transform*> m_children{};

		// Update
		bool m_isSelected = false;
		bool m_positionChanged = false;
		bool m_scaleChanged = false;
		bool m_rotationChanged = false;

		//#### Data ####
	
		// Global position
		Math::Vec3 m_position{ 0.f, 0.f, 0.f };
		// Global scale
		Math::Vec3 m_scale{ 1.f, 1.f, 1.f };
		// Global rotation
		Math::Quat m_rotation{ 1.f, 0.f, 0.f, 0.f };
		Math::Vec3 m_eulerAngles{ 0.f, 0.f, 0.f };

		Math::Vec3 m_localPosition{ 0.f, 0.f, 0.f };
		Math::Vec3 m_localScale{ 1.f, 1.f, 1.f };
		Math::Quat m_localRotation{ 1.f, 0.f, 0.f, 0.f };
		Math::Vec3 m_localEulerAngles{ 0.f, 0.f, 0.f };

		Math::Vec3 m_right{1.f, 0.f, 0.f};
		Math::Vec3 m_up{ 0.f, 1.f, 0.f };
		Math::Vec3 m_forward{ 0.f, 0.f, 1.f };
	};

	void to_json(json& _j, const Transform& _transform);
	void from_json(const json& _j, Transform& _transform);
}

#include "Transform.inl"