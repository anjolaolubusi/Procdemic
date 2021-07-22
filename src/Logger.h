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

struct Logger
{
	public:
		Logger() {
			this->now = time(0);
			this->curr_date = localtime(&now);
			char fileDir[100];
			sprintf(fileDir, "logs/%d%d%dlogs.txt", 1900 + curr_date->tm_year, 1 + curr_date->tm_mon, curr_date->tm_mday);
			fptr = fopen(fileDir, "a");
			if (fptr == NULL) {
#ifdef _WIN32
				if (_mkdir("logs") == 0) {
					fptr = fopen(fileDir, "a");
					this->Log("Created Log Folder");
				}
#else
				mkdir("logs", 0700);
				fptr = fopen(fileDir, "a");
				this->Log("Created Log Folder");
#endif
			}
			this->Log("Initalizing Logger");
		}

		void Log(const char* log, bool error = false) {
			this->now = time(0);
			this->curr_date = localtime(&now);
			fprintf(fptr, "[%d-%d-%d %d:%d:%d] ", 1900 + curr_date->tm_year, 1 + curr_date->tm_mon, curr_date->tm_mday, curr_date->tm_hour, curr_date->tm_min, curr_date->tm_sec);
			fprintf(stderr, "%s\n", log);
			if (error) {
				fprintf(fptr, "Error - ");
			}
			fprintf(fptr, "%s\n", log);
		}

		~Logger() {
			this->now = time(0);
			this->curr_date = localtime(&now);
			fprintf(fptr, "[%d-%d-%d %d:%d:%d] ", 1900 + curr_date->tm_year, 1 + curr_date->tm_mon, curr_date->tm_mday, curr_date->tm_hour, curr_date->tm_min, curr_date->tm_sec);
			fprintf(fptr, "Closing Logger\n");
			fprintf(fptr, "\n");
			fprintf(stdout, "Closing Logger");
			fclose(fptr);
		}

		FILE* fptr;
		time_t now;
		tm* curr_date;
		std::string str_currdate;
};
#endif //LOGGER_H
