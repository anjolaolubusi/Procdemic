#include "Logger.h"


Logger::Logger(const char* filename) {
	fptr = fopen("log.txt", "a");
	Log("Initalizing Logger");
}

void Logger::Log(const char* log, bool error) {
	if (error) {
		fprintf(stderr, log);
	}
	else {
		fprintf(stdout, log);
	}
	
	time_t now = time(0);
	tm* test = localtime(&now);
	std::string dates = std::to_string(1900 + test->tm_year);
	dates += "-" + std::to_string(1 + test->tm_mon) + "-" + std::to_string(test->tm_mday) + "-" + std::to_string(test->tm_hour) + ":" + std::to_string(test->tm_min) + ":" + std::to_string(test->tm_sec);
	fprintf(fptr, "[");
	fprintf(fptr, dates.c_str());
	fprintf(fptr, "]: ");
	fprintf(fptr, log);
	fprintf(fptr, "\n");
}

Logger::~Logger() {
	fclose(fptr);
}

