/*
**  @(#)debug.c
**
**  libnetwork - debug functions
**  ----------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Local function prototypes.
*/
static string_c_t FormatStringValue(string_c_t);

/*
**  Debug (print server action request) structure.
*/
void HttpDebugPrintServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar)
{
    /*
    **  Is server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    **  Print debug information.
    */
    printf("\ndebug -> HTTP_SERVER_ACTION_REQUEST\n");
    printf(" hsar->host\t: %s\n", FormatStringValue(hsar->host));
    printf(" hsar->port\t: %d\n", hsar->port);
    printf(" hsar->req\t: %s\n", FormatStringValue(hsar->req));
    printf(" hsar->req_size\t: %d\n", hsar->req_size);
    printf(" hsar->rsp_fp\t: %p\n", (void *)hsar->rsp_fp);
    printf(" hsar->timeout\t: %d\n", hsar->timeout);
    printf(" hsar->log_file\t: %s\n", FormatStringValue(hsar->log_file));
    printf(" hsar->trace\t: %d\n\n", hsar->trace);
}

/*
**  Print string value.
*/
static string_c_t FormatStringValue(string_c_t value)
{
    if (value) {
        return (value);
    }
    return ((string_c_t)"null");
}

