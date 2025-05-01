#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "Resource/IResource.hpp"
#include "ProjectExports.hpp"
#include <string>

namespace Resource
{
	class IGraphicsResource : public IResource
	{
	public:
		IGraphicsResource() = default;
		virtual ~IGraphicsResource() = default;

		virtual void Generate(RHI::IRenderInterface* _rdrInterface) = 0;
	};
}
