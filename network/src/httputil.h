/*
**  @(#)httputil.h
**
**  libnetwork - HTTP networking utility functions
**  ----------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __HTTPUTIL_H
#define __HTTPUTIL_H

/*
**  Define minimum request buffer size.
*/
#ifndef _MIN_REQUEST_SIZE
#define _MIN_REQUEST_SIZE 256
#else
#error  _MIN_REQUEST_SIZE is defined in another include file
#endif

/*
**  Define maximum URL character size.
*/
#ifndef _MAX_URL_CHAR_SIZE
#define _MAX_URL_CHAR_SIZE 3
#else
#error  _MAX_URL_CHAR_SIZE is defined in another include file
#endif

/*
**  Define maximum request size.
*/
#ifndef _MAX_REQUEST_SIZE
#define _MAX_REQUEST_SIZE 5
#else
#error  _MAX_REQUEST_SIZE is defined in another include file
#endif

/*
**  Define HTTP request type.
*/
typedef enum HttpRequestType {
        HTTP_REQ_TYPE_GET = 1,
        HTTP_REQ_TYPE_POST
} HTTP_REQUEST_TYPE;

/*
**  Function prototypes.
*/
extern int HttpSetRequestType(HTTP_SERVER_ACTION_REQUEST *, HTTP_REQUEST_TYPE);
extern int HttpSetRequest(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const size_t);
extern int HttpSetRequestParameter(string_c_t, const size_t, const string_c_t, const size_t, const string_c_t, const size_t);
extern int HttpSetRequestParameterSeparator(string_c_t, const size_t);
extern int HttpSetVersionHeader(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const size_t);
extern int HttpEncodeUrlParameter(string_c_t, const size_t, const size_t);

#endif /* __HTTPUTIL_H */

