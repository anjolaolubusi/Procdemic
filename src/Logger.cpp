#include "Logger.h"


Logger::Logger(const char* filename) {
	this->now = time(0);
	this->curr_date = localtime(&now);
	std::string fileDir = "logs/" + std::to_string(1900 + curr_date->tm_year) + std::to_string(1 + curr_date->tm_mon) + std::to_string(curr_date->tm_mday) + filename;
	fptr = fopen(fileDir.c_str(), "a");
	Log("Initalizing Logger");
}

void Logger::Log(const char* log, bool error) {
	this->now = time(0);
	this->curr_date = localtime(&now);
	this->str_currdate = std::to_string(1900 + curr_date->tm_year);
	str_currdate += "-" + std::to_string(1 + curr_date->tm_mon) + "-" + std::to_string(curr_date->tm_mday) + " " + std::to_string(curr_date->tm_hour) + ":" + std::to_string(curr_date->tm_min) + ":" + std::to_string(curr_date->tm_sec);
	fprintf(fptr, "[");
	fprintf(fptr, str_currdate.c_str());
	fprintf(fptr, "]: ");

	fprintf(stderr, log);
	fprintf(stderr, "\n");

	if (error) {
		fprintf(fptr, "Error - ");
	}
		fprintf(fptr, log);
		fprintf(fptr, "\n");
}

Logger::~Logger() {
	fclose(fptr);
}

