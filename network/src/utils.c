/*
**  @(#)utils.c
**
**  libnetwork - utility functions
**  ------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
**  Local function prototypes.
*/
#ifdef _WINDOWS_ENVIRONMENT
static int LoadWindowsSocketLibrary(void);
static void UnloadWindowsSocketLibrary(void);
#endif

/*
**  Get IP network address (in dot notation) for a given host name.
*/
int GetHostIPAddress(const string_c_t hostname, string_c_t address, size_t address_size)
{
    struct hostent *hostent;
    struct in_addr in_addr;
    char buffer[_MAX_HOSTNAME_SIZE + 1];

    /*
    **  Check address size.
    */
    if (address_size > _MAX_HOSTNAME_SIZE + 1) {
        address_size = _MAX_HOSTNAME_SIZE + 1;
    }

    /*
    **  Load Windows socket (dynamic) library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    if (LoadWindowsSocketLibrary() != 0) {
        return (-1);
    }
#endif

    /*
    **  Get host address information.
    */
    if ((hostent = gethostbyname(hostname)) == NULL) {
#ifdef _LOG_ERROR_MESSAGE
        NetLogFilePrint((string_c_t)"error-> gethostbyname() failed: unable to get host entry by name\n");
#endif
        strcpy_p(address, address_size, (const string_c_t)"", sizeof(""));
#ifdef _WINDOWS_ENVIRONMENT
        UnloadWindowsSocketLibrary();
#endif
        return (h_errno);
    }

    /*
    **  Clear format buffer.
    */
    memset(buffer, 0, sizeof(buffer));

    /*
    **  Convert host address number to host address string.
    */
    memcpy(&in_addr, hostent->h_addr_list[0], hostent->h_length);
    strfmt_p(buffer, sizeof(buffer), (const string_c_t)"%s", inet_ntoa(in_addr));
    strcpy_p(address, address_size, buffer, address_size - 1);

    /*
    **  Unload Windows socket library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    UnloadWindowsSocketLibrary();
#endif
    return (0);
}

/*
**  Get host name for a given IP network address(in dot notation).
*/
int GetHostName(const string_c_t address, string_c_t host_name, size_t host_name_size)
{
    struct hostent *hostent;
    char buffer[_MAX_HOSTNAME_SIZE + 1];

#ifdef _POSIX_ENVIRONMENT
    in_addr_t in_addr;
#else
    unsigned long in_addr;
#endif

    /*
    **  Check host name size.
    */
    if (host_name_size > _MAX_HOSTNAME_SIZE + 1) {
        host_name_size = _MAX_HOSTNAME_SIZE + 1;
    }

    /*
    **  Load Windows socket (dynamic) library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    if (LoadWindowsSocketLibrary() != 0) {
        return (-1);
    }
#endif

    /*
    **  Translate network address string to Internet address integer.
    */
    in_addr = inet_addr(address);

    /*
    **  Gets network host entry by Internet address integer.
    */
    if ((hostent = gethostbyaddr((string_c_t)&in_addr, sizeof(in_addr), AF_INET)) == NULL) {
#ifdef _LOG_ERROR_MESSAGE
        NetLogFilePrint((string_c_t)"error-> inet_addr() failed: unable to get network host entry by address\n");
#endif
        strcpy_p(host_name, host_name_size, (const string_c_t)"", sizeof(""));
#ifdef _WINDOWS_ENVIRONMENT
        UnloadWindowsSocketLibrary();
#endif
        return (h_errno);
    }

    /*
    **  Clear format buffer.
    */
    memset(buffer, 0, sizeof(buffer));

    /*
    **  Format and copy host name from host entry.
    */
    strfmt_p(buffer, sizeof(buffer), (const string_c_t)"%s", hostent->h_name);
    strcpy_p(host_name, host_name_size, buffer, host_name_size - 1);

    /*
    **  Unload Windows socket library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    UnloadWindowsSocketLibrary();
#endif
    return (0);
}

#ifdef _WINDOWS_ENVIRONMENT
/*
**  Load Windows socket (dynamic) library.
*/
static int LoadWindowsSocketLibrary(void)
{
    WSADATA wsa_data;

    /*
    **  Load Windows socket library.
    */
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        NetLogFilePrint((string_c_t)"error-> WSAStartup() failed: unable to load Windows socket dynamic library\n");
        return (-1);
    }
    return (0);
}

/*
**  Unload Windows socket (dynamic) library.
*/
static void UnloadWindowsSocketLibrary(void)
{
    WSACleanup();
}
#endif /* _WINDOWS_ENVIRONMENT */

