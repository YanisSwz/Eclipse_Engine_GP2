#include "Logger.hpp"
#include <stdio.h>
#include <cstdio>
#include <stdarg.h>
#include <ctime>
#include <string>

namespace Logging
{
	inline void Logger::SetPriority(PRIORITY _priority) { m_priority = _priority; }

	void Logger::Log(PRIORITY _priority, const char* _message, ...)
	{
		if (m_priority <= _priority && m_fileName != "")
		{
			FILE* file;
			fopen_s(&file, GetFilePath().c_str(), "w");

			fprintf(file, ColorToStr(PriorityToColor(_priority)));
			fprintf(file, GetTime().c_str());
			fprintf(file, PriorityToStr(_priority));
			va_list arglist;
			va_start(arglist, _message);
			vfprintf(file, _message, arglist);
			va_end(arglist);
			fprintf(file, "\n");

			std::fclose(file);
		}
	}
}