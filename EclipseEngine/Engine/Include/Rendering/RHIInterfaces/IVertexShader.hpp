#pragma once
#include <string>

namespace RHI
{
	class IVertexShader
	{
	public:
		IVertexShader() = default;
		virtual ~IVertexShader() = default;

		virtual void Init(std::string _path) = 0;
		virtual int GetID() const = 0;
		virtual void Delete() = 0;

	private:

	};
}