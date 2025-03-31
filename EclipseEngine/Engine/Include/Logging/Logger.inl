#include "Logger.hpp"
#include <cstdio>
#include <stdarg.h>
#include <ctime>

namespace Logging
{
	inline void Logger::SetPriority(PRIORITY _priority) { m_priority = _priority; }

	void Logger::Log(PRIORITY _priority, const char* _message, ...)
	{
		if (m_priority <= _priority && m_file)
		{
			std::time_t currTime = std::time(0);
			std::tm timestamp;
			localtime_s(&timestamp, &currTime);
			char timeBuffer[128];
			strftime(timeBuffer, 80, "[%x - %X]", &timestamp);

			fprintf(m_file, ColorToStr(PriorityToColor(_priority)));
			fprintf(m_file, timeBuffer);
			fprintf(m_file, PriorityToStr(_priority));
			va_list arglist;
			va_start(arglist, _message);
			vfprintf(m_file, _message, arglist);
			va_end(arglist);
			fprintf(m_file, "\n");
		}
	}
}