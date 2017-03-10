/*
**  @(#)version.h
**
**  libnetwork - library version information
**  ----------------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#ifndef __VERSION_H
#define __VERSION_H

/*
**  Check if product version and release number strings are defined in another include file.
*/
#ifdef  _NETWORK_PRODUCT
#error  _NETWORK_PRODUCT is defined in another include file
#endif
#ifdef  _NETWORK_RELEASE
#error  _NETWORK_RELEASE is defined in another include file
#endif

/*
**  Define product version and release number strings.
*/
#define _NETWORK_PRODUCT "libnetwork"
#define _NETWORK_RELEASE "libnetwork v7.0.0 release 1"

/*
**  Function prototypes.
*/
extern string_c_t GetNetworkLibraryVersionProduct(void);
extern string_c_t GetNetworkLibraryVersionRelease(void);

#endif /* __VERSION_H */

