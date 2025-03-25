#pragma once
#include <string>
#include <iostream>
#include "ProjectExports.hpp"

namespace Logging
{
    class Logger
    {
    public:
        enum class PRIORITY
        {
            DEBUG = 0,
            INFO = 1,
            WARNING = 2,
            ERROR = 3
        };

        enum class COLOR
        {
            RESET,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            PURPLE,
            CYAN
        };

        

        ECLIPSE_ENGINE inline void SetPriority(PRIORITY _priority);

        template<typename ... Args>
        ECLIPSE_ENGINE void Log(PRIORITY _priority, const char* _message, Args&& ... args);

    private:
        PRIORITY m_priority;

        const char* m_filePath;
        FILE* m_file;

        Logger(PRIORITY _priority = PRIORITY::DEBUG);
        ~Logger();

        void Init(PRIORITY _priority);
        void FreeFile();

        COLOR PriorityToColor(PRIORITY _priority);
        const char* PriorityToStr(PRIORITY _priority);
        const char* ColorToStr(COLOR _color);
    };
}