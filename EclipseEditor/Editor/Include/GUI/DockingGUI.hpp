#pragma once

namespace Windowing
{
	class IWindow;
}

namespace GUI
{
	class DockingGUI
	{
	public:
		DockingGUI() = default;
		~DockingGUI() = default;

		void Start();
		void End(Windowing::IWindow* _window);

	private:

	};
}