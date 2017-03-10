/*
**  @(#)http.h
**
**  libnetwork - HTTP networking functions
**  --------------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#ifndef __HTTP_H
#define __HTTP_H

/*
**  Check if HTTP methods are defined in another include file.
*/
#ifdef  _HTTP_METHOD_OPTIONS
#error  _HTTP_METHOD_OPTIONS is defined in another include file
#endif
#ifdef  _HTTP_METHOD_GET
#error  _HTTP_METHOD_GET is defined in another include file
#endif
#ifdef  _HTTP_METHOD_HEAD
#error  _HTTP_METHOD_HEAD is defined in another include file
#endif
#ifdef  _HTTP_METHOD_POST
#error  _HTTP_METHOD_POST is defined in another include file
#endif
#ifdef  _HTTP_METHOD_PUT
#error  _HTTP_METHOD_PUT is defined in another include file
#endif
#ifdef  _HTTP_METHOD_DELETE
#error  _HTTP_METHOD_DELETE is defined in another include file
#endif
#ifdef  _HTTP_METHOD_TRACE
#error  _HTTP_METHOD_TRACE is defined in another include file
#endif
#ifdef  _HTTP_METHOD_CONNECT
#error  _HTTP_METHOD_CONNECT is defined in another include file
#endif

/*
**  Define HTTP methods.
*/
#define _HTTP_METHOD_OPTIONS "OPTIONS"
#define _HTTP_METHOD_GET "GET"
#define _HTTP_METHOD_HEAD "HEAD"
#define _HTTP_METHOD_POST "POST"
#define _HTTP_METHOD_PUT "PUT"
#define _HTTP_METHOD_DELETE "DELETE"
#define _HTTP_METHOD_TRACE "TRACE"
#define _HTTP_METHOD_CONNECT "CONNECT"

/*
**  Define default timeout period.
*/
#ifndef _TIMEOUT_PERIOD
#define _TIMEOUT_PERIOD 10
#else
#error  _TIMEOUT_PERIOD is defined in another include file
#endif

/*
**  Define maximum network socket size.
*/
#ifndef _MAX_NET_SOCKET_SIZE
#define _MAX_NET_SOCKET_SIZE 65535
#else
#error  _MAX_NET_SOCKET_SIZE is defined in another include file
#endif

/*
**  Define HTTP server action request structure and type.
*/
typedef struct HttpServerActionRequest {
        string_c_t host;
        int port;
        string_c_t req;
        int req_size;
        FILE *rsp_fp;
        int timeout;
        string_c_t log_file;
        int trace;
} HTTP_SERVER_ACTION_REQUEST;

/*
**  Function prototypes.
*/
extern HTTP_SERVER_ACTION_REQUEST *HttpAllocateServerActionRequest(HTTP_SERVER_ACTION_REQUEST *);
extern int HttpSetHost(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, size_t);
extern int HttpSetPort(HTTP_SERVER_ACTION_REQUEST *, int);
extern int HttpSetRequestBuffer(HTTP_SERVER_ACTION_REQUEST *, size_t);
extern int HttpSetResponseFile(HTTP_SERVER_ACTION_REQUEST *, FILE *);
extern int HttpSetTimeout(HTTP_SERVER_ACTION_REQUEST *, int);
extern int HttpSetLogFileName(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, size_t);
extern int HttpSetTrace(HTTP_SERVER_ACTION_REQUEST *, int);
extern void HttpPrintWarningMessages(int);
extern void HttpFreeServerActionRequest(HTTP_SERVER_ACTION_REQUEST *);
extern void HttpFreeHost(HTTP_SERVER_ACTION_REQUEST *);
extern void HttpFreeRequestBuffer(HTTP_SERVER_ACTION_REQUEST *);
extern void HttpFreeResponseFile(HTTP_SERVER_ACTION_REQUEST *);
extern void HttpFreeLogFileName(HTTP_SERVER_ACTION_REQUEST *);
extern int HttpSendServerRequest(HTTP_SERVER_ACTION_REQUEST *);
extern int HttpSendServerRequestNoTimeout(HTTP_SERVER_ACTION_REQUEST *);

#endif /* __HTTP_H */

