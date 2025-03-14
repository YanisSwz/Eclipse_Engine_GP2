#pragma once
#include <vector>
#include <string>

namespace RHI
{
	class ICubeMap
	{
	public:
		ICubeMap() = default;
		 virtual ~ICubeMap() = default;

		virtual void Init(std::vector<std::string> _paths) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

	private:

	};
}