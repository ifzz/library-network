/*
**  @(#)netlogs.c
**
**  libnetwork - library logging functions
**  --------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Log file directory name, name and file open flag.
*/
static char NetLogFileDirectoryName[_MAX_FILENAME_SIZE + 1];
static char NetLogFileName[_MAX_FILENAME_SIZE + 1];
static bool_c_t NetLogFileOpened = FALSE;

/*
**  Log file stream file pointer (buffered I/O stream).
*/
static FILE *fp = NULL;

/*
**  Local function prototypes.
*/
static void CreateNetLogFileName(void);
static void PrintLocalTime(void);

/*
**  Set log file directory name.
*/
void NetLogFileDirectory(const string_c_t directory_name, size_t directory_name_size)
{
    if (directory_name_size > _MAX_FILENAME_SIZE) {
        directory_name_size = _MAX_FILENAME_SIZE;
    }

    if (directory_name && strlen(directory_name) > 0) {
        strcpy_p(NetLogFileDirectoryName, sizeof(NetLogFileDirectoryName), directory_name, directory_name_size);
    }
    else {
        strcpy_p(NetLogFileDirectoryName, sizeof(NetLogFileDirectoryName), (const string_c_t)_LOGFILE_NAME, sizeof(_LOGFILE_NAME));
    }
}

/*
**  Set log file name using given file name.
*/
void NetLogFileSetFileName(const string_c_t filename)
{
    time_t lt;
    struct tm t;

    /*
    **  Get current local system date and time.
    */
    setlocale(LC_ALL, "");
    time(&lt);
    localtime_p(&lt, &t);

    /*
    **  Use default directory name if no directory name was given.
    */
    if (strlen(NetLogFileDirectoryName) < 1) {
        strcpy_p(NetLogFileDirectoryName, sizeof(NetLogFileDirectoryName), (const string_c_t)_LOGFILE_NAME, sizeof(_LOGFILE_NAME));
    }

    /*
    **  Format log file name using directory, filename and current local system date.
    */
    strfmt_p(NetLogFileName, sizeof(NetLogFileName), (const string_c_t)"%s/%s.log.%02d%02d%02d", NetLogFileDirectoryName, filename, t.tm_mon + 1, t.tm_mday, t.tm_year % 100);
}

/*
**  Open log file.
*/
void NetLogFileOpen(void)
{
    int file_status;
    char mode[_FILE_MODE_SIZE];

    /*
    **  Create log file name if log file name does not exist.
    */
    if (strlen(NetLogFileName) < 1) {
        CreateNetLogFileName();
    }

    /*
    **  Set file mode to either append or read/write.
    */
    if (NetLogFileOpened == TRUE) {
        strcpy_p(mode, sizeof(mode), (const string_c_t)_F_AP_BIN, sizeof(_F_AP_BIN));
    }
    else {
        NetLogFileOpened = TRUE;
        if ((file_status = fopen_p(&fp, NetLogFileName, (const string_c_t)_F_RO_BIN)) != 0) {
            strcpy_p(mode, sizeof(mode), (const string_c_t)_F_RW_BIN, sizeof(_F_RW_BIN));
        }
        else {
            strcpy_p(mode, sizeof(mode), (const string_c_t)_F_AP_BIN, sizeof(_F_AP_BIN));
        }
    }

    /*
    **  Open log file using specified mode.
    */
    if ((file_status = fopen_p(&fp, NetLogFileName, (const string_c_t)mode)) != 0) {
        printf("error-> unable to open log file (errno %d)\n", errno);
        exit(EXIT_FAILURE);
    }
}

/*
**  Print log file output.
*/
void NetLogFilePrint(string_c_t format, ...)
{
    va_list vargs;

#ifdef _POSIX_ENVIRONMENT
    mode_t fmode = (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
#endif

    /*
    **  Open log file.
    */
    NetLogFileOpen();

    /*
    **  Print current local time in log file.
    */
    PrintLocalTime();

    /*
    **  Format variable arguments and print output to the log file.
    */
    va_start(vargs, format);
    vfprintf(fp, format, vargs);
    va_end(vargs);

    /*
    **  Close log file.
    */
    NetLogFileClose();

    /*
    **  Change permission codes on log file.
    */
#ifdef _POSIX_ENVIRONMENT
    if (chmod(NetLogFileName, fmode) == -1) {
        printf("error-> unable to change file permission codes (errno %d)\n", errno);
    }
#endif
}

/*
**  Flush log file buffer.
*/
void NetLogFileFlush(void)
{
    /*
    **  Flush current output to log file.
    */
    if (fp != (FILE *)NULL) {
        fflush(fp);
    }
}

/*
**  Close log file.
*/
void NetLogFileClose(void)
{
    /*
    **  Flush current output to log file.
    */
    NetLogFileFlush();

    /*
    **  Close log file.
    */
    if (fp != (FILE *)NULL) {
        fclose_p(fp);
    }
}

/*
**  Create log file name using environment variables and current system date.
*/
static void CreateNetLogFileName(void)
    {
    time_t lt;
    struct tm t;

    /*
    **  Get current local system date and time.
    */
    setlocale(LC_ALL, "");
    time(&lt);
    localtime_p(&lt, &t);

    /*
    **  Use default directory name if no directory name was given.
    */
    if (strlen(NetLogFileDirectoryName) < 1) {
        strcpy_p(NetLogFileDirectoryName, sizeof(NetLogFileDirectoryName), (const string_c_t)_LOGFILE_NAME, sizeof(_LOGFILE_NAME));
    }

    /*
    **  Format log file name using directory, and current local system date.
    */
    strfmt_p(NetLogFileName, sizeof(NetLogFileName), (const string_c_t)"%s.log.%02d%02d%02d", NetLogFileDirectoryName, t.tm_mon + 1, t.tm_mday, t.tm_year % 100);
}

/*
**  Print local time in log file.
*/
static void PrintLocalTime(void)
{
    time_t lt;
    struct tm t;

    /*
    **  Get current local system date and time.
    */
    setlocale(LC_ALL, "");
    time(&lt);
    localtime_p(&lt, &t);

    /*
    **  Print current local system time.
    */
    fprintf(fp, "%02d%02d%02d:%02d%02d%02d: ", t.tm_mon + 1, t.tm_mday, t.tm_year % 100, t.tm_hour, t.tm_min, t.tm_sec);
}
