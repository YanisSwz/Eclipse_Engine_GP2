#pragma once
#include <stdio.h>
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
        ECLIPSE_ENGINE Logger(const char* _fileName, PRIORITY _priority = PRIORITY::DEBUG);
        ECLIPSE_ENGINE ~Logger();

        ECLIPSE_ENGINE void SetPriority(PRIORITY _priority);

        void Log(PRIORITY _priority, const char* _message, ...);

    private:
        static const char* m_folderName;
        static bool m_bIsFolderCreated;

        PRIORITY m_priority;
        FILE* m_file = nullptr;        

        void Init(const char* _fileName, PRIORITY _priority);
        void FreeFile();

        COLOR PriorityToColor(PRIORITY _priority);
        const char* PriorityToStr(PRIORITY _priority);
        const char* ColorToStr(COLOR _color);
    };
}