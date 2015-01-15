/*
**  @(#)version.h
**
**  libnetwork - library version information
**  ----------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __VERSION_H
#define __VERSION_H

/*
**  Check if product version and release number strings are defined in another include file.
*/
#ifdef  _NETWORK_PRODUCT
#error  _NETWORK_PRODUCT is defined in another include file
#endif
#ifdef  _NETWORK_VERSION_NUMBER
#error  _NETWORK_VERSION_NUMBER  is defined in another include file
#endif
#ifdef  _NETWORK_RELEASE_NUMBER
#error  _NETWORK_RELEASE_NUMBER is defined in another include file
#endif

/*
**  Define product version and release number strings.
*/
#define _NETWORK_PRODUCT "libnetwork"
#define _NETWORK_VERSION_NUMBER "6.0.0"
#define _NETWORK_RELEASE_NUMBER "1"

/*
**  Function prototypes.
*/
extern void GetNetworkLibraryVersion(string_c_t, size_t);

#endif /* __VERSION_H */

