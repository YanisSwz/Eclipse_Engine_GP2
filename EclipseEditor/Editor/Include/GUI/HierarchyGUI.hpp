#pragma once

namespace Core
{
	class Scene;
	class GameObject;
	class Transform;
}

namespace GUI
{
	class HierarchyGUI
	{
	public:
		HierarchyGUI();
		~HierarchyGUI();

		Core::GameObject* Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected);
		Core::GameObject* RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected);

	private:

	};
}