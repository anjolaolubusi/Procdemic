#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string>


class Logger
{
	public:
		Logger(const char* filename);
		void Log(const char* log, bool error = false);
		virtual ~Logger();
		FILE* fptr;
		time_t now;
		tm* curr_date;
		std::string str_currdate;
};
#endif //LOGGER_H
