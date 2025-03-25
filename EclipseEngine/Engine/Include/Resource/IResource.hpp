#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "ProjectExports.hpp"

namespace Resource
{
	class IResource
	{
	public:
		IResource() = default;
		virtual ~IResource() = default;

		ECLIPSE_ENGINE bool IsLoaded() { return bIsLoaded; }

		virtual void Generate(RHI::IRenderInterface* _rdrInterface) = 0;
		// virtual void Delete() = 0; // TODO Add override

	protected:
		bool bIsLoaded = false;
	};
}