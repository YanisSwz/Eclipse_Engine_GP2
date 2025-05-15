#pragma once
#include "Maths.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui-knobs.h"
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
	bool DragInt(const char* _label, const char* _invisibleLabel, int* _int, float _speed = 0.1f, int _minValue = 0.f, int _maxValue = 0.f, const char* _format = "%.3f", float _maxColumnWidth = 100.f);
	bool DragFloat(const char* _label, const char* _invisibleLabel, float* _float, float _speed = 0.1f, float _minValue = 0.f, float _maxValue = 0.f, const char* _format = "%.3f", float _maxColumnWidth = 100.f);
	bool DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue = 0.0f, float _maxColumnWidth = 100.f);
	bool DragUniformVec3XYZ(const char* _label, Math::Vec3& _vec3, bool& _isLocked, Math::Vec3& _scaleFactor, float _resetValue = 0.0f, float _maxColumnWidth = 100.f);
	bool DragColorRGBA(const char* _label, Math::Vec4& _vec4, float _resetValue = 0.0f, float _maxColumnWidth = 100.f);
	void DrawImage(const char* _imageName, unsigned int _imageID, float _size = 50.f);
	bool ComboFilter(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values, float _maxColumnWidth = 100.f);
	bool ComboBox(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values, float _maxColumnWidth = 100.f);
	bool CheckBox(const char* _checkBoxName, const char* _invisibleCheckBoxName, bool* _boolean, float _maxColumnWidth = 100.f);
	bool FloatSlider(const char* _sliderName, float* value, float _min, float _max, const char* _format);
	void ColorEdit4(const char* _label, Math::Vec4& _color, ImGuiColorEditFlags flags = 0, float _maxColumnWidth = 100.f);
	bool AudioChannel(const char* _label, float& _sliderValue, bool _canDelete, bool& _deleted, ImVec2 _size, float _offset = 0.f);
	bool AudioChannel(const char* _label, float* _stereoVolume, float _currentVolume, float& _sliderValue, ImVec2 _size, float _offset = 0.f);
	bool AudioChannel(const char* _label, bool _isPlaying, float* _pan, float& _sliderValue, ImVec2 _size, float _offset = 0.f, int ID = 0);
	bool AudioChannel3D(const char* _label, bool _isPlaying, float& _sliderValue, ImVec2 _size, float _offset = 0.f, int ID = 0);

	ImVec4 ColorToVec4(Logging::COLOR _color);
	void ColoredText(const char* _message, Logging::COLOR _color);
}