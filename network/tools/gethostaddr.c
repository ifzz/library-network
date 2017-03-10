/*
**  @(#)gethostaddr.c
**
**  libnetwork utility - get host IP address utility
**  ------------------------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
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
    memset(hostname, 0, _MAX_HOSTNAME_SIZE + 1);
    memset(address, 0, _MAX_IP_ADDRESS_SIZE + 1);

    /*
    **  Get command line options.
    */
    GetOptions(argc, argv, hostname);

    /*
    **  Display usage if no hostname was given.
    */
    if (strlen(hostname) < 1) {
        DisplayUsage();
        return (EXIT_SUCCESS);
    }

    /*
    **  Get host IP address.
    */
    if (GetHostIPAddress(hostname, address, _MAX_IP_ADDRESS_SIZE) == EXIT_SUCCESS) {
        printf("Host name  : %s\n", hostname);
        printf("IP address : %s\n\n", address);
    }

    /*
    **  Return status.
    */
    return (EXIT_SUCCESS);
}

/*
**  Get command line options.
*/
static void GetOptions(int argc, string_c_t argv[], string_c_t hostname)
{
    int c;

    if (argc < 2) {
        DisplayUsage();
    }

    /*
    **  Process each option on the command line.
    */
    while (TRUE)
        {
        c = getopt(argc, argv, (const string_c_t)"?h:v");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?' : DisplayUsage();
                       break;
            case 'h' : strcpy_p(hostname, _MAX_HOSTNAME_SIZE, optarg, _MAX_HOSTNAME_SIZE);
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
    string_c_t release = GetNetworkLibraryVersionRelease();

    printf("%s - get host address\n", _GETHOSTADDR_VERSION_PRODUCT);
    printf("%s tool\n\n", release);
}

/*
**  Display usage.
*/
static void DisplayUsage(void)
{
    printf("usage: %s -? -v -h <host>\n", _GETHOSTADDR_VERSION_PRODUCT);
    exit(EXIT_SUCCESS);
}

