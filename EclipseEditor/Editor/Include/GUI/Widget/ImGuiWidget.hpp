#pragma once
#include "Maths.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Logger.hpp"
#include <vector>
#include <string>

#define ImGuiImplementGLFW
#define ImGuiImplementOpenGL

namespace GUI
{
	void BeginNewFrame();
	void EndFrame();
	void RenderGUI();
	void DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue = 0.0f, float _columnWidth = 100.0f);
	void DragQuatXYZ(const char* _label, Math::Quat& _quat, float _resetValue = 0.0f, float _columnWidth = 100.f);
	void DrawImage(const char* _imageName, unsigned int _imageID, float _size = 50.f);
	bool ComboFilter(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values);

	ImVec4 ColorToVec4(Logging::COLOR _color);
	void ColoredText(const char* _message, Logging::COLOR _color);
}