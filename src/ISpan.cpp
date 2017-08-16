#include <iostream>
#include "ISpan.h"
#include "Logger.h"
using namespace OpenTracing;

extern Logger* file_logger;

ISpan::~ISpan()
{
    if (file_logger != nullptr)
    {
        std::ostringstream ss;
        ss << this;        file_logger->PrintLine("    ~ISpan addr: " + ss.str());
    }
#ifdef TRACER_DEBUG
    Php::out << "    ~ISpan addr: " << this << std::endl;
#endif
}
