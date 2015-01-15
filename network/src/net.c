/*
**  @(#)net.c
**
**  libnetwork - TCP/IP network interface functions
**  -----------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
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
**  Connect to TCP/IP server.
*/
int ServerConnect(const string_c_t host, const int port)
{
    struct sockaddr_in server;
    struct hostent *hostent;
    int sock;

    /*
    **  Load Windows socket (dynamic) library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    if (LoadWindowsSocketLibrary() != 0) {
        return (-1);
    }
#endif

    /*
    **  Create a reliable stream socket using TCP.
    */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        NetLogFilePrint((string_c_t)"error-> socket() failed: unable to create TCP socket\n");
        return (-1);
    }

    /*
    **  Resolve host server name as binary, byte ordered address.
    */
    if ((hostent = gethostbyname(host)) == NULL) {
        NetLogFilePrint((string_c_t)"error-> gethostbyname() failed: unable to resolve host name:(%s)\n", host);
        return (-1);
    }

    /*
    **  Construct the server address structure.
    */
    memset(&server, 0, sizeof(server));
    memcpy((string_c_t)&server.sin_addr, hostent->h_addr, hostent->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    /*
    **  Establish connection to TCP/IP server.
    */
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        NetLogFilePrint((string_c_t)"error-> connect() failed: unable to connect to TCP/IP server\n");
        return (-1);
    }

    /*
    **  Return socket handle.
    */
    return (sock);
}

/*
**  Send request to TCP/IP server.
*/
int ServerSendRequest(int sock, const string_c_t req, const string_c_t host)
{
    int count = 0;

    /*
    **  Is send request valid?
    */
    if (!req) {
        return (-1);
    }

    /*
    **  Send request buffer to TCP/IP server.
    */
    count = strlen(req);
    if (send(sock, req, count, 0) == count) {
        return (0);
    }
    else {
        NetLogFilePrint((string_c_t)"error-> send() failed: unable to send request to TCP/IP server\n");
        return (-1);
    }
}

/*
**  Receive response from TCP/IP server.
*/
int ServerReceiveResponse(int sock, string_c_t resp, int size)
{
    int count = 0;

    /*
    **  Clear response buffer.
    */
    memset(resp, 0, size);

    /*
    **  Receive response data from TCP/IP server.
    */
    count = recv(sock, resp, size, 0);
    return (count);
}

/*
**  Disconnect from TCP/IP server.
*/
int ServerDisconnect(int sock)
{
#ifdef _WINDOWS_ENVIRONMENT
    if (sock) {
        closesocket(sock);
    }
#else
    if (sock) {
        close(sock);
    }
#endif

    /*
    **  Unload Windows socket library.
    */
#ifdef _WINDOWS_ENVIRONMENT
    UnloadWindowsSocketLibrary();
#endif
    return (0);
}

/*
**  Get socket option.
*/
int GetSocketOption(int sock, int level, int option_name, void *option_value, int *option_len)
{
#ifdef _WINDOWS_ENVIRONMENT
    return getsockopt(sock, level, option_name, (string_c_t)option_value, option_len);
#else
    return getsockopt(sock, level, option_name, option_value, (socklen_t *)option_len);
#endif
}

/*
**  Set socket option.
*/
int SetSocketOption(int sock, int level, int option_name, const void *option_value, int option_len)
{
#ifdef _WINDOWS_ENVIRONMENT
    return setsockopt(sock, level, option_name, (string_c_t)option_value, option_len);
#else
    return setsockopt(sock, level, option_name, option_value, (socklen_t)option_len);
#endif
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

