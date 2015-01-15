/*
**  @(#)httputil.c
**
**  libnetwork - HTTP networking utility functions
**  ----------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  URL character representations.
*/
struct URLCharReps {
       char character;
       const char *replacement;
}
URLCharRepsTable[] = {
       { '\t', "%09" }, { '\n', "%0A" }, { '\r', "%0D" }, { ' ',  "%20" },
       { '!',  "%21" }, { '"',  "%22" }, { '#',  "%23" }, { '$',  "%24" },
       { '%',  "%25" }, { '&',  "%26" }, { '\'', "%27" }, { '(',  "%28" },
       { ')',  "%29" }, { '*',  "%2A" }, { '+',  "%2B" }, { ',',  "%2C" },
       { '-',  "%2D" }, { '.',  "%2E" }, { '/',  "%2F" }, { ':',  "%3A" },
       { ';',  "%3B" }, { '<',  "%3C" }, { '=',  "%3D" }, { '>',  "%3E" },
       { '?',  "%3F" }, { '@',  "%40" }, { '[' , "%5B" }, { '\\', "%5C" },
       { ']',  "%5D" }, { '^',  "%5E" }, { '_',  "%5F" }, { '`',  "%60" },
       { '{',  "%7B" }, { '|',  "%7C" }, { '}',  "%7D" }, { '~',  "%7E" },
       { 0,    NULL }
};

/*
**  Local function prototypes.
*/
static bool_c_t SpecialCharactersFilter(char, string_c_t, int);
static string_c_t StringTrim(string_c_t);

/*
**  Set request type.
*/
int HttpSetRequestType(HTTP_SERVER_ACTION_REQUEST *hsar, HTTP_REQUEST_TYPE type)
{
    string_c_t format;
    size_t size = 0;

    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Are request buffer and request buffer size valid?
    */
    if (!hsar->req || !hsar->req_size) {
        return (-1);
    }

    /*
    **  Allocate memory for format buffer.
    */
    format = (string_c_t)malloc(_MAX_REQUEST_SIZE + 1);
    if (format != NULL) {
        memset(format, 0, _MAX_REQUEST_SIZE + 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory(%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    **  Format request type.
    */
    if (type == HTTP_REQ_TYPE_POST) {
        strfmt_p(format, _MAX_REQUEST_SIZE, (const string_c_t)"%s ", _HTTP_METHOD_POST);
    }
    else {
        strfmt_p(format, _MAX_REQUEST_SIZE, (const string_c_t)"%s ", _HTTP_METHOD_GET);
    }

    /*
    **  Get length of formatted request type.
    */
    size = strlen(format);

    /*
    **  Copy formatted request type to request buffer.
    */
    strcat_p(hsar->req, hsar->req_size, format, _MAX_REQUEST_SIZE);

    /*
    **  Free format buffer.
    */
    free(format);

    /*
    **  Return length of format request type.
    */
    return (size);
}

/*
**  Set request.
*/
int HttpSetRequest(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t value, const size_t value_size)
{
    /*
    **  Is search action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Are request buffer and request buffer size valid?
    */
    if (!hsar->req || !hsar->req_size) {
        return (-1);
    }

    /*
    **  Are value and value size valid?
    */
    if (!value || !value_size || (size_t)hsar->req_size < value_size) {
        return (-1);
    }

    /*
    **  Concatenate request value to request buffer.
    */
    strcat_p(hsar->req, hsar->req_size, value, value_size);

    /*
    **  Return value size.
    */
    return (value_size);
}

/*
**  Set request parameter.
*/
int HttpSetRequestParameter(string_c_t request, const size_t req_size, const string_c_t parameter, const size_t parameter_size, const string_c_t value, const size_t value_size)
{
    string_c_t encoded, format;
    size_t encoded_size, format_size, size;

    /*
    **  Are request buffer and request buffer size valid?
    */
    if (!request || !req_size || req_size < _MIN_REQUEST_SIZE) {
        return (-1);
    }

    /*
    **  Are parameter and parameter size valid?
    */
    if (!parameter || !parameter_size) {
        return (-1);
    }

    /*
    **  Are value and value size valid?
    */
    if (!value || !value_size || req_size < value_size) {
        return (-1);
    }

    /*
    **  Check for possible request buffer overflow.
    */
    size = parameter_size + sizeof("=") + (value_size * _MAX_URL_CHAR_SIZE) + 1;
    if (req_size < size) {
        NetLogFilePrint((string_c_t)"error-> insufficient request buffer size %d(request + parameters = %d)\n", req_size, size);
        return (-1);
    }

    /*
    **  Calculate encoded buffer size.
    */
    encoded_size = (value_size * _MAX_URL_CHAR_SIZE) + 1;

    /*
    **  Allocate memory for encoded buffer.
    */
    encoded = (string_c_t)malloc(encoded_size);
    if (encoded != NULL) {
        memset(encoded, 0, encoded_size);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory(%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    **  Calculate format buffer size.
    */
    format_size = parameter_size + sizeof("=") + (value_size * _MAX_URL_CHAR_SIZE) + 1;

    /*
    **  Allocate memory for format buffer.
    */
    format = (string_c_t)malloc(format_size);
    if (format != NULL) {
        memset(format, 0, format_size);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory(%s line: %d)\n", __FILE__, __LINE__);
        free(encoded);
        return (-2);
    }

    /*
    **  Encode request parameter value as HTTP URL parameter.
    */
    memcpy(encoded, value, value_size);
    StringTrim(encoded);
    HttpEncodeUrlParameter(encoded, strlen(encoded), (value_size * _MAX_URL_CHAR_SIZE));

    /*
    **  Format request parameter with parameter value.
    */
    strfmt_p(format, format_size, (const string_c_t)"%s=%s", parameter, encoded);

    /*
    **  Get length of formatted request parameter.
    */
    size = strlen(format);

    /*
    **  Concatenate formatted request parameter to request buffer.
    */
    strcat_p(request, req_size, format, format_size);

    /*
    **  Free encoded and format buffers.
    */
    free(encoded);
    free(format);

    /*
    **  Return length of formatted request parameter.
    */
    return (size);
}

/*
**  Set request parameter separator.
*/
int HttpSetRequestParameterSeparator(string_c_t request, const size_t req_size)
{
    /*
    **  Are request buffer and request buffer size valid?
    */
    if (!request || !req_size) {
        return (-1);
    }

    /*
    **  Concatenate HTTP URL separator to request buffer.
    */
    strcat_p(request, req_size, (const string_c_t)"&", sizeof("&"));

    /*
    **  Return length of parameter separator.
    */
    return (1);
}

/*
**  Set HTTP version header.
*/
int HttpSetVersionHeader(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t host, const size_t host_size)
{
    string_c_t format;
    size_t size = 0;

    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    **  Are request buffer and request buffer size valid?
    */
    if (!hsar->req || !hsar->req_size) {
        return (-1);
    }

    /*
    **  Are host name and host name size valid?
    */
    if (!host || !host_size) {
        return (-1);
    }

    /*
    **  Allocate memory for format buffer.
    */
    format = (string_c_t)malloc(hsar->req_size - 1);
    if (format != NULL) {
        memset(format, 0, hsar->req_size - 1);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory(%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    **  Format HTTP version with parameter hostname.
    */
    strfmt_p(format, hsar->req_size - 1, (const string_c_t)" HTTP/1.0\nHost: %s\n\n", host);

    /*
    **  Get length of formatted HTTP version header.
    */
    size = strlen(format);

    /*
    **  Concatenate formatted HTTP version header to request buffer.
    */
    strcat_p(hsar->req, hsar->req_size, format, size);

    /*
    **  Free format buffers.
    */
    free(format);

    /*
    **  Return length of formatted HTTP version header.
    */
    return (size);
}

/*
**  Encode URL parameter.
*/
int HttpEncodeUrlParameter(string_c_t source, const size_t source_size, const size_t length)
{
    string_c_t encoded;
    size_t i, j;
    int c;

    /*
    **  Are source string and source string size valid?
    */
    if (!source || !source_size) {
        return (-1);
    }

    /*
    **  Allocate memory for encoded buffer.
    */
    encoded = (string_c_t)malloc(BUFSIZ);
    if (encoded != NULL) {
        memset(encoded, 0, BUFSIZ);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> malloc() failed: insufficient memory(%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    **  Encode each character to URL hexadecimal representation (if applicable).
    */
    for (i = 0, j = 0; i < source_size; i++, j++) {
        c = source[i];

        if (isdigit(c)) {
            encoded[j] = source[i];
        }
        else if (islower(c)) {
            encoded[j] = source[i];
        }
        else if (isupper(c)) {
            encoded[j] = source[i];
        }
        else {
            if (SpecialCharactersFilter(c, encoded, j) == TRUE) {
                j = j + 2;
            }
            else {
                encoded[j] = ' ';
            }
        }
    }

    /*
    **  Copy encoded buffer to source buffer.
    */
    if (j > length) {
        NetLogFilePrint((string_c_t)"error-> memcpy() failed: unable to copy encoded buffer\n");
    }
    else {
        memset(source, 0, length);
        memcpy(source, encoded, j);
    }

    /*
    **  Free encoded buffer.
    */
    free(encoded);

    /*
    **  Return encoded buffer.
    */
    return (j);
}

/*
**  Special characters filter (for URL encoding/decoding).
*/
static bool_c_t SpecialCharactersFilter(char c, string_c_t encoded, int j)
{
    int k;

    /*
    **  Search for matching special character in URL replacement table.
    */
    for (k = 0; URLCharRepsTable[k].character; k++) {
        if (c == URLCharRepsTable[k].character) {
            encoded[j] = URLCharRepsTable[k].replacement[0]; j++;
            encoded[j] = URLCharRepsTable[k].replacement[1]; j++;
            encoded[j] = URLCharRepsTable[k].replacement[2];
            return (TRUE);
        }
    }

    /*
    **  Match failed.
    */
    return (FALSE);
}

/*
**  Trim leading and trailing spaces in a string.
*/
static string_c_t StringTrim(string_c_t s)
{
    string_c_t s1, s2;

    /*
    **  Trim leading, trailing spaces if string is valid.
    */
    if (s) {
        for (s1 = s2 = s; *s1; ) {
            while (*s1 && (isspace((int)*s1))) {
                s1++;
            }
            if (*s1 && (s2 != s)) {
                *(s2++) = ' ';
            }
            while (*s1 && (!isspace((int)*s1))) {
                *(s2++) = *(s1++);
            }
        }
        *s2 = '\0';
    }
    return (s);
}

