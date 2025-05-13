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

	bool DragInt(const char* _label, const char* _invisibleLabel, int* _int, float _speed, int _minValue, int _maxValue, const char* _format, float _maxColumnWidth)
	{
		std::string invisibleLabel = "##";
		invisibleLabel.append(_invisibleLabel);
		ImGui::PushID(invisibleLabel.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
		ImGui::Text(_label);
		ImGui::NextColumn();

		_speed; _minValue; _maxValue; _format;

		if (ImGui::DragInt(invisibleLabel.c_str(), _int, _speed, _minValue, _maxValue))
		{
			ImGui::Columns(1);
			ImGui::PopID();
			return true;
		}
		ImGui::Columns(1);
		ImGui::PopID();
		return false;
	}

	bool DragFloat(const char* _label, const char* _invisibleLabel, float* _float, float _speed, float _minValue, float _maxValue, const char* _format, float _maxColumnWidth)
	{
		std::string invisibleLabel = "##";
		invisibleLabel.append(_invisibleLabel);
		ImGui::PushID(invisibleLabel.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 3.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
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

	bool DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue, float _maxColumnWidth)
	{
		bool changed = false;

		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		// Draw widget label
		ImGui::PushID(_label);
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
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
		{
			_vec3.x = _resetValue;
			changed = true;
		}
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
		{
			_vec3.y = _resetValue;
			changed = true;
		}
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
		{
			_vec3.z = _resetValue;
			changed = true;
		}
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

	bool DragUniformVec3XYZ(const char* _label, Math::Vec3& _vec3, bool& _isLocked, Math::Vec3& _scaleFactor, float _resetValue, float _maxColumnWidth)
	{
		bool changed = false;

		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		// Draw widget label
		ImGui::PushID(_label);
		ImGui::Columns(3, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 8.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth / 2.f);
		ImGui::Text(_label);
		ImGui::NextColumn();

		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() / 8.f);
		else
			ImGui::SetColumnWidth(1, _maxColumnWidth / 2.f);
		ImGui::Checkbox("##", &_isLocked);
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
		{
			if (_vec3.x != _resetValue)
			{
				if (_isLocked)
				{
					if (_vec3.x == 0.f)
					{
						_vec3.y = _resetValue * _scaleFactor.y;
						_vec3.z = _resetValue * _scaleFactor.z;
					}
					else
					{
						_vec3.y = _resetValue * (_vec3.y / _vec3.x);
						_vec3.z = _resetValue * (_vec3.z / _vec3.x);
					}
				}
				_vec3.x = _resetValue;
				changed = true;
			}
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		float tempX = _vec3.x;
		if (ImGui::DragFloat("##X", &_vec3.x, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			if (_isLocked)
			{
				if (tempX == 0.f)
				{
					_vec3.y = _vec3.x * _scaleFactor.y;
					_vec3.z = _vec3.x * _scaleFactor.z;
				}
				else
				{
					_scaleFactor.y = _vec3.y / tempX;
					_scaleFactor.z = _vec3.z / tempX;
					float factor = _vec3.x / tempX;
					_vec3.y *= factor;
					_vec3.z *= factor;
				}
			}
			changed = true;
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw Y
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
		{
			if (_vec3.y != _resetValue)
			{
				if (_isLocked)
				{
					if (_vec3.y == 0.f)
					{
						_vec3.x = _resetValue * _scaleFactor.x;
						_vec3.z = _resetValue * _scaleFactor.z;
					}
					else
					{
						_vec3.x = _resetValue * (_vec3.x / _vec3.y);
						_vec3.z = _resetValue * (_vec3.z / _vec3.y);
					}
				}
				_vec3.y = _resetValue;
				changed = true;
			}
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		float tempY = _vec3.y;
		if (ImGui::DragFloat("##Y", &_vec3.y, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			if (_isLocked)
			{
				if (tempY == 0.f)
				{
					_vec3.x = _vec3.y * _scaleFactor.x;
					_vec3.z = _vec3.y * _scaleFactor.z;
				}
				else
				{
					_scaleFactor.x = _vec3.x / tempY;
					_scaleFactor.z = _vec3.z / tempY;
					float factor = _vec3.y / tempY;
					_vec3.x *= factor;
					_vec3.z *= factor;
				}
			}
			changed = true;
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw Z
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 3.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
		{
			if (_vec3.z != _resetValue)
			{
				if (_isLocked)
				{
					if (_vec3.z == 0.f)
					{
						_vec3.x = _resetValue * _scaleFactor.x;
						_vec3.y = _resetValue * _scaleFactor.y;
					}
					else
					{
						_vec3.x = _resetValue * (_vec3.x / _vec3.z);
						_vec3.y = _resetValue * (_vec3.y / _vec3.z);
					}
				}
				_vec3.z = _resetValue;
				changed = true;
			}
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		float tempZ = _vec3.z;
		if (ImGui::DragFloat("##Z", &_vec3.z, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			if (_isLocked)
			{
				if (tempZ == 0.f)
				{
					_vec3.x = _vec3.z * _scaleFactor.x;
					_vec3.y = _vec3.z * _scaleFactor.y;
				}
				else
				{
					_scaleFactor.x = _vec3.x / tempZ;
					_scaleFactor.y = _vec3.y / tempZ;
					float factor = _vec3.z / tempZ;
					_vec3.x *= factor;
					_vec3.y *= factor;
				}
			}
			changed = true;
		}
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return changed;
	}

	bool DragColorRGBA(const char* _label, Math::Vec4& _vec4, float _resetValue, float _maxColumnWidth)
	{
		bool changed = false;
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		// Draw widget label
		ImGui::PushID(_label);
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 5.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
		ImGui::Text(_label);
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = ImGui::GetFrameHeight();
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// Draw R
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 4.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("R", buttonSize))
		{
			_vec4.x = _resetValue;
			changed = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##R", &_vec4.x, 0.1f, 0.f, 255.f, "%.0f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw G
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 4.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("G", buttonSize))
		{
			_vec4.y = _resetValue;
			changed = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##G", &_vec4.y, 0.1f, 0.f, 255.f, "%.0f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw B
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 4.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("B", buttonSize))
		{
			_vec4.z = _resetValue;
			changed = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##B", &_vec4.z, 0.1f, 0.f, 255.f, "%.0f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// Draw A
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 4.f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, _vec4.w / 255.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.9f, 0.9f, _vec4.w / 255.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.8f, 0.8f, _vec4.w / 255.f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("A", buttonSize))
		{
			_vec4.w = _resetValue;
			changed = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		changed |= ImGui::DragFloat("##A", &_vec4.w, 0.1f, 0.f, 255.f, "%.0f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);


		// Color Picker PopUp
		ImVec4 ImVec4Color{ _vec4.x / 255.f, _vec4.y / 255.f, _vec4.z / 255.f, _vec4.w / 255.f };
		if (ImGui::ColorButton("Particle Color Begin", ImVec4Color))
			ImGui::OpenPopup("ColorPickerPopUp");

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("Color4", &ImVec4Color.x, sizeof(ImVec4));
			ImGui::Text(_label);
			ImGui::SameLine();
			ImGui::ColorButton("Particle Color Begin", ImVec4Color);
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Color4"))
			{
				IM_ASSERT(payload->DataSize == sizeof(ImVec4));
				ImVec4 payload_n = *static_cast<ImVec4*>(payload->Data);
				_vec4 = { payload_n.x * 255.f, payload_n.y * 255.f, payload_n.z * 255.f, payload_n.w * 255.f };
			}
			ImGui::EndDragDropTarget();
		}

		if (ImGui::BeginPopup("ColorPickerPopUp"))
		{
			const float square_sz = ImGui::GetFrameHeight();
			ImGuiColorEditFlags picker_flags = ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf;
			ImGui::SetNextItemWidth(square_sz * 12.0f);

			float colorPick4[4] = { _vec4.x / 255.f, _vec4.y / 255.f, _vec4.z / 255.f, _vec4.w / 255.f };
			if (ImGui::ColorPicker4("##picker", colorPick4, picker_flags))
				_vec4 = { colorPick4[0] * 255.f, colorPick4[1] * 255.f, colorPick4[2] * 255.f, colorPick4[3] * 255.f };
			ImGui::EndPopup();
		}

		ImGui::PopID();

		return changed;
	}

	void DrawImage(const char* _imageName, unsigned int _imageID, float _size)
	{
		ImVec2 uv_min = ImVec2(0.0f, 1.0f);
		ImVec2 uv_max = ImVec2(1.0f, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
		ImGui::ImageButton(_imageName, _imageID, ImVec2(_size, _size), uv_min, uv_max, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(3);
	}

	bool ComboFilter(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values, float _maxColumnWidth)
	{
		std::string invisibleComboName = "##";
		invisibleComboName.append(_comboName).append("(w/ filter)");
		ImGui::PushID(invisibleComboName.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
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
						ImGui::Columns(1);
						return true;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopID();
		ImGui::Columns(1);
		return false;
	}

	bool ComboBox(const char* _comboName, std::string* _crtValue, std::vector<std::string> _values, float _maxColumnWidth)
	{
		std::string invisibleComboName = "##";
		invisibleComboName.append(_comboName).append("(w/ filter)");
		ImGui::PushID(invisibleComboName.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
		ImGui::Text(_comboName);
		ImGui::NextColumn();
		if (ImGui::BeginCombo(invisibleComboName.c_str(), _crtValue->c_str()))
		{
			for (int i = 0; i < _values.size(); ++i)
			{
				const bool is_selected = (*_crtValue == _values[i]);
				if (ImGui::Selectable(_values[i].c_str(), is_selected))
				{
					*_crtValue = _values[i];
					ImGui::EndCombo();
					ImGui::PopID();
					ImGui::Columns(1);
					return true;
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopID();
		ImGui::Columns(1);
		return false;
	}

	bool CheckBox(const char* _checkBoxName, const char* _invisibleCheckBoxName, bool* _boolean, float _maxColumnWidth)
	{
		std::string invisibleCheckBoxName = "##";
		invisibleCheckBoxName.append(_invisibleCheckBoxName);
		ImGui::PushID(invisibleCheckBoxName.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
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

	bool FloatSlider(const char* _sliderName, float* value, float _min, float _max, const char* _format)
	{
		return ImGui::SliderFloat(_sliderName, value, _min, _max, _format);
	}

	void ColorEdit4(const char* _label, Math::Vec4& _color, ImGuiColorEditFlags flags, float _maxColumnWidth)
	{
		std::string invisibleLabel = std::string("##") + _label;
		ImGui::PushID(invisibleLabel.c_str());
		ImGui::Columns(2, 0, false);
		if ((ImGui::GetWindowWidth() / 4.f) < _maxColumnWidth)
			ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 4.f);
		else
			ImGui::SetColumnWidth(0, _maxColumnWidth);
		ImGui::Text(_label);
		ImGui::NextColumn();
		float col[4]{ _color.x / 255.f, _color.y / 255.f, _color.z / 255.f, _color.w / 255.f };
		ImGui::ColorEdit4(invisibleLabel.c_str(), col, flags);
		_color.x = col[0] * 255.f;
		_color.y = col[1] * 255.f;
		_color.z = col[2] * 255.f;
		_color.w = col[3] * 255.f;
		ImGui::Columns(1);
		ImGui::PopID();
	}

	bool AudioChannel(const char* _label, float* _stereoVolume, float& _sliderValue, ImVec2 _size, float _offset)
	{
		ImGui::SetCursorPosX(8.f + _offset);
		float alpha = ImGui::GetStyle().Alpha;
		ImGui::BeginDisabled();
		ImGui::GetStyle().Alpha = alpha;
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.25f, 0.25f, 0.25f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(1.f, 1.f, 1.f, 1.f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2);
		std::string label = "##";
		label += _label;
		label += "StereoVolume";
		ImGui::PlotHistogram(label.c_str(), _stereoVolume, 2, 0, NULL, 0.0f, 1.0f, _size);

		float vol = 0.f;
		if (_stereoVolume[0] > _stereoVolume[1])
			vol = _stereoVolume[0];
		else
			vol = _stereoVolume[1];
		ImGui::SameLine();
		ImGui::SetCursorPosX(8.f + _offset);
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(1.f, 1.f, 1.f, 1.f));
		label = "##";
		label += _label;
		label += "MaxVolume";
		ImGui::VSliderFloat(label.c_str(), _size, &vol, 0.0f, 1.0f, "");
		ImGui::EndDisabled();
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar();

		ImGui::SameLine();

		auto* colors = ImGui::GetStyle().Colors;
		ImVec4 color = ImVec4(colors[ImGuiCol_Button].x, colors[ImGuiCol_Button].y, colors[ImGuiCol_Button].z, alpha);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, color);
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.5f, 0.5f, 0.5f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.75f, 0.75f, 0.75f, 1.f));
		ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 15);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderThickness, 0.35f);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderContrast, 0.75f);

		label = "##";
		label += _label;
		label += "Volume";
		bool changed = ImGui::VSliderFloat(label.c_str(), _size, &_sliderValue, 0.0f, 1.0f, "");
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetTooltip("%.3f", _sliderValue);
		ImGui::PopStyleColor(5);
		ImGui::PopStyleVar(3);

		ImGui::SameLine();
		ImGui::SetCursorPos(ImVec2(8.f + _offset, 16.f + _size.y + ImGui::GetFontSize())); 
		// We wrap the text to not overflow on other audio channels
		label = _label;
		for(int i = 12; i < label.size(); i += 12)
			label.insert(i, "\n"); 
		ImGui::Text(label.c_str());

		return changed;
	}

	bool AudioChannel(const char* _label, bool _isPlaying, float* _pan, float& _sliderValue, ImVec2 _size, float _offset, int ID)
	{
		bool changed = false;
		ImGui::SetCursorPosX(8.f + _offset);
		float alpha = ImGui::GetStyle().Alpha;
		ImGui::BeginDisabled();
		ImGui::GetStyle().Alpha = alpha;
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.25f, 0.f, 0.25f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2);
		std::string label = "##";
		label += _label;
		label += "IsPlaying" + std::to_string(ID);
		
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(1.f, 0.75f, 0.f, 1.f));
		ImGui::RadioButton(label.c_str(), _isPlaying);
		ImGui::EndDisabled();
		ImGui::PopStyleColor();

		ImGui::SameLine();
		ImGui::SetCursorPosX(8.f + _offset);
		ImGui::SetCursorPosY(_size.y - 85.f);
		label = "Pan " + std::to_string(ID);
		if (ImGuiKnobs::Knob(label.c_str(), _pan, -1.0f, 1.0f, 0.01f, "%.2f", ImGuiKnobVariant_Tick, 60.f))
			changed = true;
		if (ImGui::IsItemActive() && ImGui::IsMouseDoubleClicked(0))
		{
			*_pan = 0.f;
			changed = true;
		}
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();

		ImGui::SameLine();

		auto* colors = ImGui::GetStyle().Colors;
		ImVec4 color = ImVec4(colors[ImGuiCol_Button].x, colors[ImGuiCol_Button].y, colors[ImGuiCol_Button].z, alpha);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, color);
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.5f, 0.5f, 0.5f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.75f, 0.75f, 0.75f, 1.f));
		if(alpha != 1.f)
			ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0);
		else
			ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 10);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderThickness, 0.25f);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderContrast, 0.75f);

		label = "##";
		label += _label;
		label += "Volume" + std::to_string(ID);
		if (ImGui::VSliderFloat(label.c_str(), _size, &_sliderValue, 0.0f, 1.0f, ""))
			changed = true;
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetItemTooltip("%.3f", _sliderValue);
		ImGui::PopStyleColor(5);
		ImGui::PopStyleVar(3);
		ImGui::GetStyle().Alpha = alpha;

		ImGui::SameLine();
		ImGui::SetCursorPos(ImVec2(8.f + _offset, 16.f + _size.y + ImGui::GetFontSize()));
		// We wrap the text to not overflow on other audio channels
		label = _label;
		for (int i = 12; i < label.size(); i += 12)
			label.insert(i, "\n");
		ImGui::Text(label.c_str());

		return changed;
	}

	bool AudioChannel3D(const char* _label, bool _isPlaying, float& _sliderValue, ImVec2 _size, float _offset, int ID)
	{
		bool changed = false;
		ImGui::SetCursorPosX(8.f + _offset);
		float alpha = ImGui::GetStyle().Alpha;
		ImGui::BeginDisabled();
		ImGui::GetStyle().Alpha = alpha;
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.25f, 0.25f, 0.25f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2);
		std::string label = "##";
		label += _label;
		label += "IsPlaying" + std::to_string(ID);
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(1.f, 0.75f, 0.f, 1.f));
		ImGui::RadioButton(label.c_str(), _isPlaying);
		ImGui::EndDisabled();
		ImGui::PopStyleColor();

		auto* colors = ImGui::GetStyle().Colors;
		ImVec4 color = ImVec4(colors[ImGuiCol_Button].x, colors[ImGuiCol_Button].y, colors[ImGuiCol_Button].z, alpha);
		ImGui::SameLine();
		ImGui::SetCursorPosX(8.f + _offset);
		ImGui::SetCursorPosY(_size.y);
		ImGui::SetWindowFontScale(1.5f);
		ImGui::TextColored(color, "3D  ");
		ImGui::SetWindowFontScale(1.f);

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, color);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, color);
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.5f, 0.5f, 0.5f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.75f, 0.75f, 0.75f, 1.f));
		if (alpha != 1.f)
			ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0);
		else
			ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 10);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderThickness, 0.25f);
		ImGui::PushStyleVar(ImGuiStyleVar_SliderContrast, 0.75f);

		label = "##";
		label += _label;
		label += "Volume" + std::to_string(ID);
		if (ImGui::VSliderFloat(label.c_str(), _size, &_sliderValue, 0.0f, 1.0f, ""))
			changed = true;
		if (ImGui::IsItemActive() || ImGui::IsItemHovered())
			ImGui::SetItemTooltip("%.3f", _sliderValue);
		ImGui::PopStyleColor(5);
		ImGui::PopStyleVar(3);

		ImGui::SameLine();
		ImGui::SetCursorPos(ImVec2(8.f + _offset, 16.f + _size.y + ImGui::GetFontSize()));
		// We wrap the text to not overflow on other audio channels
		label = _label;
		for (int i = 12; i < label.size(); i += 12)
			label.insert(i, "\n");
		ImGui::Text(label.c_str());

		return changed;
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