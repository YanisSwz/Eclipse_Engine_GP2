#pragma once
#include <string>

namespace RHI
{
	class IGeometryShader
	{
	public:
		IGeometryShader() = default;
		virtual ~IGeometryShader() = default;

		virtual void Generate(std::string _path) = 0;
		virtual unsigned int GetID() const = 0;
		virtual void Delete() = 0;

	private:

	};
}