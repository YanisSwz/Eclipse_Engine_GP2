#include "Resource/VertShader.hpp"
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

namespace Resource
{
	VertShader::VertShader()
	{
	}

	VertShader::~VertShader()
	{
		Delete();
	}

	void VertShader::GetFileContent(std::string _path)
	{
		// Verify if Vertex file path exists
		if (!std::filesystem::exists(_path))
		{
			std::cout << "The file: " << _path << " not found!" << std::endl;
			return;
		}

		// Get Vertex file content
		std::ifstream vertFile(_path);
		std::string fileContent((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());
		m_vertexFileContent = fileContent;

		bIsLoaded = true;
	}

	void VertShader::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_vertexShader = _rdrInterface->InstantiateVertexShader();
		m_vertexShader->Generate(m_vertexFileContent);
	}

	unsigned int VertShader::GetID() const
	{
		return m_vertexShader->GetID();
	}

	void VertShader::Delete()
	{
		m_vertexFileContent.clear();
		m_vertexShader->Delete();
		m_rdrInter->DestroyVertexShader(m_vertexShader);
	}
}