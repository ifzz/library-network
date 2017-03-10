/*
**  @(#)version.c
**
**  libnetwork - library version information
**  ----------------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
**  Version information.
*/
string_c_t GetNetworkLibraryVersionProduct(void)
{
    return ((string_c_t)_NETWORK_PRODUCT);
}

string_c_t GetNetworkLibraryVersionRelease(void)
{
    return ((string_c_t)_NETWORK_RELEASE);
}

