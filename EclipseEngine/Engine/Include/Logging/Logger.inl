#include "Logger.hpp"
#include <cstdio>

namespace Logging
{
	inline void Logger::SetPriority(Logger::Priority _priority) { m_piority = _priority; }

	template<typename ... Args>
	void Logger::Log(Logger::Priority _priority, const char* _message, Args&& ... args)
	{
		if (m_priority <= _priority)
		{
			std::time_t currTime = std::time(0);
			std::tm* timestamp = std::localtime(&currTime);
		}
	}
}