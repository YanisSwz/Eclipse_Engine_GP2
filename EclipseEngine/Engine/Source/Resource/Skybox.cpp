#include "Resource/Skybox.hpp"
#include <stb_image.h>
#include <string>
#include <iostream>

namespace Resource
{
	Skybox::Skybox()
	{
	}

	Skybox::~Skybox()
	{
		Delete();
	}

	void Skybox::GetFileContent(const char* _skyboxFolderPath, TEXTURE_EXTENSION _textureExtention)
	{
		textureExtention = _textureExtention;
		std::vector<std::string> _paths(6);
		for (int i = 0; i < 6; ++i)
			_paths[i] = std::string{ _skyboxFolderPath }.append(m_faces[i]).append(TEXTURE_EXTENTION_TO_STR(_textureExtention));

		int nrChannels;
		stbi_set_flip_vertically_on_load(false);

		for (int i = 0; i < 6; ++i)
		{
			m_data.push_back(stbi_load(_paths[i].c_str(), &m_width, &m_height, &nrChannels, 0));
			if (!m_data[i])
			{
				std::cout << "Error during the load of the CubeMap Texture !" << std::endl;
				stbi_image_free(m_data[i]);
				return;
			}
		}
	}

	void Skybox::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_cubeMap = _rdrInterface->InstantiateCubeMap();
		m_cubeMap->Generate(m_data, m_width, m_height, textureExtention);

		for (int i = 0; i < 6; ++i)
			stbi_image_free(m_data[i]);

		bIsLoaded = true;
	}

	void Skybox::SetModel(Resource::Model* _model)
	{
		m_model = _model;
	}

	void Skybox::SetShader(Resource::ShaderProgram* _shader)
	{
		m_shaderProgram = _shader;
	}

	void Skybox::Draw() const
	{
		m_rdrInter->DepthFunc(RHI::IFLAGS::DEPTH_LEQUAL);
		m_shaderProgram->Bind();
		m_cubeMap->Bind();
		m_model->Draw();
		m_cubeMap->Unbind();
		m_shaderProgram->Unbind();
		m_rdrInter->DepthFunc(RHI::IFLAGS::DEPTH_LESS);
	}

	void Skybox::Delete()
	{
		m_data.clear();
		m_cubeMap->Delete();
		m_rdrInter->DestroyCubeMap(m_cubeMap);
	}
}