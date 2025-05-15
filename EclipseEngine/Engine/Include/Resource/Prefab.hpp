#pragma once
#include "IResource.hpp"

namespace Resource
{
	class Prefab : public IResource
	{
	public:
		ECLIPSE_ENGINE Prefab(std::string _name);
		ECLIPSE_ENGINE ~Prefab() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Delete() override;

		ECLIPSE_ENGINE inline std::string GetFilePath() const { return m_filePath; }

	private:
		std::string m_filePath;
	};
}