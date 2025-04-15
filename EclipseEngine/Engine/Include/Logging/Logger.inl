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

	void Logger::LogToConsole(PRIORITY _priority, const char* _message, va_list _list)
	{
		printf(ColorToStr(PriorityToColor(_priority)));
		printf(GetTime().c_str());
		printf(" ");
		printf(PriorityToStr(_priority));
		printf(" ");
		vprintf(_message, _list);
		printf("\n");
	}

	void Logger::LogToFile(PRIORITY _priority, const char* _message, va_list _list)
	{
		FILE* file;
		fopen_s(&file, GetFilePath().c_str(), "w");

		if (m_isStandardConsoleEnabled)
			fprintf(file, ColorToStr(PriorityToColor(_priority)));

		fprintf(file, GetTime().c_str());
		fprintf(file, " ");
		fprintf(file, PriorityToStr(_priority));
		fprintf(file, " ");
		vfprintf(file, _message, _list);
		fprintf(file, "\n");

		std::fclose(file);
	}
}