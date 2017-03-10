/*
**  @(#)utils.h
**
**  libnetwork - utility functions
**  ------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#ifndef __UTILS_H
#define __UTILS_H

/*
**  Define maximum IP address string size.
*/
#ifndef _MAX_IP_ADDRESS_SIZE
#define _MAX_IP_ADDRESS_SIZE 16
#else
#error  _MAX_IP_ADDRESS_SIZE is defined in another include file
#endif

/*
**  Define maximum hostname string size.
*/
#ifndef _MAX_HOSTNAME_SIZE
#define _MAX_HOSTNAME_SIZE 255
#else
#error  _MAX_HOSTNAME_SIZE is defined in another include file
#endif

/*
**  Function prototypes.
*/
extern int GetHostIPAddress(const string_c_t, string_c_t, size_t);
extern int GetHostName(const string_c_t, string_c_t, size_t);

#endif /* __UTILS_H */

