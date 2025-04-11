#pragma once
#include "Maths.hpp"

namespace GUI
{
	void DragVec3XYZ(const char* _label, Math::Vec3& _vec3, float _resetValue = 0.0f, float _columnWidth = 100.0f);
	void DragQuatXYZ(const char* _label, Math::Quat& _quat, float _resetValue = 0.0f, float _columnWidth = 100.f);
}