#include "Logger.hpp"
#include <cstdio>
#include <ctime>
#include <string>

namespace Logging
{
	inline void Logger::SetPriority(PRIORITY _priority) { m_priority = _priority; }
	inline void Logger::EnableStandardConsoleOutput(bool _isStandardConsoleEnabled) { m_isStandardConsoleEnabled = _isStandardConsoleEnabled; }

	void Logger::Log(PRIORITY _priority, const char* _message, ...)
	{
		if (m_priority <= _priority)
		{
			va_list list;
			va_start(list, _message);

			if (m_isStandardConsoleEnabled)
				LogToConsole(_priority, _message, list);

			if (m_fileName != "")
				LogToFile(_priority, _message, list);

			va_end(list);
		}
	}
}