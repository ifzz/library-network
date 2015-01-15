/*
**  @(#)net.h
**
**  libnetwork - TCP/IP network interface functions
**  -----------------------------------------------
**
**  copyright 2001-2015 Software Constructions (SC)
*/
#ifndef __NET_H
#define __NET_H

/*
**  Function prototypes.
*/
extern int ServerConnect(const string_c_t, const int);
extern int ServerSendRequest(int, const string_c_t, const string_c_t);
extern int ServerReceiveResponse(int, string_c_t, int);
extern int ServerGetHostAddress(string_c_t, string_c_t);
extern int ServerDisconnect(int);
extern int GetSocketOption(int, int, int, void *, int *);
extern int SetSocketOption(int, int, int, const void *, int);

#endif /* __NET_H */

