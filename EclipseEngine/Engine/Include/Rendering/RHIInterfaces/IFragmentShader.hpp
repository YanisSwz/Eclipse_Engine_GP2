#pragma once
#include <string>

namespace RHI
{
	class IFragmentShader
	{
	public:
		IFragmentShader() = default;
		virtual ~IFragmentShader() = default;

		virtual void Generate(std::string _data) = 0;
		virtual unsigned int GetID() const = 0;
		virtual void Delete() = 0;

	private:

	};
}