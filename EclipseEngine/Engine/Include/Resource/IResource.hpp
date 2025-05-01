#pragma once
#include "ProjectExports.hpp"
#include <string>

namespace Resource
{
	class IResource
	{
	public:
		IResource() = default;
		virtual ~IResource() = default;
		
		std::string name = "";

		ECLIPSE_ENGINE virtual bool IsLoaded() { return bIsLoaded; }

		virtual void GetFileContent(std::string _path) = 0;
		virtual void Delete() = 0;

	protected:
		bool bIsLoaded = false;
	};
}