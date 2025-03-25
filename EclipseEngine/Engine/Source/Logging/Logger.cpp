#include "Logger.hpp"
#include <ctime>

namespace Logging
{
    Logger::Logger(PRIORITY _priority)
    {
        Init(_priority);
    }

    Logger::~Logger()
    {
        FreeFile();
    }

    void Logger::Init(PRIORITY _priority)
    {
        SetPriority(_priority);
        m_file = std::fopen(m_filePath, "a");
    }

    void Logger::FreeFile()
    {
        if (m_file)
        {
            std::fclose(m_file);
            m_file = nullptr;
        }
    }

    Logger::COLOR Logger::PriorityToColor(PRIORITY _priority)
    {
        switch (_priority)
        {
        case PRIORITY::DEBUG:
            return COLOR::RESET;
        case PRIORITY::INFO:
            return COLOR::GREEN;
        case PRIORITY::WARNING:
            return COLOR::YELLOW;
        case PRIORITY::ERROR:
            return COLOR::RED;
        }
    }

	const char* Logger::PriorityToStr(PRIORITY _priority)
	{
        switch (_priority)
        {
        case PRIORITY::DEBUG:
            return "[DEBUG]";
        case PRIORITY::INFO:
            return "[INFO]";
        case PRIORITY::WARNING:
            return "[WARNING]";
        case PRIORITY::ERROR:
            return "[ERROR]";
        }
	}

	const char* Logger::ColorToStr(COLOR _color)
	{
        switch (_color)
        {
        case COLOR::RESET:
            return "\033[0m";
        case COLOR::RED:
            return "\033[31m";
        case COLOR::GREEN:
            return "\033[32m";
        case COLOR::YELLOW:
            return "\033[33m";
        case COLOR::BLUE:
            return "\033[36m";
        case COLOR::PURPLE:
            return "\033[1;35m";
        case COLOR::CYAN:
            return "\033[1;36m";
        }
	}
}