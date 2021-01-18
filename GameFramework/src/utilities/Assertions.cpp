#include <iostream>

#include "utilities/Assertions.h"
#include "utilities/Loggers.hpp"




void logAssertFail(const char* function, const char* file, int line)
{
	Loggers::assertLog()->critical("Failed Expression: {0}, File: {1}, Line: {2}", function, file, line);
}







