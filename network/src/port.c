/*
**  @(#)port.c
**
**  libnetwork - portable functions
**  -------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  String concatenate.
*/
int strcat_p(string_c_t destination, size_t destination_size, const string_c_t source, size_t count)
{
#ifdef _SCL
    return (strncat_s(destination, destination_size, source, count));
#else
    return ((strncat(destination, source, count) != NULL) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
}

/*
**  String copy.
*/
int strcpy_p(string_c_t destination, size_t destination_size, const string_c_t source, size_t count)
{
#ifdef _SCL
    return (strncpy_s(destination, destination_size, source, count));
#else
    return ((strncpy(destination, source, count) != NULL) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
}

/*
**  String format.
*/
int strfmt_p(string_c_t destination, size_t destination_size, const string_c_t format, ...)
{
    va_list varg;
    int rc;

    va_start(varg,format);
#ifdef _SCL
    rc = vsprintf_s(destination, destination_size, format, varg);
#else
    rc = vsprintf(destination, format, varg);
#endif
    va_end(varg);
    return (rc);
}

/*
**  String tokenizer.
*/
int strtok_p(string_c_t *token, string_c_t string, const string_c_t delimiters, string_c_t *context)
{
#ifdef _SCL
    return ((*token = strtok_s(string, delimiters, &*context)) ? EXIT_SUCCESS : EXIT_FAILURE);
#else
    return ((*token = strtok(string, delimiters)) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
}

/*
**  Get system time.
*/
int time_p(time_t *timer)
{
    time(timer);
    return (EXIT_SUCCESS);
}

/*
**  Convert time as local time.
*/
int localtime_p(time_t *timer, struct tm *time)
{
#ifdef _SCL
    return (localtime_s(time, timer));
#else
    struct tm *local_time = localtime(timer);

    time->tm_sec   = local_time->tm_sec;
    time->tm_min   = local_time->tm_min;
    time->tm_hour  = local_time->tm_hour;
    time->tm_mday  = local_time->tm_mday;
    time->tm_mon   = local_time->tm_mon;
    time->tm_year  = local_time->tm_year;
    time->tm_wday  = local_time->tm_wday;
    time->tm_yday  = local_time->tm_yday;
    time->tm_isdst = local_time->tm_isdst;
    return (EXIT_SUCCESS);
#endif
}

/*
**  Open file stream.
*/
int fopen_p(FILE **file_pointer, const string_c_t file_name, const string_c_t mode)
{
#ifdef _SCL
    return (fopen_s(file_pointer, file_name, mode));
#else
    *file_pointer = fopen(file_name, mode);
    return (*file_pointer != NULL ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
}

/*
**  Close file stream.
*/
int fclose_p(FILE *file_pointer)
{
    return (fclose(file_pointer));
}

/*
**  Get temporary file.
*/
int tmpfile_p(FILE **fp)
{
#ifdef _SCL
     return (tmpfile_s(fp));
#else
     *fp = tmpfile();
     return (*fp != NULL ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
}

