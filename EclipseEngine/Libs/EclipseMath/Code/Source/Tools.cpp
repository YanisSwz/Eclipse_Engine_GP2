#include "Tools.hpp"

namespace Math::Tools
{
	std::vector<std::string> Split(std::string _string, const char _delimiter)
	{
		std::vector<std::string> stringList;
		std::string crtString = "";
		for (const char ch : _string)
		{
			if (ch == _delimiter && !crtString.empty())
			{
				stringList.push_back(crtString);
				crtString.clear();
				continue;
			}
				
			crtString += ch;
		}
		
		if (!crtString.empty())
			stringList.push_back(crtString);
		
		return stringList;
	}
}