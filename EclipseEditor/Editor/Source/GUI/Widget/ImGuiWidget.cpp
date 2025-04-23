#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	void BeginNewFrame()
	{
#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_NewFrame();
#endif // ImGuiImplementOpenGL
#ifdef ImGuiImplementGLFW
		ImGui_ImplGlfw_NewFrame();
#endif // ImGuiImplementGLFW
		ImGui::NewFrame();
	}

	void EndFrame()
	{
		ImGui::EndFrame();
	}

	void RenderGUI()
	{
		ImGui::Render();

#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // ImGuiImplementOpenGL
	}

	bool DragFloat(const char* _label, const char* _invisibleLabel, float* _float, float _speed, float _minValue, float _maxValue, const char* _format)
	{
		std::string invisibleLabel = "##";
		invisibleLabel.append(_invisibleLabel);
		ImGui::PushID(invisibleLabel.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.f);
		ImGui::Text(_label);
		ImGui::NextColumn();

		if (ImGui::DragFloat(invisibleLabel.c_str(), _float, _speed, _minValue, _maxValue, _format))
		{
			ImGui::Columns(1);
			ImGui::PopID();
			return true;
		}
		ImGui::Columns(1);
		ImGui::PopID();
		return false;
	}

	bool DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue, float _columnWidth)
	{
		bool changed = false;

		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		// Draw widget label
		ImGui::PushID(_label);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, _columnWidth);
		ImGui::Text(_label);
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = ImGui::GetFrameHeight();
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// Draw X
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			_vec3.x = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##X", &_vec3.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw Y
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			_vec3.y = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##Y", &_vec3.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw Z
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			_vec3.z = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##Z", &_vec3.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return changed;
	}

	bool DragQuatXYZ(const char* _label, Math::Quat& _quat, float _resetValue, float _columnWidth)
	{
		bool changed = false;

		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];
		Math::Vec3 vec = _quat.GetEulerAnglesDegXYZ();

		// Draw widget label
		ImGui::PushID(_label);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, _columnWidth);
		ImGui::Text(_label);
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = ImGui::GetFrameHeight();
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// Draw X
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			vec.x = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##X", &vec.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();


		// Draw Y
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			vec.y = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##Y", &vec.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw Z
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			vec.z = _resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##Z", &vec.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();

		_quat = Math::Quat::QuaternionEuler(vec.x, vec.y, vec.z);

		return changed;
	}

	void DrawImage(const char* _imageName, unsigned int _imageID, float _size)
	{
		ImVec2 uv_min = ImVec2(0.0f, 1.0f);
		ImVec2 uv_max = ImVec2(1.0f, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
		ImGui::ImageButton(_imageName, _imageID, ImVec2(_size, _size), uv_min, uv_max, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::PopStyleVar();
	}

	bool ComboFilter(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values)
	{
		std::string invisibleComboName = "##";
		invisibleComboName.append(_comboName).append("(w/ filter)");
		ImGui::PushID(invisibleComboName.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.f);
		ImGui::Text(_comboName);
		ImGui::NextColumn();
		if (ImGui::BeginCombo(invisibleComboName.c_str(), _crtValue->c_str()))
		{
			ImGuiTextFilter filter;
			if (ImGui::IsWindowAppearing())
			{
				ImGui::SetKeyboardFocusHere();
				filter.Clear();
			}
			filter.Draw("##Filter", -FLT_MIN);

			for (int i = 0; i < _values.size(); ++i)
			{
				const bool is_selected = (*_crtValue == _values[i]);
				if (filter.PassFilter(_values[i].c_str()))
				{
					if (ImGui::Selectable(_values[i].c_str(), is_selected))
					{
						*_crtValue = _values[i];
						ImGui::EndCombo();
						ImGui::PopID();
						return true;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopID();
		return false;
	}

	bool CheckBox(const char* _checkBoxName, const char* _invisibleCheckBoxName, bool* _boolean)
	{
		std::string invisibleCheckBoxName = "##";
		invisibleCheckBoxName.append(_invisibleCheckBoxName);
		ImGui::PushID(invisibleCheckBoxName.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.f);
		ImGui::Text(_checkBoxName);
		ImGui::NextColumn();

		if (ImGui::Checkbox(invisibleCheckBoxName.c_str(), _boolean))
		{
			ImGui::Columns(1);
			ImGui::PopID();
			return true;
		}
		ImGui::Columns(1);
		ImGui::PopID();
		return false;
	}

	ImVec4 ColorToVec4(Logging::COLOR _color)
	{
		switch (_color)
		{
		case Logging::COLOR::WHITE:
			return ImVec4(1.f, 1.f, 1.f, 1.f);
		case Logging::COLOR::RED:
			return ImVec4(1.f, 0.f, 0.f, 1.f);
		case Logging::COLOR::GREEN:
			return ImVec4(0.f, 1.f, 0.f, 1.f);
		case Logging::COLOR::YELLOW:
			return ImVec4(1.f, 1.f, 0.f, 1.f);
		case Logging::COLOR::BLUE:
			return ImVec4(0.f, 0.f, 1.f, 1.f);
		case Logging::COLOR::PURPLE:
			return ImVec4(0.5f, 0.f, 0.5f, 1.f);
		case Logging::COLOR::CYAN:
			return ImVec4(0.f, 1.f, 1.f, 1.f);
		default:
			return ImVec4(1.f, 1.f, 1.f, 1.f);
		}
	}

	void ColoredText(const char* _message, Logging::COLOR _color)
	{
		ImGui::TextColored(ColorToVec4(_color), _message);
	}
}