#pragma once

namespace Core
{
	class Scene;
	class GameObject;
}

namespace GUI
{
	class HierarchyGUI
	{
	public:
		HierarchyGUI();
		~HierarchyGUI();

		Core::GameObject* Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected);

	private:

	};
}