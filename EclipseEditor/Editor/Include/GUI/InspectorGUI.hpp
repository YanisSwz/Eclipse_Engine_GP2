#pragma once

namespace Core
{
	class GameObject;
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

	};
}