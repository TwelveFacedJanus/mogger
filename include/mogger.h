#ifndef MOGGER_H
#define MOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

typedef struct MoggerCore {
	char* path_to_log;
	FILE* file;
	
	void (*log)(struct MoggerCore*, const char*);
	void (*change_logfile)(struct MoggerCore*, const char*);
	void (*print)(struct MoggerCore*, const char *format, ...);

} MoggerCore;



void log(struct MoggerCore* mc, const char* message) {
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

void print(struct MoggerCore* mc, const char *format, ...)
{

    va_list args;
    va_start(args, format); // Initialize args to point after 'format'

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 's': { // String
                    char *str = va_arg(args, char *);
                    fputs(str, stdout);
                    break;
                }
                case 'd': { // Integer
                    int num = va_arg(args, int);
                    fprintf(stdout, "%d", num);
                    break;
                }
                case 'f': { // Float
                    double num = va_arg(args, double);
                    fprintf(stdout, "%f", num);
                    break;
                }
                case '%': { // Literal '%'
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(*format); // Print unknown format specifier as-is
                    break;
                }
            }
        } else {
            putchar(*format); // Print normal characters
        }
        format++; // Move to next character
    }

    va_end(args); // Clean up
}

void change_logfile(struct MoggerCore* mc, const char* logs_path)
{
	if (mc->file) {
		fclose(mc->file);
	}
	mc->file = fopen(logs_path, "a+");

	if (mc->file == NULL) {
		free(mc->file);
		free(mc);
	}
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
	mc->print = print;
	mc->change_logfile = change_logfile;
	return mc;
}

void destroy_mogger(struct MoggerCore* mc)
{
	fclose(mc->file);
	free(mc);
}



#endif //MOGGER_H
