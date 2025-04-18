#include "Resource/Skybox.hpp"
#include "Resource/ResourceManager.hpp"
#include <stb_image.h>
#include <string>
#include <filesystem>
#include <iostream>

namespace Resource
{
	Skybox::Skybox(std::string _name)
	{
		name = _name;
	}

	Skybox::~Skybox()
	{
		Delete();
	}

	void Skybox::GetFileContent(std::string _path)
	{

		// FindSkybox extention
		std::string findPathExtention = _path + m_faces[0];
		if (std::filesystem::exists(findPathExtention + ".png"))
		{
			textureExtention = TEXTURE_EXTENSION::PNG;
		}
		else if (std::filesystem::exists(findPathExtention + ".jpg"))
		{
			textureExtention = TEXTURE_EXTENSION::JPG;
		}
		else
		{
			std::cout << "The file: " << _path << " not found!" << std::endl;
			return;
		}

		std::vector<std::string> _paths(6);
		for (int i = 0; i < 6; ++i)
			_paths[i] = std::string{ _path }.append(m_faces[i]).append(TEXTURE_EXTENSION_TO_STR(textureExtention));

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

	void Skybox::SetModelName(std::string _modelName)
	{
		m_meshName = _modelName;
	}

	void Skybox::SetShaderName(std::string _shaderName)
	{
		m_shaderProgramName = _shaderName;
	}

	void Skybox::Draw()
	{
		if (!m_mesh)
			m_mesh = ResourceManager::GetInstance().GetResource<Resource::Mesh>(m_meshName);
		else if (!m_shaderProgram)
			m_shaderProgram = ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_shaderProgramName);

		if (!m_mesh || !m_shaderProgram)
			return;

		m_rdrInter->DepthFunc(RHI::IFLAGS::DEPTH_LEQUAL);
		m_shaderProgram->Bind();
		m_cubeMap->Bind();
		m_mesh->Draw();
		m_cubeMap->Unbind();
		m_shaderProgram->Unbind();
		m_rdrInter->DepthFunc(RHI::IFLAGS::DEPTH_LESS);
	}

	void Skybox::Delete()
	{
		m_data.clear();
		if (m_cubeMap)
		{
			m_cubeMap->Delete();
			m_rdrInter->DestroyCubeMap(m_cubeMap);
		}
	}
}