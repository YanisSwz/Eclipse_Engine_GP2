#pragma once

namespace Core
{
	class Camera;
}

namespace GUI
{
	class GameGUI
	{
	public:
		GameGUI() = default;
		~GameGUI() = default;

		void Draw(Core::Camera* _currentCam, const unsigned int _textureID, int& _windowWidth, int& _windowHeight);

	private:
	};
}