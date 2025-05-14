#pragma once

namespace Core
{
	class Scene;
	class GameObject;
	class Transform;
}

namespace GUI
{
	class ContentBrowserGUI;

	class HierarchyGUI
	{
	public:
		HierarchyGUI() = default;
		~HierarchyGUI() = default;

		Core::GameObject* Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected, ContentBrowserGUI* _contentBrowser);
		Core::GameObject* RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected, ContentBrowserGUI* _contentBrowser);
	};
}