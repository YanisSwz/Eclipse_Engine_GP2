#include "Prefab.hpp"
#include <fstream>

namespace Resource
{
	Prefab::Prefab(std::string _name)
	{
		name = _name;
	}

	Prefab::~Prefab()
	{
		m_filePath.clear();
	}

	void Prefab::GetFileContent(std::string _path)
	{
		m_filePath = _path;
		std::ifstream fileStream(_path);
		fileStream.close();
		bIsLoaded = true;
	}

	void Prefab::Delete()
	{
	}
}