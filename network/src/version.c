/*
**  @(#)version.c
**
**  libnetwork - library version information
**  ----------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#include "modules.h"

/*
**  Version information.
*/
void GetNetworkLibraryVersion(string_c_t version, size_t version_size)
{
    if (!version) {
        return;
    }
    strcpy_p(version, version_size, (const string_c_t)_NETWORK_VERSION_NUMBER , sizeof(_NETWORK_VERSION_NUMBER));
}

