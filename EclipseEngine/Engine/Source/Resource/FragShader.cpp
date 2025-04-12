#include "Resource/FragShader.hpp"
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

namespace Resource
{
	FragShader::FragShader(std::string _name)
	{
		name = _name;
	}

	FragShader::~FragShader()
	{
		Delete();
	}

	void FragShader::GetFileContent(std::string _path)
	{
		// Verify if Fragment file path exists
		if (!std::filesystem::exists(_path))
			std::cout << "The file: " << _path << " not found!" << std::endl;

		// Get Fragment file content
		std::ifstream fragFile(_path);
		std::string fileContent((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());
		m_fragmentFileContent = fileContent;

	}

	void FragShader::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_fragmentShader = _rdrInterface->InstantiateFragmentShader();
		m_fragmentShader->Generate(m_fragmentFileContent);

		bIsLoaded = true;
	}

	unsigned int FragShader::GetID() const
	{
		return m_fragmentShader->GetID();
	}

	void FragShader::Delete()
	{
		m_fragmentFileContent.clear();
		if (m_fragmentShader)
		{
			m_fragmentShader->Delete();
			m_rdrInter->DestroyFragmentShader(m_fragmentShader);
		}
	}
}