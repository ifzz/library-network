/*
**  @(#)netlogs.h
**
**  libnetwork - library logging functions
**  --------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __NETLOGS_H
#define __NETLOGS_H

/*
**  Define default logfile name.
*/
#ifndef _LOGFILE_NAME
#define _LOGFILE_NAME "libnetwork"
#else
#error  _LOGFILE_NAME is defined in another include file
#endif

/*
**  Define file mode string size.
*/
#ifndef _FILE_MODE_SIZE
#define _FILE_MODE_SIZE 8
#else
#error  _FILE_MODE_SIZE is defined in another include file
#endif

/*
**  Function prototypes.
*/
extern void NetLogFileDirectory(const string_c_t, size_t);
extern void NetLogFileSetFileName(const string_c_t);
extern void NetLogFileOpen(void);
extern void NetLogFilePrint(string_c_t, ...);
extern void NetLogFileFlush(void);
extern void NetLogFileClose(void);

#endif /* __NETLOGS_H */

