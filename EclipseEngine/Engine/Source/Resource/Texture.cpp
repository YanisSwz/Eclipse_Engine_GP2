#include "Resource/Texture.hpp"
#include "filesystem"
#include "stb_image.h"
#include <iostream>

namespace Resource
{
	Texture::Texture(std::string _name)
	{
		name = _name;
	}

	Texture::~Texture()
	{
		Delete();
	}

	void Texture::GetFileContent(std::string _path)
	{
		// Verify if Texture file path exists
		if (!std::filesystem::exists(_path))
		{
			std::cout << "The file: " << _path << " not found!" << std::endl;
			return;
		}

		// Get Texture file content
		stbi_set_flip_vertically_on_load(true);
		m_imgData = stbi_load(_path.c_str(), &m_width, &m_height, &m_numColCh, 0);
	}

	void Texture::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_texture = _rdrInterface->InstantiateTexture2D();;
		m_texture->Generate(m_imgData, m_width, m_height, m_numColCh);
		stbi_image_free(m_imgData);
		m_imgData = nullptr;

		bIsLoaded = true;
	}

	unsigned int Texture::GetID() const
	{
		return m_texture->GetID();
	}

	int Texture::GetWidth() const
	{
		return m_width;
	}

	int Texture::GetHeight() const
	{
		return m_height;
	}

	void Texture::Bind()
	{
		m_texture->Bind();
	}

	void Texture::Unbind()
	{
		m_texture->Unbind();
	}

	void Texture::Delete()
	{
		if (m_imgData)
		{
			stbi_image_free(m_imgData);
			m_imgData = nullptr;
		}
		if (m_texture)
		{
			m_texture->Delete();
			m_rdrInter->DestroyTexture2D(m_texture);
		}
	}
}