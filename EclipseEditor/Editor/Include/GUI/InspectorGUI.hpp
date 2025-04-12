#pragma once

namespace Core
{
	class GameObject;
	class Transform;
	class Model;
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

	};
}