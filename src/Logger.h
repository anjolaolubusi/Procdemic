#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

class Logger
{
	public:
		Logger();
		void Log(const char* log, bool error = false);
		~Logger();
		FILE* fptr;
		time_t now;
		tm* curr_date;
		std::string str_currdate;
};
#endif //LOGGER_H
