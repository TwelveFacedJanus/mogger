#ifndef MOGGER_H
#define MOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct MoggerCore {
	char* path_to_log;
	FILE* file;
	
	void (*log)(struct MoggerCore*, const char*);
} MoggerCore;

void log(struct MoggerCore* mc, const char* message)
{
	time_t current_time;
	struct tm *time_info;
	char buffer[80];

	time(&current_time);
	time_info = localtime(&current_time);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S ]=", time_info);
	fprintf(mc->file, buffer);
	fprintf(mc->file, message);
	fprintf(mc->file, "\n");
}


struct MoggerCore* init_mogger(const char* logs_path)
{
	MoggerCore *mc = (MoggerCore*)malloc(sizeof(MoggerCore));
	if (mc == NULL)
	{
		fprintf(stderr, "Failed to initialize MoggerCore.");
		return NULL;
	}
	mc->file = fopen(logs_path, "a+");

	if (mc->file == NULL) {
		free(mc->file);
		free(mc);
	}

	mc->log = log;
	return mc;
}

void destroy_mogger(struct MoggerCore* mc)
{
	fclose(mc->file);
	free(mc);
}



#endif //MOGGER_H
