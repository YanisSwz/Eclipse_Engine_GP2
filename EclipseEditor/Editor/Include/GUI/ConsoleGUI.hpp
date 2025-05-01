#pragma once

namespace GUI
{
	class ConsoleGUI
	{
	public:
		ConsoleGUI() = default;
		~ConsoleGUI() = default;

		void Draw();

	private:
		int m_maxLineCount = 100;
	};
}