#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>

struct Logger
{
    FILE *output_file;

    void LogTimer(char *name, double delta_time) const
    {
        fprintf(output_file, "%s: %f\n", name, delta_time);
    }

    explicit Logger(const char *log_path)
    {
        output_file = fopen(log_path, "w");
    }

    ~Logger()
    {
        fclose(output_file);
    }
};

#endif //LOGGER_H
