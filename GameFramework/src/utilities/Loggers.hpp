#ifndef LOGGERS_HPP_
#define LOGGERS_HPP_


#include <spdlog/spdlog.h>




class Loggers
{
public:

	inline static std::shared_ptr<spdlog::logger> getLog() { return spdlog::get("fileLogger"); }
};


#endif



