#include "Logger.hpp"
#include <ctime>

#define NOGDI
#include <windows.h>

namespace Logging
{
    Logger* Logger::m_instance = nullptr;
    std::string Logger::m_folderName = "Logs";
    std::string Logger::m_fileName = "";

    Logger* Logger::Get()
    {
        if (!m_instance)
        {
            std::string fileName = std::string("Log_") + GetDateTime() + ".txt";
            m_instance = new Logger(fileName);
        }
        return m_instance;
    }

    void Logger::Destroy()
    {
        if (m_instance)
            delete m_instance;
    }

    std::string Logger::GetFilePath()
    {
        std::string filePath = m_folderName + "/" + m_fileName;
        return filePath;
    }

    Logger::Logger()
    {
    }

    Logger::Logger(std::string _fileName, PRIORITY _priority, bool _isStandardConsoleEnabled)
    {
        SetPriority(_priority);
        EnableStandardConsoleOutput(_isStandardConsoleEnabled);

        m_fileName = _fileName;

        CreateDirectory(m_folderName.c_str(), NULL);

        HANDLE handle = CreateFile(GetFilePath().c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (handle != 0)
            CloseHandle(handle);
    }

    Logger::~Logger()
    {
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
        fopen_s(&file, GetFilePath().c_str(), "a");

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

    COLOR Logger::PriorityToColor(PRIORITY _priority)
    {
        switch (_priority)
        {
        case PRIORITY::DEBUG:
            return COLOR::WHITE;
        case PRIORITY::INFO:
            return COLOR::GREEN;
        case PRIORITY::WARNING:
            return COLOR::YELLOW;
        case PRIORITY::ERROR:
            return COLOR::RED;
        default:
            return COLOR::WHITE;
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
        default:
            return "[]";
        }
	}

	const char* Logger::ColorToStr(COLOR _color)
	{
        switch (_color)
        {
        case COLOR::WHITE:
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
        default:
            return "\033[0m";
        }
	}

    std::string Logger::GetDateTime()
    {
        std::time_t currTime = std::time(0);
        std::tm timestamp;
        localtime_s(&timestamp, &currTime);
        char timeBuffer[128];
        strftime(timeBuffer, 80, "%d-%m-%y_%H-%M", &timestamp);
        return std::string(timeBuffer);
    }

    std::string Logger::GetTime()
    {
        std::time_t currTime = std::time(0);
        std::tm timestamp;
        localtime_s(&timestamp, &currTime);
        char timeBuffer[128];
        strftime(timeBuffer, 80, "[%X]", &timestamp);
        return std::string(timeBuffer);
    }
}