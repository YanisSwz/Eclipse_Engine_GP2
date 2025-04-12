#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "ProjectExports.hpp"
#include "string"

namespace Resource
{
	class IResource
	{
	public:
		IResource() = default;
		virtual ~IResource() = default;
		
		std::string name = "";

		ECLIPSE_ENGINE bool IsLoaded() { return bIsLoaded; }

		virtual void GetFileContent(std::string _path) = 0;
		virtual void Generate(RHI::IRenderInterface* _rdrInterface) = 0;
		virtual void Delete() = 0;

	protected:
		bool bIsLoaded = false;
	};
}