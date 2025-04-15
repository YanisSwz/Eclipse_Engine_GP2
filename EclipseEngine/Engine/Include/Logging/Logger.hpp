#pragma once
#include <string>
#include "ProjectExports.hpp"

namespace Logging
{
    enum class PRIORITY
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    enum class COLOR
    {
        WHITE,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        PURPLE,
        CYAN
    };

    class Logger
    {
    public:
        ECLIPSE_ENGINE static Logger* Get();
        ECLIPSE_ENGINE static std::string GetFilePath();

        ECLIPSE_ENGINE void SetPriority(PRIORITY _priority);

        ECLIPSE_ENGINE void Log(PRIORITY _priority, const char* _message, ...);

    private:
        static Logger* m_instance;
        static std::string m_folderName;
        static std::string m_fileName;
        PRIORITY m_priority;

        Logger(std::string _fileName, PRIORITY _priority = PRIORITY::DEBUG);
        ~Logger();

        COLOR PriorityToColor(PRIORITY _priority);
        const char* PriorityToStr(PRIORITY _priority);
        const char* ColorToStr(COLOR _color);

        static std::string GetDateTime();
        std::string GetTime();
    };
}