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

	void DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue, float _columnWidth)
	{
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
		ImGui::DragFloat("##X", &_vec3.x, 0.1f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Y", &_vec3.y, 0.1f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Z", &_vec3.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void DragQuatXYZ(const char* _label, Math::Quat& _quat, float _resetValue, float _columnWidth)
	{
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
		ImGui::DragFloat("##X", &vec.x, 0.1f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Y", &vec.y, 0.1f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Z", &vec.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();

		_quat = Math::Quat::QuaternionEuler(vec.x, vec.y, vec.z);
	}

	void DrawImage(const char* _imageName, unsigned int _imageID, float _size)
	{
		ImVec2 uv_min = ImVec2(0.0f, 0.0f);
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);
		ImGui::ImageWithBg(_imageID, ImVec2(_size, _size), uv_min, uv_max, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text(_imageName);
	}
}