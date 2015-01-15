/*
**  @(#)modules.h
**
**  libnetwork utility - modules
**  ----------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __MODULES_H
#define __MODULES_H

/*
**  Standard C header files.
*/
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/*
**  POSIX environment C header files.
*/
#ifdef _POSIX_ENVIRONMENT
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

/*
**  Windows environment C header files.
*/
#ifdef _WINDOWS_ENVIRONMENT
#include <io.h>
#include <winsock.h>
#endif

/*
**  Windows environment C functions.
*/
#ifdef _WINDOWS_ENVIRONMENT
#define strcasecmp _stricmp
#endif

/*
**  Common definitions header file.
*/
#include "common.h"

/*
**  Network library header file.
*/
#include "network.h"

/*
**  Network utility header files.
*/
#include "gethostaddr.h"
#include "gethostname.h"
#include "gethttp.h"
#include "getopt.h"
#include "port.h"

#endif /* __MODULES_H */

