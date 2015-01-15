/*
**  @(#)gethostname.c
**
**  libnetwork utility - get host name utility
**  ------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Local function prototype.
*/
static void GetOptions(int, string_c_t [], string_c_t);
static void InterruptHandler(void);
static void DisplayVersion(void);
static void DisplayUsage(void);

/*
**  Get host IP address utility.
*/
int main(int argc, string_c_t argv[])
{
    char hostname[_MAX_HOSTNAME_SIZE + 1], address[_MAX_IP_ADDRESS_SIZE + 1];

    /*
    **  Set signal trap for signal interrupt from the console or user.
    */
    signal(SIGINT, (fptr_c_t)InterruptHandler);

    /*
    **  Setup hostname and address parameters.
    */
    memset(hostname, (int)NULL, _MAX_HOSTNAME_SIZE + 1);
    memset(address, (int)NULL, _MAX_IP_ADDRESS_SIZE + 1);

    /*
    **  Get command line options.
    */
    GetOptions(argc, argv, address);

    /*
    **  Display usage if no address was given.
    */
    if (strlen(address) < 1) {
        DisplayUsage();
        return (EXIT_SUCCESS);
    }

    /*
    **  Get host name.
    */
    if (GetHostName(address, hostname, _MAX_HOSTNAME_SIZE) == EXIT_SUCCESS) {
        printf("Host name  : %s\n", hostname);
        printf("IP address : %s\n\n", address);
    }

    /*
    **  Return status.    printf("%s\n\n", GETHTTP_VERSION_STRING);
    */
    return (EXIT_SUCCESS);
}

/*
**  Get command line options.
*/
static void GetOptions(int argc, string_c_t argv[], string_c_t address)
{
    int c;

    /*
    **  Process each option on the command line.
    */
    while (TRUE) {
        c = getopt(argc, argv, (const string_c_t)"a:hv");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?' : DisplayUsage();
                       break;
            case 'a' : strcpy_p(address, _MAX_IP_ADDRESS_SIZE, optarg, _MAX_IP_ADDRESS_SIZE);
                       break;
            case 'v' : DisplayVersion();
                       break;
            default  : exit(EXIT_FAILURE);
                       break;
        }
    }
}

/*
**  Interrupt handler.
*/
static void InterruptHandler(void)
{
    /*
    **  Display interrupt message and exit application.
    */
    printf("signal detected!\n");
    exit(EXIT_SUCCESS);
}

/*
**  Display version.
*/
static void DisplayVersion(void)
{
    printf("%s - get host name\n",  _GETHOSTNAME_VERSION_PRODUCT);
    printf("%s release %s\n\n", _NETWORK_VERSION_NUMBER, _NETWORK_RELEASE_NUMBER);
}

/*
**  Display usage.
*/
static void DisplayUsage(void)
{
    printf("usage: %s -? -v -a <address>\n",  _GETHOSTNAME_VERSION_PRODUCT);
    exit(EXIT_SUCCESS);
}

