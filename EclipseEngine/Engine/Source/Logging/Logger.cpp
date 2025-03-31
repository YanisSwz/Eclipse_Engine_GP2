#include "Logger.hpp"
#include <string>

#define NOGDI
#include <windows.h>

namespace Logging
{
    const char* Logger::m_folderName = "Logs";
    bool Logger::m_bIsFolderCreated = false;

    Logger::Logger(const char* _fileName, PRIORITY _priority)
    {
        Init(_fileName, _priority);
    }

    Logger::~Logger()
    {
        FreeFile();
    }

    void Logger::Init(const char* _fileName, PRIORITY _priority)
    {
        SetPriority(_priority);

        if (!m_bIsFolderCreated)
        {
            CreateDirectory(m_folderName, NULL);
            Logger::m_bIsFolderCreated = true;
        }

        std::string filePathStr = std::string(m_folderName) + "/" + _fileName;
        const char* filePath = filePathStr.c_str();
        HANDLE handle = CreateFile(filePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (handle != 0)
            CloseHandle(handle);

        fopen_s(&m_file, filePath, "a");
    }

    void Logger::FreeFile()
    {
        if (m_file)
        {
            std::fclose(m_file);
            m_file = nullptr;
        }
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
}