#pragma once

namespace Core
{
	class GameObject;
	class Transform;
	class Model;
	class BoxCollider;
	class CapsuleCollider;
	class MeshCollider;
}

namespace GUI
{
	class InspectorGUI
	{
	public:
		InspectorGUI();
		~InspectorGUI();

		void Draw(Core::GameObject* _crtGOselected);

	private:
		void DrawTransformComponent(Core::Transform* _transform);
		void DrawModelComponent(Core::Model* _model);
		void DrawBoxColliderComponent(Core::BoxCollider* _collider);
		void DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider);
		void DrawMeshColliderComponent(Core::MeshCollider* _collider);

	};
}