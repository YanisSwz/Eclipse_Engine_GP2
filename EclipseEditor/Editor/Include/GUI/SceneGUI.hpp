#pragma once

namespace GUI
{
	class SceneGUI
	{
	public:
		SceneGUI();
		~SceneGUI();

		void Draw(const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY);

	private:

	};
}