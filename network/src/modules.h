/*
**  @(#)modules.h
**
**  libnetwork - modules
**  --------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __MODULES_H
#define __MODULES_H

/*
**  Standard C include files.
*/
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/*
**  POSIX environment include files.
*/
#ifdef _POSIX_ENVIRONMENT
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

/*
**  Windows environment include files.
*/
#ifdef _WINDOWS_ENVIRONMENT
#include <io.h>
#include <share.h>
#include <winsock.h>
#endif

/*
**  Windows environment functions.
*/
#ifdef _WINDOWS_ENVIRONMENT
#define close _close
#define open _open
#define read _read
#define strcasecmp _stricmp
#define write _write
#endif

/*
**  Network library include files.
*/
#include "common.h"
#include "http.h"
#include "httputil.h"
#include "net.h"
#include "netlogs.h"
#include "debug.h"
#include "port.h"
#include "utils.h"
#include "version.h"

#endif /* __MODULES_H */

