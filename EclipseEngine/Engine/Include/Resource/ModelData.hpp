#pragma once
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Mat4.hpp"

namespace Resource
{
	struct ModelData
	{
		Mesh* mesh = nullptr;
		Texture* texture = nullptr;
		ShaderProgram* shaderProgram = nullptr;
		Math::Mat4 TRS;
		int ID;
	};
}