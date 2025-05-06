#include "Resource/GeoShader.hpp"
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

namespace Resource
{
	GeoShader::GeoShader(std::string _name)
	{
		name = _name;
	}

	GeoShader::~GeoShader()
	{
		Delete();
	}

	void GeoShader::GetFileContent(std::string _path)
	{
		// Verify if Geometry Shader file path exists
		if (!std::filesystem::exists(_path))
		{
			std::cout << "The file: " << _path << " not found!" << std::endl;
			return;
		}

		// Get Vertex file content
		std::ifstream geoFile(_path);
		std::string fileContent((std::istreambuf_iterator<char>(geoFile)), std::istreambuf_iterator<char>());
		m_geometryFileContent = fileContent;

		bIsLoaded = true;
	}

	void GeoShader::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_geometryShader = _rdrInterface->InstantiateGeometryShader();
		m_geometryShader->Generate(m_geometryFileContent);
	}

	unsigned int GeoShader::GetID() const
	{
		return m_geometryShader->GetID();
	}

	void GeoShader::Delete()
	{
		m_geometryFileContent.clear();
		if (m_geometryShader)
		{
			m_geometryShader->Delete();
			m_rdrInter->DestroyGeometryShader(m_geometryShader);
		}
	}
}