/*
**  @(#)http.c
**
**  libnetwork - HTTP networking functions
**  --------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Print warning messages flag.
*/
static bool_c_t PrintWarningMessages = FALSE;

/*
**  Local function prototypes.
*/
#ifdef _POSIX_ENVIRONMENT
static void AlarmHandler(int);
#endif

/*
**  Allocate server action request structure.
*/
HTTP_SERVER_ACTION_REQUEST *HttpAllocateServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Allocate memory for server action request structure.
    */
    hsar = (HTTP_SERVER_ACTION_REQUEST *)malloc(sizeof(HTTP_SERVER_ACTION_REQUEST));
    if (hsar == NULL) {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for server action request structure\n");
        return (NULL);
    }

    /*
    **  Set default values to each structure element.
    */
    hsar->host = NULL;
    hsar->port = 80;
    hsar->req = NULL;
    hsar->req_size = 0;
    hsar->rsp_fp = NULL;
    hsar->timeout = 0;
    hsar->log_file = NULL;
    hsar->trace = 0;
    return (hsar);
}

/*
**  Set server action request host name parameter.
*/
int HttpSetHost(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t host, size_t host_size)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is host name valid?
    */
    if (!host || !host_size) {
        return (-1);
    }

    /*
    **  Allocate memory for host name parameter.
    */
    hsar->host = (string_c_t)malloc(host_size + 1);
    if (hsar->host != NULL) {
        memset(hsar->host, 0, host_size + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for host name parameter\n");
        return (-2);
    }

    /*
    **  Set host name parameter.
    */
    strcpy_p(hsar->host, host_size + 1, host, host_size);
    return (host_size);
}

/*
**  Set server action request port (number) parameter.
*/
int HttpSetPort(HTTP_SERVER_ACTION_REQUEST *hsar, int port)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is port number valid?
    */
    if (!port || port > _MAX_NET_SOCKET_SIZE) {
        return (-1);
    }

    /*
    **  Set port number parameter.
    */
    hsar->port = port;
    return (port);
}

/*
**  Set server action request request buffer parameter.
*/
int HttpSetRequestBuffer(HTTP_SERVER_ACTION_REQUEST *hsar, size_t req_size)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is request buffer size valid?
    */
    if (!req_size) {
        return (-1);
    }

    /*
    **  Allocate memory for request buffer parameter.
    */
    hsar->req = (string_c_t)malloc(req_size + 1);
    if (hsar->req != NULL) {
        memset(hsar->req, 0, req_size + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for request buffer parameter\n");
        return (-2);
    }

    /*
    **  Set request buffer size parameter and return request size.
    */
    hsar->req_size = req_size;
    return (req_size);
}

/*
**  Set response file pointer parameter.
*/
int HttpSetResponseFile(HTTP_SERVER_ACTION_REQUEST *hsar, FILE *fp)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Set response file pointer parameter and return status.
    */
    if (fp) {
        hsar->rsp_fp = fp;
    }
    return (EXIT_SUCCESS);
}

/*
**  Set server action request timeout parameter.
*/
int HttpSetTimeout(HTTP_SERVER_ACTION_REQUEST *hsar, int timeout)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is timeout value valid?
    */
    if (!timeout) {
        return (-1);
    }

    /*
    **  Set timeout parameter and return timeout value.
    */
    hsar->timeout = timeout;
    return (timeout);
}

/*
**  Set server action request log file name parameter.
*/
int HttpSetLogFileName(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t log_file, size_t log_file_size)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is log file name valid?
    */
    if (!log_file || !log_file_size) {
        return (-1);
    }

    /*
    **  Allocate memory for log file name parameter.
    */
    hsar->log_file = (string_c_t)malloc(log_file_size + 1);
    if (hsar->log_file != NULL) {
        memset(hsar->log_file, 0, log_file_size + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for log file name parameter\n");
        return (-2);
    }

    /*
    **  Set log file name parameter and return log file size.
    */
    strcpy_p(hsar->log_file, log_file_size + 1, log_file, log_file_size);
    return (log_file_size);
}

/*
**  Set server action request trace (flag) parameter.
*/
int HttpSetTrace(HTTP_SERVER_ACTION_REQUEST *hsar, int trace)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is trace flag value valid?
    */
    if (!trace) {
        return (-1);
    }

    /*
    **  Set trace flag parameter and return trace flag.
    */
    hsar->trace = trace;
    return (trace);
}

/*
**  Print warning messages switch.
*/
void HttpPrintWarningMessages(int flag)
{
    /*
    **  Set print warning messages switch if flag value is valid.
    */
    if (flag == TRUE || flag == FALSE) {
        PrintWarningMessages = (bool_c_t)flag;
    }
}

/*
**  Free server action request structure.
*/
void HttpFreeServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Free memory for each structure element.
    */
    if (hsar->host) {
        free(hsar->host);
    }
    if (hsar->req) {
        free(hsar->req);
    }
    if (hsar->log_file) {
        free(hsar->log_file);
    }

    /*
    **  Free memory for server action request.
    */
    free(hsar);
}

/*
**  Free server action request host name parameter.
*/
void HttpFreeHost(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Is host name valid?
    */
    if (!hsar->host) {
        return;
    }

    /*
    **  Free host name parameter.
    */
    free(hsar->host);
}

/*
**  Free server action request request buffer parameter.
*/
void HttpFreeRequestBuffer(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Is request buffer valid?
    */
    if (!hsar->req) {
        return;
    }

    /*
    **  Free request buffer parameter and reset request buffer size.
    */
    free(hsar->req);
    hsar->req_size = 0;
}

/*
**  Free response file.
*/
void HttpFreeResponseFile(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Is response file valid?
    */
    if (!hsar->rsp_fp) {
        return;
    }

    /*
    **  Free response file and reset response file.
    */
    fclose_p(hsar->rsp_fp);
    hsar->rsp_fp = NULL;
}

/*
**  Free server action request log file name parameter.
*/
void HttpFreeLogFileName(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Is log file name valid?
    */
    if (!hsar->log_file) {
        return;
    }

    /*
    **  Free log file name parameter.
    */
    free(hsar->log_file);
}

/*
**  Send server action request to HTTP server.
*/
int HttpSendServerRequest(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    int sock;
    string_c_t buffer;
    unsigned int count, total = 0;

#ifdef _POSIX_ENVIRONMENT
    struct sigaction sigact;
    sigact.sa_handler = AlarmHandler;
    sigact.sa_flags = 0;
#endif

    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is response file pointer valid?
    */
    if (!hsar->rsp_fp) {
        return (-1);
    }

    /*
    **  Set log file directory.
    */
    NetLogFileDirectory(hsar->log_file, strlen(hsar->log_file));

    /*
    **  Set timeout if no timeout was given.
    */
    if (hsar->timeout) {
        hsar->timeout = _TIMEOUT_PERIOD;
    }

    /*
    **  Set signal handler for alarm signal.
    */
#ifdef _POSIX_ENVIRONMENT
    if (sigfillset(&sigact.sa_mask) < 0) {
        NetLogFilePrint((string_c_t)"error-> sigfillset() failed: unable to set signal handler\n");
        return (-3);
    }
    if (sigaction(SIGALRM, &sigact, 0) < 0) {
        NetLogFilePrint((string_c_t)"error-> sigaction() failed: SIGALRM\n");
        return (-3);
    }
#endif

    /*
    **  Connect to the HTTP server.
    */
    sock = ServerConnect(hsar->host, hsar->port);
    if (sock < 1) {
        return (-3);
    }

    /*
    **  Trace network request.
    */
    if (hsar->trace) {
        NetLogFilePrint((string_c_t)"trace-> request buffer: %s\n", hsar->req);
    }

    /*
    **  Set the timeout alarm.
    */
#ifdef _POSIX_ENVIRONMENT
    alarm(hsar->timeout);
#endif

    /*
    **  Send request to the HTTP server (exit if send request has failed).
    */
    if (ServerSendRequest(sock, hsar->req, hsar->host) != EXIT_SUCCESS) {
        ServerDisconnect(sock);
        return (-3);
    }

    /*
    **  Allocate memory for response buffer.
    */
    buffer = (string_c_t)malloc(BUFSIZ + 1);
    if (buffer != NULL) {
        memset(buffer, 0, BUFSIZ + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for response buffer\n");
        return (-2);
    }

    /*
    **  Process each response from the HTTP server.
    */
    do  {
        /*
        **  Exit if system call was interrupted.
        */
        if (errno == EINTR) {
            ServerDisconnect(sock);
            return (-3);
        }

        /*
        **  Receive response from the HTTP server.
        */
        count = ServerReceiveResponse(sock, buffer, BUFSIZ);
        total = total + count;

        /*
        **  Write contents of response buffer to response file.
        */
        if (fwrite (buffer, 1, count, hsar->rsp_fp) != count) {
            if (PrintWarningMessages == TRUE) {
                NetLogFilePrint((string_c_t)"error-> write() failed: write error to response file (errno %d)\n", errno);
            }
        }

        /*
        **  Trace network response.
        */
        if (hsar->trace) {
            NetLogFilePrint((string_c_t)"trace-> response buffer: %s\n", buffer);
        }
    }
    while (count > 0);

    /*
    **  Free response buffer.
    */
    free(buffer);

    /*
    **  Unset the alarm.
    */
#ifdef _POSIX_ENVIRONMENT
    alarm(0);
#endif

    /*
    **  Disconnect from the HTTP server.
    */
    ServerDisconnect(sock);

    /*
    **  Return total count.
    */
    return (total);
}

/*
**  Send server action request to HTTP server with no timeout.
*/
int HttpSendServerRequestNoTimeout(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    int sock;
    string_c_t buffer;
    unsigned int count, total = 0;

    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Is response file pointer valid?
    */
    if (!hsar->rsp_fp) {
        return (-1);
    }

    /*
    **  Set log file directory.
    */
    NetLogFileDirectory(hsar->log_file, strlen(hsar->log_file));

    /*
    **  Connect to the HTTP server.
    */
    sock = ServerConnect(hsar->host, hsar->port);
    if (sock < 1) {
        return (-3);
    }

    /*
    **  Trace network request.
    */
    if (hsar->trace) {
        NetLogFilePrint((string_c_t)"trace-> request buffer: %s\n", hsar->req);
    }

    /*
    **  Send request to the HTTP server (exit if send request has failed).
    */
    if (ServerSendRequest(sock, hsar->req, hsar->host) != EXIT_SUCCESS) {
        ServerDisconnect(sock);
        return (-3);
    }

    /*
    **  Allocate memory for response buffer.
    */
    buffer = (string_c_t)malloc(BUFSIZ + 1);
    if (buffer != NULL) {
        memset(buffer, 0, BUFSIZ + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory for response buffer (no timeout)\n");
        return (-2);
    }

    /*
    **  Process each response from the HTTP server.
    */
    do  {
        /*
        **  Exit if system call was interrupted.
        */
        if (errno == EINTR) {
            ServerDisconnect(sock);
            return (-3);
        }

        /*
        **  Receive response from the HTTP server.
        */
        count = ServerReceiveResponse(sock, buffer, BUFSIZ);
        total = total + count;

        /*
        **  Write contents of response buffer to response file.
        */
        if (fwrite (buffer, 1, count, hsar->rsp_fp) != count) {
            if (PrintWarningMessages == TRUE) {
                NetLogFilePrint((string_c_t)"error-> write() failed: write error to response file (errno %d)\n", errno);
            }
        }

        /*
        **  Trace network response.
        */
        if (hsar->trace) {
            NetLogFilePrint((string_c_t)"trace-> response buffer: %s\n", buffer);
        }
    }
    while (count > 0);

    /*
    **  Free response buffer.
    */
    free(buffer);

    /*
    **  Disconnect from the HTTP server.
    */
    ServerDisconnect(sock);

    /*
    **  Return total count.
    */
    return (total);
}

#ifdef _POSIX_ENVIRONMENT
/*
**  Signal alarm handler.
*/
static void AlarmHandler(int signal)
{
    if (PrintWarningMessages == TRUE) {
        NetLogFilePrint((string_c_t)"error-> signal alarm(SIGALRM): alarm() timeout condition (%d)\n", signal);
    }
}
#endif /* _POSIX_ENVIRONMENT */

