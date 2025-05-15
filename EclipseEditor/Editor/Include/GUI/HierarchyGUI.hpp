#pragma once
#include <string>

namespace Core
{
	class Scene;
	class GameObject;
	class Transform;
}

namespace Resource
{
	class Prefab;
}

namespace GUI
{
	class ContentBrowserGUI;

	class HierarchyGUI
	{
	public:
		HierarchyGUI() = default;
		~HierarchyGUI() = default;

		Core::GameObject* Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected);
		Core::GameObject* RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected);
	
	private:
		bool bIsPrefabWindowOpen = false;
		/// <summary>
		/// true = Prefab window to instantiate a Prefab // false = Prefab window to save as a Prefab
		/// </summary>
		bool bIsPrefabInstantiate = false;

		std::string m_crtPrefabName;
		Resource::Prefab* m_crtPrefab = nullptr;
	};
}