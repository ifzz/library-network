/*
**  @(#)getopt.c
**
**  libnetwork utility - get options functions
**  ------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Option argument pointer.
*/
string_c_t optarg;

/*
**  Option argument index.
*/
static int optind = 0;

/*
**  Option argument scan pointer.
*/
static string_c_t scan = NULL;

/*
**  Get options from command line arguments.
*/
int getopt(int argc, string_c_t argv[], string_c_t string)
{
    char c;
    string_c_t mark;

    optarg = NULL;

    /*
    **  Check option index and argument list for next argument.
    */
    if (scan == NULL || *scan == '\0') {
        if (optind == 0) {
            optind++;
        }
        if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0') {
            return( EOF);
        }
        if (strcmp(argv[optind], "--") == 0) {
            optind++;
            return (EOF);
        }

        /*
        **  Store next option argument and increment option index.
        */
        scan = argv[optind] + 1;
        optind++;
    }

    /*
    **  Get option symbol.
    */
    c = *scan++;

    /*
    **  Search for option symbol in option string.
    */
    mark = strchr(string, c);

    /*
    **  Check for unknown option symbol.
    */
    if (mark == NULL || c == ':') {
        printf("%s: unknown option -%c\n", argv[0], c);
        return ('?');
    }

    /*
    **  Store option argument from argument list (if applicable).
    */
    mark++;
    if (*mark == ':') {
        if (*scan != '\0') {
            optarg = scan;
            scan = NULL;
        }
        else if (optind < argc) {
            optarg = argv[optind];
            optind++;
        }
        else {
            printf("%s: -%c argument missing\n", argv[0], c);
            return ('?');
        }
    }

    /*
    **  Return option symbol.
    */
    return (c);
}

